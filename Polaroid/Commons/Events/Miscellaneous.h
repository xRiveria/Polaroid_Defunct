#pragma once
#include "EventUtilities.h"

namespace Polaroid
{
	// Resize data passed with Resize events.
	struct ResizeData
	{
		uint32_t m_Width;		 // New width of the window viewport.
		uint32_t m_Height;	 // New height of the window viewport.
		bool m_IsResizing = false;   // Are we in the midst of resizing?

		ResizeData(uint32_t newWidth, uint32_t newHeight, bool isResizing)
		{

		}

		static const EventType m_EventType = EventType::Resize;
	};

	// Focus data passed with Focus events.
	struct FocusData
	{
		bool m_IsFocused = false;	 // True if cased, false if not.

		FocusData(bool isFocused)
		{

		}

		static const EventType m_EventType = EventType::Focus;
	};

	// DPI data passed with DPI events.
	struct DPIData
	{
		float m_Scale;

		DPIData(float scale)
		{

		}

		static const EventType m_EventType = EventType::DPI;
	};
}