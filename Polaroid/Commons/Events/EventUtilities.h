#pragma once
#include <stdint.h>

namespace Polaroid
{
	enum class EventType : uint32_t
	{
		None = 0,

		Close,			// Closing a window.
		Create,			// Creating a window,
		Focus,			// Focus or Unfocus a window.
		Paint,			// Paint events - a good time to present any graphic changes.
		Resize,			// Resizing a window.
		DPI,			// Change in the screen DPI scaling (such as moving a window to a monitor with a larger DPI).
		Keyboard,		// Keyboard input such as press or release events.
		MouseMoved,		// Mouse moving events.
		MouseRaw,		// Raw mouse data events.
		MouseWheel,		// Mouse scrolling events.
		MouseInput,		// Mouse button press events.

		EventTypeMax
	};

	// State of a button press - be it for keyboard, mouse or whatsoever.
	enum ButtonState : uint32_t
	{
		Pressed = 0,
		Released = 1,

		ButtonStateMax
	};

	// State of modifier keys that affect the output of a key press.
	struct ModifierState
	{
		bool m_Control = false;
		bool m_Shift = false;
		bool m_Alt = false;
		bool m_Super = false;	  // Buttons such as the Windows button or Mac command button.
	};
}