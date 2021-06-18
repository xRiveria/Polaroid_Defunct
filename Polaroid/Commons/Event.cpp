#include "Event.h"

namespace Polaroid
{
    ModifierState::ModifierState(bool ctrlPressed, bool altPressed, bool shiftPressed , bool superPressed) : m_Control(ctrlPressed), m_Alt(altPressed), m_Shift(shiftPressed), m_Super(superPressed)
    {

    }

    MouseMoveData::MouseMoveData(uint32_t x, uint32_t y, uint32_t screenX, uint32_t screenY, int deltaX, int deltaY) : m_X(x), m_Y(y), m_ScreenX(screenX), m_ScreenY(screenY), m_DeltaX(deltaX), m_DeltaY(deltaY)
    {

    }

    MouseInputData::MouseInputData(MouseInput button, ButtonState state, ModifierState modifiers) : m_MouseButton(button), m_ButtonState(state), m_ModifierState(modifiers)
    {

    }

    MouseRawData::MouseRawData(int deltaX, int deltaY) : m_DeltaX(deltaX), m_DeltaY(deltaY)
    {

    }

    MouseWheelData::MouseWheelData(double delta, ModifierState modifiers) : m_Delta(delta), m_ModifierState(modifiers)
    {

    }

    KeyboardData::KeyboardData(Key key, ButtonState state, ModifierState modifiers) : m_Key(key), m_ButtonState(state), m_ModifierState(modifiers)
    {

    }

    DPIData::DPIData(float scale) : m_Scale(scale)
    {

    }

    FocusData::FocusData(bool isFocused) : m_IsFocused(isFocused)
    {

    }

    ResizeData::ResizeData(uint32_t newWidth, uint32_t newHeight, bool isResizing) : m_Width(newWidth), m_Height(newHeight), m_IsResizing(isResizing)
    {

    }

    Event::Event(EventType type, Window* window)
    {
    }

    Event::Event(FocusData focusData, Window* window)
    {

    }

    Event::Event(ResizeData resizeData, Window* window)
    {

    }

    Event::Event(KeyboardData keyboardData, Window* window)
    {

    }

    Event::Event(MouseMoveData mouseMoveData, Window* window)
    {

    }

    Event::Event(MouseRawData mouseRawData, Window* window)
    {

    }

    Event::Event(MouseInputData mouseInputData, Window* window)
    {

    }

    Event::Event(MouseWheelData mouseWheelData, Window* window)
    {

    }

    Event::Event(DPIData dpiData, Window* window)
    {

    }
}