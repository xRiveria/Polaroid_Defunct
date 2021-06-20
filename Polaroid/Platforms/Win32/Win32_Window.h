#pragma once
#include "../Commons/PlatformData.h"
#include "../Commons/WindowDescription.h"
#include "../Commons/EventQueue.h"
#include <Windows.h>
#include <functional>
#include <unordered_map>

// Thread local data exclusively belongs to the current thread and behaves like static data. It is tied to the lifetime of the thread. Thread local data is called thread local storage.
static thread_local Polaroid::Window* g_WindowInCreation = nullptr;
static thread_local std::unordered_map<HWND, Polaroid::Window*> g_HWNDMap = {};

namespace Polaroid
{
	struct WindowDescription;

	class Window
	{
	public:
		Window();
		~Window();

		// Window Actions
		bool Create(WindowDescription& windowDescription, EventQueue& eventQueue);
		void SetSize(const uint32_t newWidth, const uint32_t newHeight);
		void Maximize();
		void Minimize();

		void SetTitle(const std::string& newTitle);
		const std::string& RetrieveTitle() const { m_Title; }

		const bool IsDestroyed() const { return m_IsDestroyed; }
		void Destroy();

		// Description
		void UpdateDescription(WindowDescription& description);
		const WindowDescription RetrieveDescription() const { return m_Description; }

		// Executes an event callback asynchonously. Use this for non-blocking events (resizing while rendering, etc).
		void ExecuteEventCallback(const Polaroid::Event& event);

		// Application-defined function that processes messages sent to a window. The WNDPROC type defines a pointer to this callback function.
		static LRESULT CALLBACK WindowProcStatic(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); // wParam and lParam contain additional message information that depend on the value of "msg".
		LRESULT WindowProc(UINT msg, WPARAM wParam, LPARAM lParam);

		// Retrievals
		const HINSTANCE& RetrieveHINSTANCE() const { return m_HINSTANCE; }

		void SetHWND(HWND newHWND) { m_HWND = newHWND; }
		const HWND& RetrieveHWND() const { return m_HWND; }

		std::function<void(const Polaroid::Event& event)> m_EventCallback;

	private:
		std::wstring ConvertToLPCWSTR(const std::string& string);

	private:
		std::string m_Title = "Polaroid";
		bool m_IsDestroyed = false;

		// Window Description
		EventQueue* m_EventQueue;
		WindowDescription m_Description;

		// Application Instance
		HINSTANCE m_HINSTANCE;

		// Window Handle
		HWND m_HWND; // The Windows window is an opaque handle to an internal Windows data structure that corresponds to a window and consumes system resources when present. It is identified by a window handle (HWND).
	};
}
