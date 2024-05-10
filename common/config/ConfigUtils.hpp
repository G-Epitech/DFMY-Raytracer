/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** ConfigUtils
*/

#pragma once

#include <libconfig.h++>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <cxxabi.h>
#include <exception>
#include "types/math/Vector.hpp"
#include "types/math/Point.hpp"
#include "types/graphics/Color.hpp"

using namespace Raytracer::Common;

namespace Raytracer::Common {
    class ConfigUtils;
}

class Raytracer::Common::ConfigUtils {
    public:
        ConfigUtils() = delete;
        ~ConfigUtils() = delete;

                /**
         * @brief Parse a vector3D group from the configuration
         * @param propName Name of the property
         * @param setting Setting of the vector3D group
         */
        static Math::Vector3D parseVector3D(const std::string& propName, const libconfig::Setting &setting);
        /**
         * @brief Parse a point3D group from the configuration
         * @param propName Name of the property
         * @param setting Setting of the point3D group
         */
        static Math::Point3D parsePoint3D(const std::string& propName, const libconfig::Setting &setting);
        /**
         * @brief Parse a color group from the configuration
         * @param setting Setting of the color group
         */
        static Raytracer::Common::Graphics::Color parseColor(const libconfig::Setting &setting);
        /**
         * @brief Parse a tuple of 3 floats from the configuration
         * @param prop Name of the property
         * @param setting Setting of the tuple group
         * @param keys List of keys to look for in the tuple
         */
        static std::tuple<float, float, float> parseTuple3f(const std::string& prop,
            const libconfig::Setting &setting, const std::vector<std::string>& keys);

        /// @brief Check if a setting has valid keys
        static void settingHasValidKeys(const std::string& prop, const libconfig::Setting &setting,
            const std::vector<std::string> &keys);

        /// @brief Wrapper to lookup a value from a setting, and assign it to a variable,
        /// throws an exception if the value is not found or is of the wrong type
        template <typename T>
        static void lookupValueWrapper(const std::string prop, const libconfig::Setting &setting, T &value)
        {
            if (setting.lookupValue(prop, value) == false) {
                throw std::runtime_error(prop + " must be a " + _typeName(value));
            }
        }

    private:
        /// @brief Get the type name of a template variable
        /// Mainly used for debugging purposes and error messages
        template <typename T>
        static std::string _typeName(T &value)
        {
            int status = 0;
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

};
