/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer
** File description:
** Config
*/

#include "Config.hpp"
#include "ConfigValidator.hpp"

Config::Config(PluginsManager &pluginsManager) :
    _sceneConfig(),
    _fromString(false),
    _pluginsManager(pluginsManager) {}

Config Config::loadFromString(const std::string &configContents, PluginsManager &pluginsManager)
{
    Config config(pluginsManager);

    config._contents = configContents;
    config._fromString = true;
    config._load();
    return config;
}

Config Config::loadFromFile(const std::string &configPath, PluginsManager &pluginsManager)
{
    Config config(pluginsManager);

    config._path = configPath;
    config._fromString = false;
    config._load();
    return config;
}

Raytracer::Core::Config::SceneConfig Config::getSceneConfig() const
{
    return _sceneConfig;
}

Rendering::Scene::Ptr Config::toScene()
{
    Rendering::Scene::Ptr scene = std::make_shared<Rendering::Scene>(_sceneConfig.name);

    scene->ambient.first = _sceneConfig.ambient.color;
    scene->ambient.second = _sceneConfig.ambient.strength;
    _buildSceneCameras(scene);
    _buildSceneMaterials(scene);
    _buildSceneObjects(scene, _pluginsManager);
    return scene;
}

void Config::_buildSceneCameras(const Rendering::Scene::Ptr& scene)
{
    Rendering::Camera::Config cameraConfig;

    for (auto &camera: _sceneConfig.cameras) {
        cameraConfig.name = camera.name;
        cameraConfig.position = camera.position;
        cameraConfig.direction = camera.direction;
        cameraConfig.fov = camera.fov;
        cameraConfig.screen.size = camera.screenSize;
        scene->cameras[cameraConfig.name] = std::make_shared<Rendering::Camera>(cameraConfig);
    }
}

void Config::_buildSceneMaterials(const Rendering::Scene::Ptr& scene)
{
    for (auto &material: _sceneConfig.materials) {
        scene->materials[material.name] =
            std::make_shared<Common::Graphics::Material>(
                material.objectColor,
                material.emissionColor,
                material.emissionStrength,
                material.reflectivity,
                material.emissions
            );
    }
}

void Config::_buildSceneObjects(const Rendering::Scene::Ptr& scene, PluginsManager &pluginsManager)
{
    Raytracer::Core::ObjectFactory objectFactory(pluginsManager);

    for (auto &object: _sceneConfig.objects) {
        scene->objects.push_back(objectFactory.create(
            object.name,
            object.type,
            scene->materials[object.material],
            object.rotation,
            object.origin,
            object.property
        ));
    }
}

void Config::_load()
{
    libconfig::Config cfg;

    try {
        if (_fromString) {
            cfg.readString(_contents);
        } else {
            cfg.readFile(_path.c_str());
        }
    } catch (const libconfig::FileIOException &fioex) {
        throw Raytracer::Core::ConfigException("I/O error while reading file.");
    } catch (const libconfig::ParseException &pex) {
        throw Raytracer::Core::ConfigException("Parse error at " + std::to_string(pex.getLine())
            + ": " + pex.getError() + " - " + pex.getFile());
    } catch (const std::exception &e) {
        throw Raytracer::Core::ConfigException(e.what());
    }
    const libconfig::Setting &root = cfg.getRoot();
    ConfigUtils::settingHasValidKeys("root", root, {"cameras", "materials", "objects", "ambient"});
    _sceneConfig.name = _loadName();
    _sceneConfig.ambient = _loadAmbient(root);
    _sceneConfig.cameras = _loadCameras(root);
    _sceneConfig.materials = _loadMaterials(root);
    _sceneConfig.objects = _loadObjects(root, _pluginsManager);
    ConfigValidator::valid(_sceneConfig);
}

std::string Config::_loadName()
{
    std::string name;
    size_t found;

    if (_fromString) {
        return "scene";
    }
    name = _path;
    found = name.find_last_of('/');
    if (found != std::string::npos) {
        name = name.substr(found + 1);
    }
    found = name.find_last_of('.');
    if (found != std::string::npos) {
        name = name.substr(0, found);
    }
    return name;
}

Config::AmbientConfig Config::_loadAmbient(const libconfig::Setting &root)
{
    AmbientConfig ambient;
    const libconfig::Setting &ambientCfg = root["ambient"];

    if (!ambientCfg.isGroup()) {
        throw Raytracer::Core::ConfigException("ambient must be a group");
    }
    ConfigUtils::settingHasValidKeys("ambient", ambientCfg, {"color", "strength"});
    ambient.color = ConfigUtils::parseColor(ambientCfg["color"]);
    ConfigUtils::lookupValueWrapper("strength", ambientCfg, ambient.strength);
    return ambient;
}

std::vector<Config::CameraConfig> Config::_loadCameras(const libconfig::Setting &root)
{
    std::vector<Config::CameraConfig> cameras = {};
    Config::CameraConfig camera;
    const libconfig::Setting &camerasCfg = root["cameras"];
    unsigned height, width;

    if (!camerasCfg.isList()){
        throw Raytracer::Core::ConfigException("cameras must be a list");
    }
    for (int i = 0; i < camerasCfg.getLength(); i++) {
        const libconfig::Setting &cameraCfg = camerasCfg[i];
        ConfigUtils::settingHasValidKeys("camera", cameraCfg, {"direction",
            "position", "fieldOfView", "name", "size"});
        ConfigUtils::lookupValueWrapper("name", cameraCfg, camera.name);
        camera.position = ConfigUtils::parsePoint3D("position", cameraCfg["position"]);
        camera.direction = ConfigUtils::parseVector3D("direction", cameraCfg["direction"]);
        ConfigUtils::lookupValueWrapper("fieldOfView", cameraCfg, camera.fov);
        ConfigUtils::settingHasValidKeys("camera", cameraCfg["size"], {"width", "height"});
        ConfigUtils::lookupValueWrapper("width", cameraCfg["size"], width);
        ConfigUtils::lookupValueWrapper("height", cameraCfg["size"], height);
        camera.screenSize = {width, height};
        cameras.push_back(camera);
    }
    return cameras;
}

std::vector<Config::MaterialConfig> Config::_loadMaterials(const libconfig::Setting &root)
{
    std::vector<MaterialConfig> materials = {};
    const libconfig::Setting &materialsCfg = root["materials"];

    if (!materialsCfg.isList()){
        throw Raytracer::Core::ConfigException("materials must be a list");
    }
    materials.reserve(materialsCfg.getLength());
    for (int i = 0; i < materialsCfg.getLength(); i++) {
        materials.push_back(_parseMaterial(materialsCfg[i]));
    }
    return materials;
}

Config::MaterialConfig Config::_parseMaterial(const libconfig::Setting &setting)
{
    MaterialConfig material = {};

    if (!setting.isGroup()) {
        throw Raytracer::Core::ConfigException("material must be a group");
    }
    ConfigUtils::settingHasValidKeys("material", setting, {"name", "objectColor",
        "emissions", "reflectivity", "emissionStrength", "emissionColor"});
    ConfigUtils::lookupValueWrapper("name", setting, material.name);
    material.objectColor = ConfigUtils::parseColor(setting["objectColor"]);
    material.emissionColor = ConfigUtils::parseColor(setting["emissionColor"]);
    ConfigUtils::lookupValueWrapper("reflectivity", setting, material.reflectivity);
    ConfigUtils::lookupValueWrapper("emissionStrength", setting, material.emissionStrength);
    material.emissions = _parseEmissions(setting["emissions"]);
    return material;
}

std::vector<Raytracer::Common::Graphics::Material::Emission> Config::_parseEmissions(const libconfig::Setting &setting)
{
    std::vector<Raytracer::Common::Graphics::Material::Emission> emissions = {};
    Raytracer::Common::Graphics::Material::Emission emission;

    if (!setting.isList()) {
        throw Raytracer::Core::ConfigException("emissions must be a list");
    }
    for (int i = 0; i < setting.getLength(); i++) {
        const libconfig::Setting &emissionCfg = setting[i];

        if (!emissionCfg.isGroup()) {
            throw Raytracer::Core::ConfigException("emission must be a list of groups");
        }
        ConfigUtils::settingHasValidKeys("emission", emissionCfg,
            {"direction", "color", "strength"});
        emission.direction = ConfigUtils::parseVector3D("direction", emissionCfg["direction"]);
        emission.color = ConfigUtils::parseColor(emissionCfg["color"]);
        ConfigUtils::lookupValueWrapper("strength", emissionCfg, emission.strength);
        emissions.push_back(emission);
    }
    return emissions;
}

std::vector<Config::ObjectConfig> Config::_loadObjects(const libconfig::Setting &root,
    PluginsManager &pluginsManager)
{
    std::vector<ObjectConfig> objects = {};
    const libconfig::Setting &objectsCfg = root["objects"];

    if (!objectsCfg.isList()){
        throw Raytracer::Core::ConfigException("objects must be a list");
    }
    objects.reserve(objectsCfg.getLength());
    for (int i = 0; i < objectsCfg.getLength(); i++) {
        objects.push_back(_parseObject(objectsCfg[i], pluginsManager));
    }
    return objects;
}

Config::ObjectConfig Config::_parseObject(const libconfig::Setting &setting,
    PluginsManager &pluginsManager)
{
    ObjectConfig object;

    if (!setting.isGroup())
        throw Raytracer::Core::ConfigException("object must be a group");
    ConfigUtils::settingHasValidKeys("object", setting, {"type", "material", "properties",
        "origin", "name", "rotation"});
    ConfigUtils::lookupValueWrapper("name", setting, object.name);
    ConfigUtils::lookupValueWrapper("type", setting, object.type);
    ConfigUtils::lookupValueWrapper("material", setting, object.material);
    object.rotation = ConfigUtils::parseVector3D("object rotation", setting["rotation"]);
    object.origin = ConfigUtils::parsePoint3D("object origin", setting["origin"]);
    if (pluginsManager.providers.find(object.type) == pluginsManager.providers.end()) {
        throw Raytracer::Core::ConfigException("Unknown object type: " + object.type);
    }
    object.property = pluginsManager.providers[object.type]->parseProperty(setting["properties"]);
    return object;
}
