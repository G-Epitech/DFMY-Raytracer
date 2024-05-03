/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** Config
*/

#include "Config.hpp"

Config::Config()
{
}

Config::SceneConfig Config::load(const std::string &path)
{
    SceneConfig scene_config;
    libconfig::Config cfg;

    try {
        cfg.readFile(path.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        throw Config::Exception("I/O error while reading file.");
    } catch (const libconfig::ParseException &pex) {
        throw Config::Exception("Parse error at " + std::to_string(pex.getLine())
            + ": " + pex.getError() + " - " + pex.getFile());
    }
    const libconfig::Setting &root = cfg.getRoot();
    _settingHasValidKeys("root", root, {"cameras", "materials", "objects", "ambient"});
    scene_config.name = _loadName(path);
    scene_config.ambient = _loadAmbient(root);
    scene_config.cameras = _loadCameras(root);
    scene_config.materials = _loadMaterials(root);
    scene_config.objects = _loadObjects(root);
    return scene_config;
}

std::string Config::_loadName(const std::string &path)
{
    std::string name = path;
    size_t found = name.find_last_of("/");

    if (found != std::string::npos) {
        name = name.substr(found + 1);
    }
    found = name.find_last_of(".");
    if (found != std::string::npos) {
        name = name.substr(0, found);
    }
    return name;
}

Config::AmbientConfig Config::_loadAmbient(const libconfig::Setting &root)
{
    AmbientConfig ambient;
    const libconfig::Setting &ambient_cfg = root["ambient"];

    if (!root.isGroup()) {
        throw Config::Exception("ambient must be a group");
    }
    _settingHasValidKeys("ambient", ambient_cfg, {"color", "strength"});
    ambient.color = _parseColor(ambient_cfg["color"]);
    _lookupValueWrapper("strength", ambient_cfg, ambient.strength);
    return ambient;
}

std::list<Config::CameraConfig> Config::_loadCameras(const libconfig::Setting &root)
{
    std::list<CameraConfig> cameras = {};
    CameraConfig camera;
    unsigned height, width;
    const libconfig::Setting &cameras_cfg = root["cameras"];

    if (!cameras_cfg.isList()){
        throw Config::Exception("cameras must be a list");
    }
    for (int i = 0; i < cameras_cfg.getLength(); i++) {
        const libconfig::Setting &camera_cfg = cameras_cfg[i];
        _settingHasValidKeys("camera", camera_cfg, {"resolution", "direction",
            "position", "fieldOfView"});
        if (!camera_cfg["resolution"].isGroup()) {
            throw Config::Exception("resolution must be a group of 2 integers");
        }
        _lookupValueWrapper("height", camera_cfg["resolution"], height);
        _lookupValueWrapper("width", camera_cfg["resolution"], width);
        camera.resolution = {height, width};
        camera.position = _parsePoint3D("position", camera_cfg["position"]);
        camera.direction = _parseVector3D("direction", camera_cfg["direction"]);
        _lookupValueWrapper("fieldOfView", camera_cfg, camera.fov);
        cameras.push_back(camera);
    }
    return cameras;
}

std::list<Config::MaterialConfig> Config::_loadMaterials(const libconfig::Setting &root)
{
    std::list<MaterialConfig> materials = {};
    const libconfig::Setting &materials_cfg = root["materials"];

    if (!materials_cfg.isList()){
        throw Config::Exception("materials must be a list");
    }
    for (int i = 0; i < materials_cfg.getLength(); i++) {
        materials.push_back(_parseMaterial(materials_cfg[i]));
    }
    return materials;
}

Config::MaterialConfig Config::_parseMaterial(const libconfig::Setting &setting)
{
    MaterialConfig material = {};

    if (!setting.isGroup()) {
        throw Config::Exception("material must be a group");
    }
    _settingHasValidKeys("material", setting, {"name", "objectColor",
        "emissionDirections", "reflectivity"});
    _lookupValueWrapper("name", setting, material.name);
    material.color = _parseColor(setting["objectColor"]);
    _lookupValueWrapper("reflectivity", setting, material.reflectivity);
    material.emissionDirections = _parseEmissionDirections(setting["emissionDirections"]);
    return material;
}

std::vector<Config::EmissionDirectionConfig> Config::_parseEmissionDirections(const libconfig::Setting &setting)
{
    std::vector<EmissionDirectionConfig> emissionDirections = {};
    EmissionDirectionConfig emissionDirection;

    if (!setting.isList()) {
        throw Config::Exception("emissionDirections must be a list");
    }
    for (int i = 0; i < setting.getLength(); i++) {
        const libconfig::Setting &emissionDirection_cfg = setting[i];

        if (!emissionDirection_cfg.isGroup()) {
            throw Config::Exception("emissionDirection must be a list of groups");
        }
        _settingHasValidKeys("emissionDirection", emissionDirection_cfg,
            {"vector", "color", "strength"});
        emissionDirection.vector = _parseVector3D("vector", emissionDirection_cfg["vector"]);
        emissionDirection.color = _parseColor(emissionDirection_cfg["color"]);
        _lookupValueWrapper("strength", emissionDirection_cfg, emissionDirection.strength);
        emissionDirections.push_back(emissionDirection);
    }
    return emissionDirections;
}

std::list<Config::ObjectConfig> Config::_loadObjects(const libconfig::Setting &root)
{
    std::list<ObjectConfig> objects = {};
    const libconfig::Setting &objects_cfg = root["objects"];

    if (!objects_cfg.isList()){
        throw Config::Exception("objects must be a list");
    }
    for (int i = 0; i < objects_cfg.getLength(); i++) {
        objects.push_back(_parseObject(objects_cfg[i]));
    }
    return objects;
}

Config::ObjectConfig Config::_parseObject(const libconfig::Setting &setting)
{
    ObjectConfig object;

    if (!setting.isGroup())
        throw Config::Exception("object must be a group");
    _settingHasValidKeys("object", setting, {"type", "material", "properties",
        "origin"});
    _lookupValueWrapper("type", setting, object.type);
    _lookupValueWrapper("material", setting, object.material);
    object.origin = _parseVector3D("object origin", setting["origin"]);
    if (object.type == "sphere") {
        object.properties = _parseSphere(setting["properties"]);
    }
    if (object.type == "cube") {
        object.properties = _parseCube(setting["properties"]);
    }
    return object;
}

Config::SphereConfig Config::_parseSphere(const libconfig::Setting &setting)
{
    SphereConfig sphere;

    if (!setting.isGroup()) {
        throw Config::Exception("sphere must be a group");
    }
    _settingHasValidKeys("sphere", setting, {"radius"});
    _lookupValueWrapper("radius", setting, sphere.radius);
    return sphere;
}

Config::CubeConfig Config::_parseCube(const libconfig::Setting &settings)
{
    CubeConfig cube;
    std::tuple<float, float, float> tuple;

    if (!settings.isGroup())
        throw Config::Exception("cube must be a group");
    _settingHasValidKeys("cube", settings, {"size"});
    if (!settings["size"].isGroup())
        throw Config::Exception("size must be a group");
    _settingHasValidKeys("size", settings["size"], {"width", "height", "depth"});
    tuple = _parseTuple3f("size", settings["size"], {"width", "height", "depth"});
    cube.size = {std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple)};
    return cube;
}

std::tuple<float, float, float> Config::_parseTuple3f(const std::string prop,
    const libconfig::Setting &setting, const std::vector<std::string> keys)
{
    std::tuple<float, float, float> tuple;
    if (!setting.isGroup())
        throw Config::Exception(prop + " must be a group of 3 floats {x, y, z}");
    _settingHasValidKeys(prop, setting, keys);
    _lookupValueWrapper(keys[0], setting, std::get<0>(tuple));
    _lookupValueWrapper(keys[1], setting, std::get<1>(tuple));
    _lookupValueWrapper(keys[2], setting, std::get<2>(tuple));
    return tuple;
}

Math::Vector3D Config::_parseVector3D(const std::string propName, const libconfig::Setting &setting)
{
    Math::Vector3D vector3;
    std::tuple<float, float, float> tuple;

    if (!setting.isGroup())
        throw Config::Exception(propName + "must be a group of 3 floats {x, y, z}");
    tuple = _parseTuple3f(propName, setting, {"x", "y", "z"});
    vector3.x = std::get<0>(tuple);
    vector3.y = std::get<1>(tuple);
    vector3.z = std::get<2>(tuple);
    return vector3;
}

Math::Point3D Config::_parsePoint3D(const std::string propName, const libconfig::Setting &setting)
{
    Math::Point3D point3;
    std::tuple<float, float, float> tuple;

    if (!setting.isGroup())
        throw Config::Exception(propName + " must be a list of 3 floats");
    tuple = _parseTuple3f(propName, setting, {"x", "y", "z"});
    point3.x = std::get<0>(tuple);
    point3.y = std::get<1>(tuple);
    point3.z = std::get<2>(tuple);
    return point3;
}

Graphics::Color Config::_parseColor(const libconfig::Setting &setting)
{
    Graphics::Color color;
    std::tuple<int, int, int, int> icolor;

    if (!setting.isGroup())
        throw Config::Exception("color must be a group of 4 floats");
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

void Config::_settingHasValidKeys(const std::string prop, const libconfig::Setting &setting,
    const std::vector<std::string> &keys)
{
    bool has_all_keys = true;
    std::string error_msg = prop + " must have ";

    for (int i = 0; i < keys.size(); i++){
        if (!setting.exists(keys[i])) {
            has_all_keys = false;
        }
        if (i == keys.size() - 1) {
            error_msg += keys[i];
        } else {
            error_msg += keys[i] + ", ";
        }
    }
    if (!has_all_keys) {
        throw Config::Exception(error_msg);
    }
}

template <typename T>
void Config::_lookupValueWrapper(const std::string prop,
    const libconfig::Setting &setting, T &value)
{
    if (setting.lookupValue(prop, value) == false) {
        throw Config::Exception(prop + " must be a " + _typeName(value));
    }
}

template <typename T>
std::string Config::_typeName(T &value)
{
    int status;
    std::string tname = typeid(T).name();
    char *demangled = abi::__cxa_demangle(tname.c_str(), nullptr, nullptr, &status);

    if (status == 0) {
        tname = demangled;
        free(demangled);
    } else {
        tname = "unknown";
    }
    return tname;
}
