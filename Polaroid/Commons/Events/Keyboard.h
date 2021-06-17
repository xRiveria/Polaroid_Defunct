#pragma once
#include "EventUtilities.h"

namespace Polaroid
{
	// Keycodes
	enum class Key : uint32_t
	{
        // Keyboard
        Escape = 0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,
        Num0,
        Minus,
        Equals,
        Back,
        Tab,
        Q,
        W,
        E,
        R,
        T,
        Y,
        U,
        I,
        O,
        P,
        LBracket,
        RBracket,
        Enter,
        LControl,
        A,
        S,
        D,
        F,
        G,
        H,
        J,
        K,
        L,
        Semicolon,
        Colon,
        Apostrophe,
        Quotation,
        Grave,
        LShift,
        Backslash,
        Z,
        X,
        C,
        V,
        B,
        N,
        M,
        Comma,
        Period,
        Slash,
        RShift,
        Multiply,
        LAlt,
        Space,
        Capital,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        Numlock,
        Scroll,
        Numpad7,
        Numpad8,
        Numpad9,
        Subtract,
        Numpad4,
        Numpad5,
        Numpad6,
        Add,
        Numpad1,
        Numpad2,
        Numpad3,
        Numpad0,
        Decimal,
        F11,
        F12,
        Numpadenter,
        RControl,
        Divide,
        sysrq,
        RAlt,
        Pause,
        Home,
        Up,
        PgUp,
        Left,
        Right,
        End,
        Down,
        PgDn,
        Insert,
        Del,
        LWin,
        RWin,
        Apps,

        KeysMax
	};

	// Converts a key to a string for serialization.

	// Data passed with keyboard events.
	struct KeyboardData
	{
		Key m_Key;
		ButtonState m_ButtonState;
		ModifierState m_ModifierState;

		static const EventType m_EventType = EventType::Keyboard;

        KeyboardData(Key key, ButtonState state, ModifierState modifiers);
	};
}
