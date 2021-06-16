#pragma once
#include "EventUtilities.h"

namespace Polaroid
{
	// Keycodes
	enum class Key : uint32_t
	{
		// Keyboard

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
