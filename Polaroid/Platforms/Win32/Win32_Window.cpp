#include "Win32_Window.h"

namespace Polaroid
{
	Window::Window()
	{
		
	}

	Window::~Window()
	{

	}

	// A WndProc (Windows Procedure) must be created and is used to determine how your application will respond to various events. It may very well be called an Event Handler. After all, it responds to events!
	void Window::Create(const WindowDescription& windowDescription, EventQueue& eventQueue)
	{
		m_EventQueue = &eventQueue;
		const PlatformData& platformData = RetrievePlatformData();

		m_hInstance = platformData.m_hInstance;                   // A hInstance is used to identify the executable (EXE) when it is loaded in memory. Also known as a "handle to an instance". It is used by Windows as a reference to your application for event handling, message processing and various other duties.
		HINSTANCE hPrevInstance = platformData.m_hPrevInstance;   // Tends to always be null. Used in the past to detect previous instances of an application to get yourself up from the ground faster. See: https://devblogs.microsoft.com/oldnewthing/20040615-00/?p=38873
		LPSTR lpCmdLine = platformData.m_lpCmdLine;               // A pointer string that is used to hold any command-line arguments that may have been specified when the application began. For example, if the user opened the Run application and typed myapp.exe "myparameter 123", then lpCmdLine would be "myparameter 123".
		int nCmdShow = platformData.m_nCmdShow;                   // Used to determine how your application's window will be displayed once it begins executing.

		m_Description = windowDescription;

		// Window class creation.
	}

	void Window::SetSize(const uint32_t newWidth, const uint32_t newHeight)
	{
		RECT lpRect;

		if (GetWindowRect(m_hwHandle, &lpRect))
		{
			SetWindowPos(m_hwHandle, nullptr, lpRect.left, lpRect.top, newWidth, newHeight, 0);
		}
	}

	void Window::Maximize()
	{

	}

	void Window::Minimize()
	{

	}

	void Window::SetTitle(const std::string& newTitle)
	{
		if (wchar_t* titleInWideString = ConvertToLPCWSTR(newTitle.c_str()))
		{
			SetWindowText(m_hwHandle, titleInWideString);
			delete titleInWideString;
			m_Title = newTitle;
		}
	}

	void Window::Destroy()
	{
		if (m_hwHandle != nullptr)
		{
			DestroyWindow(m_hwHandle);
			m_hwHandle = nullptr;
			m_IsDestroyed = true;
		}
	}

	void Window::ExecuteEventCallback(const Polaroid::Event& event)
	{
	}

	void Window::UpdateDescription(WindowDescription& description)
	{
	}

	wchar_t* Window::ConvertToLPCWSTR(const char* charArray)
	{
		wchar_t* wideString = new wchar_t[4096];
		MultiByteToWideChar(CP_ACP, 0, charArray, -1, wideString, 4096);
		return wideString;
	}
}