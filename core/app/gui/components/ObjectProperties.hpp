/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** ObjectProperties
*/

#pragma once

#include "interfaces/IObject.hpp"
#include <TGUI/TGUI.hpp>

namespace Raytracer::Core::Gui {
    class ObjectProperties {
        public:
            explicit ObjectProperties(Raytracer::Common::IObject::Ptr &obj);
            ~ObjectProperties() = default;

            void init(tgui::Group::Ptr &settingsGroup);

        private:
            Raytracer::Common::IObject::Ptr &_obj;

            tgui::ScrollablePanel::Ptr _propertiesPanel;

            tgui::EditBox::Ptr _objName;

            /// @brief Object position X
            tgui::SpinControl::Ptr _objPositionX;
            /// @brief Object position Y
            tgui::SpinControl::Ptr _objPositionY;
            /// @brief Object position Z
            tgui::SpinControl::Ptr _objPositionZ;
            /// @brief Object direction X
            tgui::SpinControl::Ptr _objDirectionX;
            /// @brief Object direction Y
            tgui::SpinControl::Ptr _objDirectionY;
            /// @brief Object direction Z
            tgui::SpinControl::Ptr _objDirectionZ;

            void _initPropertiesName();
            void _initPropertiesPosition();
            void _initPropertiesDirection();
    };
}
