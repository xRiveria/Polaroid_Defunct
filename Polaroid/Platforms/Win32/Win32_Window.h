#pragma once
#include "../Commons/PlatformData.h"
#include "../Commons/WindowDescription.h"
#include "../Commons/EventQueue.h"
#include <Windows.h>

namespace Polaroid
{
	struct WindowDescription;

	class Window
	{
	public:
		Window();
		~Window();

		// Window Actions
		void Create(const WindowDescription& windowDescription, EventQueue& eventQueue);
		void SetSize(const uint32_t newWidth, const uint32_t newHeight);
		void Maximize();
		void Minimize();

		void SetTitle(const std::string& newTitle);
		const std::string& RetrieveTitle() const { m_Title; }

		const bool IsDestroyed() const { return m_IsDestroyed; }
		void Destroy();

		// Executes an event callback asynchonously. Use this for non-blocking events (resizing while rendering, etc).
		void ExecuteEventCallback(const Polaroid::Event& event);

		// Description
		void UpdateDescription(WindowDescription& description);
		const WindowDescription RetrieveDescription() const { return m_Description; }

		// Retrievals
		const HINSTANCE& RetrieveHINSTANCE() const { return m_hInstance; }
		const HWND& RetrieveHWND() const { return m_hwHandle; }

	private:
		wchar_t* ConvertToLPCWSTR(const char* charArray);

	private:
		std::string m_Title = "Polaroid";
		bool m_IsDestroyed = false;

		// Window Description
		EventQueue* m_EventQueue;
		WindowDescription m_Description;

		// Application Instance
		HINSTANCE m_hInstance;

		// Window Handle
		HWND m_hwHandle; // The Windows window is an opaque handle to an internal Windows data structure that corresponds to a window and consumes system resources when present. It is identified by a window handle (HWND).
	};
}