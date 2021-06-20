#pragma once
#include "Events/Mouse.h"
#include "Events/Keyboard.h"
#include "Events/Miscellaneous.h"
#include "Events/Touch.h"

namespace Polaroid
{
    class Window;

    union EventData
    {
        FocusData m_Focus_Data;
        ResizeData m_Resize_Data;
        DPIData m_DPI_Data;
        KeyboardData m_Keyboard_Data;
        MouseMoveData m_MouseMove_Data;
        MouseInputData m_MouseInput_Data;
        MouseWheelData m_MouseWheel_Data;
        MouseRawData m_MouseRaw_Data;

        EventData() {}

        ~EventData() {}
    };

    class Event
    {
    public:
        Event(EventType type, Window* window);
        ~Event() {}

        // =====
        Event(FocusData focusData, Window* window);
        Event(ResizeData resizeData, Window* window);
        Event(KeyboardData keyboardData, Window* window);
        Event(MouseMoveData mouseMoveData, Window* window);
        Event(MouseRawData mouseRawData, Window* window);
        Event(MouseInputData mouseInputData, Window* window);
        Event(MouseWheelData mouseWheelData, Window* window);
        Event(DPIData dpiData, Window* window);

        const EventType RetrieveEventType() const { return m_Type; }
        EventData& RetrieveEventData() { return m_Data; }
        const uint32_t RetrieveTimestamp() const { return m_Timestamp; }

    private:
        EventType m_Type;       // The event type.
        EventData m_Data;       // The event data.
        Window* m_Window;       // Pointer to a Polaroid window.

        uint32_t m_Timestamp = 0;   // The timestamp of the event.
    };
}