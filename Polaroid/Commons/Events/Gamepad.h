#pragma once
#include "EventUtilities.h"

namespace Polaroid
{
    // Gamepad Button Pressed
    enum class GamepadButton : uint32_t
    {
        DPadUp,
        DPadDown,
        DPadLeft,
        DPadRight,

        StartButton,
        BackButton,

        LThumbClick,
        RThumbClick,
        LShoulder,
        RShoulder,

        AButton,
        BButton,
        XButton,
        YButton,

        GamepadButtonMax
    };

    // Gamepay Analog Stick
    enum class AnalogInput : uint32_t
    {
        // Gamepad
        AnalogLeftTrigger,
        AnalogRightTrigger,

        AnalogLeftStickX,
        AnalogLeftStickY,

        AnalogRightStickX,
        AnalogRightStickY,

        // Mouse
        AnalogMouseX,
        AnalogMouseY,
        AnalogMouseScroll,

        AnalogInputsMax
    };

    struct GamepadData
    {
        /// Gamepad Data.
    };
}