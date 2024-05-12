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

            tgui::EditBox::Ptr _objName;

            tgui::Panel::Ptr _propertiesPanel;

            void _initPropertiesName();
            void _initPropertiesPosition();
    };
}
