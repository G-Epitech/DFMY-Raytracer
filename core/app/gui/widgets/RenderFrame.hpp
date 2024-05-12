/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RenderFrame.hpp
*/

#pragma once

#include <TGUI/TGUI.hpp>
#include "types/rendering/Screen.hpp"

namespace Raytracer::Core::Gui {
    class RenderFrame: public tgui::Widget {
    public:
        using Ptr = std::shared_ptr<RenderFrame>; //!< Shared widget pointer
        using ConstPtr = std::shared_ptr<const RenderFrame>; //!< Shared constant widget pointer

        static constexpr const char StaticWidgetType[] = "Picture"; //!< Type name of the widget

        /**
         * @brief Construct a new RenderFrame object
         * @param typeName Type name of the widget
         * @param initRenderer Initialize the renderer
         */
        explicit RenderFrame(const char* typeName = StaticWidgetType, bool initRenderer = true);

        /**
         * @brief Destroy the RenderFrame object
         */
        ~RenderFrame() override;

        /**
         * @brief Create a new RenderFrame
         * @return Shared pointer to the new RenderFrame
         */
        static Ptr create();

        bool isMouseOnWidget(tgui::Vector2f pos) const override;

        void draw(tgui::BackendRenderTarget& target, tgui::RenderStates states) const override;

        Widget::Ptr clone() const override;

        /**
         * @brief Update the render frame from a screen object
         * @param screen Screen object
         */
        void updateFromScreen(Raytracer::Core::Rendering::Screen &screen);

    private:
        /// @brief Sprite object
        tgui::Sprite _sprite;

        /// @brief Texture object
        tgui::Texture _texture;
    };
}
