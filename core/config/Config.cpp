/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer
** File description:
** Config
*/

#include "Config.hpp"
#include "ConfigValidator.hpp"

Config::Config()
: _contents(""), _path(""), _sceneConfig(), _fromString(false) {}

void Config::loadFromString(const std::string &configContents)
{
    _contents = configContents;
    _fromString = true;
    _load();
}

void Config::loadFromFile(const std::string &configPath)
{
    _path = configPath;
    _fromString = false;
    _load();
}

Raytracer::Core::Config::SceneConfig Config::getSceneConfig() const
{
    return _sceneConfig;
}

Rendering::Scene::Ptr Config::toScene(PluginsManager &pluginsManager)
{
    Rendering::Scene::Ptr scene = std::make_shared<Rendering::Scene>(_sceneConfig.name);

    scene->ambient.first = _sceneConfig.ambient.color;
    scene->ambient.second = _sceneConfig.ambient.strength;
    _buildSceneCameras(scene);
    _buildSceneMaterials(scene);
    _buildSceneObjects(scene, pluginsManager);
    return scene;
}

void Config::_buildSceneCameras(Rendering::Scene::Ptr scene)
{
    Rendering::Camera::Config cameraConfig;

    for (auto &camera: _sceneConfig.cameras) {
        cameraConfig.name = camera.name;
        cameraConfig.position = camera.position;
        cameraConfig.direction = camera.direction;
        cameraConfig.fov = camera.fov;
        cameraConfig.screen.size = camera.screen.size;
        scene->cameras[cameraConfig.name] = std::make_shared<Rendering::Camera>(cameraConfig);
    }
}

void Config::_buildSceneMaterials(Rendering::Scene::Ptr scene)
{
    for (auto &material: _sceneConfig.materials) {
        scene->materials[material.name] =
            std::make_shared<Common::Graphics::Material>(
                material.color,
                material.emissions[0].color,
                Common::Graphics::Color(0, 0, 0, 0),
                material.reflectivity
            );
    }
}

void Config::_buildSceneObjects(Rendering::Scene::Ptr scene, PluginsManager &pluginsManager)
{
    Raytracer::Core::ObjectFactory objectFactory(pluginsManager);

    for (auto &object: _sceneConfig.objects) {
        scene->objects.push_back(objectFactory.create(
            object.type,
            scene->materials[object.material],
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
    }
    const libconfig::Setting &root = cfg.getRoot();
    _settingHasValidKeys("root", root, {"cameras", "materials", "objects", "ambient"});
    _sceneConfig.name = _loadName();
    _sceneConfig.ambient = _loadAmbient(root);
    _sceneConfig.cameras = _loadCameras(root);
    _sceneConfig.materials = _loadMaterials(root);
    _sceneConfig.objects = _loadObjects(root);
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
    _settingHasValidKeys("ambient", ambientCfg, {"color", "strength"});
    ambient.color = _parseColor(ambientCfg["color"]);
    _lookupValueWrapper("strength", ambientCfg, ambient.strength);
    return ambient;
}

std::vector<Config::CameraConfig> Config::_loadCameras(const libconfig::Setting &root)
{
    std::vector<Config::CameraConfig> cameras = {};
    Config::CameraConfig camera;
    const libconfig::Setting &camerasCfg = root["cameras"];

    if (!camerasCfg.isList()){
        throw Raytracer::Core::ConfigException("cameras must be a list");
    }
    for (int i = 0; i < camerasCfg.getLength(); i++) {
        const libconfig::Setting &cameraCfg = camerasCfg[i];
        _settingHasValidKeys("camera", cameraCfg, {"direction",
            "position", "fieldOfView", "name", "screen"});
        _lookupValueWrapper("name", cameraCfg, camera.name);
        camera.position = _parsePoint3D("position", cameraCfg["position"]);
        camera.direction = _parseVector3D("direction", cameraCfg["direction"]);
        _lookupValueWrapper("fieldOfView", cameraCfg, camera.fov);
        camera.screen = _parseCameraScreen(cameraCfg["screen"]);
        cameras.push_back(camera);
    }
    return cameras;
}

Config::ScreenConfig Config::_parseCameraScreen(const libconfig::Setting &setting)
{
    Config::ScreenConfig screen;
    unsigned height, width;

    if (!setting.isGroup()) {
        throw Raytracer::Core::ConfigException("screen must be a group");
    }
    _settingHasValidKeys("screen", setting, {"origin", "size"});
    screen.origin = _parsePoint3D("screen origin", setting["origin"]);
    if (!setting["size"].isGroup()) {
        throw Raytracer::Core::ConfigException("size must be a group of 2 integers");
    }
    _settingHasValidKeys("size", setting["size"], {"width", "height"});
    _lookupValueWrapper("width", setting["size"], width);
    _lookupValueWrapper("height", setting["size"], height);
    screen.size = {width, height};
    return screen;
}

std::vector<Config::MaterialConfig> Config::_loadMaterials(const libconfig::Setting &root)
{
    std::vector<MaterialConfig> materials = {};
    const libconfig::Setting &materialsCfg = root["materials"];

    if (!materialsCfg.isList()){
        throw Raytracer::Core::ConfigException("materials must be a list");
    }
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
    _settingHasValidKeys("material", setting, {"name", "color",
        "emissions", "reflectivity"});
    _lookupValueWrapper("name", setting, material.name);
    material.color = _parseColor(setting["color"]);
    _lookupValueWrapper("reflectivity", setting, material.reflectivity);
    material.emissions = _parseEmissions(setting["emissions"]);
    return material;
}

std::vector<Config::EmissionConfig> Config::_parseEmissions(const libconfig::Setting &setting)
{
    std::vector<EmissionConfig> emissions = {};
    EmissionConfig emission;

    if (!setting.isList()) {
        throw Raytracer::Core::ConfigException("emissions must be a list");
    }
    for (int i = 0; i < setting.getLength(); i++) {
        const libconfig::Setting &emissionCfg = setting[i];

        if (!emissionCfg.isGroup()) {
            throw Raytracer::Core::ConfigException("emission must be a list of groups");
        }
        _settingHasValidKeys("emission", emissionCfg,
            {"direction", "color", "strength"});
        emission.direction = _parseVector3D("direction", emissionCfg["direction"]);
        emission.color = _parseColor(emissionCfg["color"]);
        _lookupValueWrapper("strength", emissionCfg, emission.strength);
        emissions.push_back(emission);
    }
    return emissions;
}

std::vector<Config::ObjectConfig> Config::_loadObjects(const libconfig::Setting &root)
{
    std::vector<ObjectConfig> objects = {};
    const libconfig::Setting &objectsCfg = root["objects"];

    if (!objectsCfg.isList()){
        throw Raytracer::Core::ConfigException("objects must be a list");
    }
    for (int i = 0; i < objectsCfg.getLength(); i++) {
        objects.push_back(_parseObject(objectsCfg[i]));
    }
    return objects;
}

Config::ObjectConfig Config::_parseObject(const libconfig::Setting &setting)
{
    ObjectConfig object;

    if (!setting.isGroup())
        throw Raytracer::Core::ConfigException("object must be a group");
    _settingHasValidKeys("object", setting, {"type", "material", "properties",
        "origin"});
    _lookupValueWrapper("type", setting, object.type);
    _lookupValueWrapper("material", setting, object.material);
    object.origin = _parsePoint3D("object origin", setting["origin"]);
    if (object.type == "sphere") {
        object.property = _parseSphere(setting["properties"]);
    }
    if (object.type == "cube") {
        object.property = _parseCube(setting["properties"]);
    }
    return object;
}

float Config::_parseSphere(const libconfig::Setting &setting)
{
    float radius;

    if (!setting.isGroup()) {
        throw Raytracer::Core::ConfigException("sphere must be a group");
    }
    _settingHasValidKeys("sphere", setting, {"radius"});
    _lookupValueWrapper("radius", setting, radius);
    return radius;
}

Math::Float3 Config::_parseCube(const libconfig::Setting &settings)
{
    Math::Float3 cubeSize;
    std::tuple<float, float, float> tuple;

    if (!settings.isGroup())
        throw Raytracer::Core::ConfigException("cube must be a group");
    _settingHasValidKeys("cube", settings, {"size"});
    if (!settings["size"].isGroup())
        throw Raytracer::Core::ConfigException("size must be a group");
    _settingHasValidKeys("size", settings["size"], {"width", "height", "depth"});
    tuple = _parseTuple3f("size", settings["size"], {"width", "height", "depth"});
    cubeSize.x = std::get<0>(tuple);
    cubeSize.y = std::get<1>(tuple);
    cubeSize.z = std::get<2>(tuple);
    return cubeSize;
}

std::tuple<float, float, float> Config::_parseTuple3f(const std::string& prop,
    const libconfig::Setting &setting, const std::vector<std::string>& keys)
{
    std::tuple<float, float, float> tuple;
    if (!setting.isGroup())
        throw Raytracer::Core::ConfigException(prop + " must be a group of 3 floats {x, y, z}");
    _settingHasValidKeys(prop, setting, keys);
    _lookupValueWrapper(keys[0], setting, std::get<0>(tuple));
    _lookupValueWrapper(keys[1], setting, std::get<1>(tuple));
    _lookupValueWrapper(keys[2], setting, std::get<2>(tuple));
    return tuple;
}

Math::Vector3D Config::_parseVector3D(const std::string& propName, const libconfig::Setting &setting)
{
    Math::Vector3D vector3;
    std::tuple<float, float, float> tuple;

    if (!setting.isGroup())
        throw Raytracer::Core::ConfigException(propName + "must be a group of 3 floats {x, y, z}");
    tuple = _parseTuple3f(propName, setting, {"x", "y", "z"});
    vector3.x = std::get<0>(tuple);
    vector3.y = std::get<1>(tuple);
    vector3.z = std::get<2>(tuple);
    return vector3;
}

Math::Point3D Config::_parsePoint3D(const std::string& propName, const libconfig::Setting &setting)
{
    Math::Point3D point3;
    std::tuple<float, float, float> tuple;

    if (!setting.isGroup())
        throw Raytracer::Core::ConfigException(propName + " must be a list of 3 floats");
    tuple = _parseTuple3f(propName, setting, {"x", "y", "z"});
    point3.x = std::get<0>(tuple);
    point3.y = std::get<1>(tuple);
    point3.z = std::get<2>(tuple);
    return point3;
}

Raytracer::Common::Graphics::Color Config::_parseColor(const libconfig::Setting &setting)
{
    Raytracer::Common::Graphics::Color color;
    std::tuple<int, int, int, int> icolor;

    if (!setting.isGroup())
        throw Raytracer::Core::ConfigException("color must be a group of 4 integers");
    _settingHasValidKeys("color", setting, {"r", "g", "b", "a"});
    _lookupValueWrapper("r", setting, std::get<0>(icolor));
    _lookupValueWrapper("g", setting, std::get<1>(icolor));
    _lookupValueWrapper("b", setting, std::get<2>(icolor));
    _lookupValueWrapper("a", setting, std::get<3>(icolor));
    color.r = std::get<0>(icolor);
    color.g = std::get<1>(icolor);
    color.b = std::get<2>(icolor);
    color.a = std::get<3>(icolor);
    return color;
}

void Config::_settingHasValidKeys(const std::string& prop, const libconfig::Setting &setting,
    const std::vector<std::string> &keys)
{
    bool has_all_keys = true;
    std::string error_msg = prop + " must have ";

    for (int i = 0; i < keys.size(); i++){
        if (!setting.exists(keys[i])) {
            has_all_keys = false;
        }
        if (i == keys.size() - 1) {
            error_msg += "\"" + keys[i] + "\"";
        } else {
            error_msg += "\"" + keys[i] + "\"" + ", ";
        }
    }
    if (!has_all_keys) {
        throw Raytracer::Core::ConfigException(error_msg + " as keys");
    }
}
