/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2024 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_SCROLLABLE_PANEL_RENDERER_HPP
#define TGUI_SCROLLABLE_PANEL_RENDERER_HPP


#include <TGUI/Renderers/PanelRenderer.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TGUI_MODULE_EXPORT namespace tgui
{
    class TGUI_API ScrollablePanelRenderer : public PanelRenderer
    {
    public:

        using PanelRenderer::PanelRenderer;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the renderer data of the scrollbars
        ///
        /// @param scrollbarRendererData  Data about how the scrollbars should look
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setScrollbar(std::shared_ptr<RendererData> scrollbarRendererData);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer data of the scrollbars
        ///
        /// @return Data about how the scrollbars looks
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD std::shared_ptr<RendererData> getScrollbar() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the wanted width of the scrollbar
        /// @param scrollbarWidth  Requested scrollbar width or 0 to use the default width (texture size if using textures)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setScrollbarWidth(float scrollbarWidth);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the wanted width of the scrollbar
        /// @return Requested scrollbar width or 0 if no width was set (texture width or default value will be used)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getScrollbarWidth() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_SCROLLABLE_PANEL_RENDERER_HPP