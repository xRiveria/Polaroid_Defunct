#pragma once
#include <string>

namespace Polaroid
{
    struct WindowDescription
    {
        // Transform
        uint32_t m_Width = 1920;                   // Current Window Width
        uint32_t m_Height = 1080;                  // Current Window Height
        uint32_t m_WidthMinimum = 0;               // Minimum Window Width
        uint32_t m_HeightMinimum = 0;              // Minimum Window Height
        uint32_t m_WidthMaximum = 0xFFFF;          // Maximum Window Width
        uint32_t m_HeightMaximum = 0xFFF;          // Maximum Window Height

        // Window Settings
        bool m_IsCentered = true;                  // Should the window be centered upon creation?
        bool m_IsResizable = true;                 // Is the window resizable?
        bool m_IsMovable = true;                   // Is the window movable?
        bool m_IsClosable = true;                  // Is the window closable?
        bool m_IsMinimizable = true;               // Can the window be minimizable?
        bool m_IsMaximizable = true;               // Can the window be maximizable?
        bool m_IsFullscreenEnabled = true;         // Can the window become fullscreen?

        // Color and Style
        uint32_t m_BackgroundColor = 0xFFFFFFFF;   // Hexadecimal background color (0xFFFFFFFF = white).
        bool m_IsTransparent = false;              // Is this window transparent?
        bool m_IsFrameEnabled = true;              // Does this window contain a frame?
        bool m_IsShadowEnabled = true;             // Are shadows enabled?

                                                   // States
        bool m_IsVisible = true;                   // Is this window currently visible?
        bool m_IsFullscreen = false;               // Is this window currently fullscreen?
        bool m_IsModal = false;                    // Is this window a modal?

                                                   // Application Data
        std::string m_Title;                       // Window Title
        std::string m_Name;                        // Window Name ID
        std::string m_IconPath;                    // Icon Path
    };
}