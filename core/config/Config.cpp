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

scene_config_t Config::load(const std::string &path)
{
    scene_config_t scene_config;
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
    _settingHasValidKeys("root", root, {"cameras", "materials", "objects"});
    scene_config.cameras = _loadCameras(root);
    scene_config.materials = _loadMaterials(root);
    scene_config.objects = _loadObjects(root);
    return scene_config;
}

std::list<camera_config_t> Config::_loadCameras(const libconfig::Setting &root)
{
    std::list<camera_config_t> cameras = {};
    camera_config_t camera;
    unsigned height, width;
    const libconfig::Setting &cameras_cfg = root["cameras"];

    if (!cameras_cfg.isList()){
        throw Config::Exception("cameras must be a list");
    }
    for (int i = 0; i < cameras_cfg.getLength(); i++) {
        const libconfig::Setting &camera_cfg = cameras_cfg[i];
        _settingHasValidKeys("camera", camera_cfg, {"resolution", "rotation", "position", "fieldOfView"});
        if (!camera_cfg["resolution"].isGroup())
            throw Config::Exception("resolution must be a group of 2 integers");
        _lookupValueWrapper("height", camera_cfg["resolution"], height);
        _lookupValueWrapper("width", camera_cfg["resolution"], width);
        camera.resolution = {height, width};
        camera.position = _parsePoint3D("position", camera_cfg["position"]);
        camera.rotation = _parseVector3D("rotation", camera_cfg["rotation"]);
        _lookupValueWrapper("fieldOfView", camera_cfg, camera.fov);
        cameras.push_back(camera);
    }
    return cameras;
}

std::list<material_config_t> Config::_loadMaterials(const libconfig::Setting &root)
{
    std::list<material_config_t> materials = {};
    const libconfig::Setting &materials_cfg = root["materials"];

    if (!materials_cfg.isList()){
        throw Config::Exception("materials must be a list");
    }
    for (int i = 0; i < materials_cfg.getLength(); i++) {
        materials.push_back(_parseMaterial(materials_cfg[i]));
    }
    return materials;
}

material_config_t Config::_parseMaterial(const libconfig::Setting &setting)
{
    material_config_t material = {};

    if (!setting.isGroup()) {
        throw Config::Exception("material must be a group");
    }
    _settingHasValidKeys("material", setting, {"name", "objectColor", "emissionColor",
        "specularColor", "reflectivity", "emissionStrength"});
    _lookupValueWrapper("name", setting, material.name);
    material.objectColor = _parseColor(setting["objectColor"]);
    material.emissionColor = _parseColor(setting["emissionColor"]);
    material.specularColor = _parseColor(setting["specularColor"]);
    _lookupValueWrapper("reflectivity", setting, material.reflectivity);
    _lookupValueWrapper("emissionStrength", setting, material.emissionStrength);
    return material;
}

std::list<object_config_t> Config::_loadObjects(const libconfig::Setting &root)
{
    std::list<object_config_t> objects = {};
    const libconfig::Setting &objects_cfg = root["objects"];

    if (!objects_cfg.isList()){
        throw Config::Exception("objects must be a list");
    }
    for (int i = 0; i < objects_cfg.getLength(); i++) {
        objects.push_back(_parseObject(objects_cfg[i]));
    }
    return objects;
}

object_config_t Config::_parseObject(const libconfig::Setting &setting)
{
    object_config_t object;

    if (!setting.isGroup())
        throw Config::Exception("object must be a group");
    _settingHasValidKeys("object", setting, {"type", "material", "properties", "origin"});
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

object_sphere_config_t Config::_parseSphere(const libconfig::Setting &setting)
{
    object_sphere_config_t sphere;

    if (!setting.isGroup())
        throw Config::Exception("sphere must be a group");
    _settingHasValidKeys("sphere", setting, {"radius"});
    _lookupValueWrapper("radius", setting, sphere.radius);
    return sphere;
}

object_cube_config_t Config::_parseCube(const libconfig::Setting &settings)
{
    object_cube_config_t cube;
    std::tuple<float, float, float> tuple;

    if (!settings.isGroup())
        throw Config::Exception("cube must be a group");
    _settingHasValidKeys("cube", settings, {"size"});
    if (!settings["size"].isGroup())
        throw Config::Exception("size must be a group");
    _settingHasValidKeys("size", settings["size"], {"width", "height", "depth"});
    tuple = _parseTuple3f(settings["size"], {"width", "height", "depth"});
    cube.size = {std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple)};
    return cube;
}

std::tuple<float, float, float> Config::_parseTuple3f(const libconfig::Setting &setting,
    const std::string (&keys)[3])
{
    if (!setting.exists(keys[0]) || !setting.exists(keys[1]) || !setting.exists(keys[2]))
        throw Config::Exception("tuple must have " + keys[0] + ", " + keys[1] + " and " + keys[2]);
    if (!setting[keys[0].c_str()].isNumber() || !setting[keys[1].c_str()].isNumber() || !setting[keys[2].c_str()].isNumber())
        throw Config::Exception(keys[0] + ", " + keys[1] + " and " + keys[2] + " must be floats");
    return {setting[keys[0].c_str()], setting[keys[1].c_str()], setting[keys[2].c_str()]};
}

Math::Vector3D Config::_parseVector3D(const std::string propName, const libconfig::Setting &setting)
{
    Math::Vector3D vector3;
    std::tuple<float, float, float> tuple;

    if (!setting.isGroup())
        throw Config::Exception(propName + "must be a group of 3 floats {x, y, z}");
    tuple = _parseTuple3f(setting, {"x", "y", "z"});
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
    tuple = _parseTuple3f(setting, {"x", "y", "z"});
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

void Config::_settingHasValidKeys(const std::string &prop, const libconfig::Setting &setting,
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
void Config::_lookupValueWrapper( const std::string &prop, const libconfig::Setting &setting, T &value)
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
