#pragma once
#include "EventUtilities.h"

namespace Polaroid
{
    // The event data passed with mouse click events.
    enum MouseInput
    {
        Left,
        Right,
        Middle,
        Button4,
        Button5,

        MouseInputMax
    };

    // The event data passed with mouse move events.
    struct MouseMoveData
    {
        uint32_t m_X;           // Current X position relative to the active window.
        uint32_t m_Y;           // Current Y position relative to the active window.
        uint32_t m_ScreenX;     // Current global X position.
        uint32_t m_ScreenY;     // Current global Y position.
        int m_DeltaX;           // Change in X relative to previous event.
        int m_DeltaY;           // Change in Y relative to previous event.

        static const EventType m_EventType = EventType::MouseMoved;

        MouseMoveData(uint32_t x, uint32_t y, uint32_t screenX, uint32_t screenY, int deltaX, int deltaY);
    };

    // The event data passed with raw mouse move events.
    struct MouseRawData
    {
        int m_DeltaX;
        int m_DeltaY;

        static const EventType m_EventType = EventType::MouseRaw;

        MouseRawData(int deltaX, int deltaY);
    };

    // Data passed with mouse input events.
    struct MouseInputData
    {
        MouseInput m_MouseButton;
        ButtonState m_ButtonState;
        ModifierState m_ModifierState;

        static const EventType m_EventType = EventType::MouseInput;

        MouseInputData(MouseInput button, ButtonState state, ModifierState modifiers);
    };

    // Data passed with mouse wheel events.
    struct MouseWheelData
    {
        double m_Delta;
        ModifierState m_ModifierState;

        static const EventType m_EventType = EventType::MouseWheel;

        MouseWheelData(double delta, ModifierState modifiers);
    };
}