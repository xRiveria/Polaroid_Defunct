#pragma once
#include "EventUtilities.h"

namespace Polaroid
{
    // Data about a touch point on a screen.
    struct TouchPoint
    {
        uint32_t m_ID;        // A unique ID for each touch point.

        uint32_t m_ScreenX;   // Touch coordinate relative to the whole screen in pixels.
        uint32_t m_ScreenY;   // Touch coordinate relative to the whole screen in pixels.
        uint32_t m_WindowX;   // Touch coordinate relative to the window in pixels.
        uint32_t m_WindowY;   // Touch coordinate relative to the window in pixels.

        bool m_HasChanged;    // Did the touch point change?
    };

    // Data passed for touch events.
    struct TouchData
    {
        unsigned int m_NumberOfTouches;

        TouchPoint m_Touches[32];

        static const EventType m_EventType = EventType::Touch;
    };
}