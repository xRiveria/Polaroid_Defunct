#include "Win32_Window.h"
#include <ShObjIdl_core.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

// To be safe, use Windows data types whenever possible. This is because their range/formats are what Windows functions rely on. See: https://stackoverflow.com/questions/2995251/why-in-c-do-we-use-dword-rather-than-unsigned-int

HBRUSH g_hBrush = CreateSolidBrush(RGB(30, 30, 30));

namespace Polaroid
{
	Window::Window()
	{
		m_HWND = nullptr;
	}

	Window::~Window()
	{
		if (m_HWND != nullptr)
		{
			Destroy();
		}
	}

	// A WndProc (Windows Procedure) must be created and is used to determine how your application will respond to various events. It may very well be called an Event Handler. After all, it responds to events!
	bool Window::Create(WindowDescription& windowDescription, EventQueue& eventQueue)
	{
		m_EventQueue = &eventQueue;
		const PlatformData& platformData = RetrievePlatformData();

		m_HINSTANCE = platformData.m_HINSTANCE;                   // A hInstance is used to identify the executable (EXE) when it is loaded in memory. Also known as a "handle to an instance". It is used by Windows as a reference to your application for event handling, message processing and various other duties.
		HINSTANCE hPrevInstance = platformData.m_hPrevInstance;   // Tends to always be null. Used in the past to detect previous instances of an application to get yourself up from the ground faster. See: https://devblogs.microsoft.com/oldnewthing/20040615-00/?p=38873
		LPSTR lpCmdLine = platformData.m_lpCmdLine;               // A pointer string that is used to hold any command-line arguments that may have been specified when the application began. For example, if the user opened the Run application and typed myapp.exe "myparameter 123", then lpCmdLine would be "myparameter 123".
		int nCmdShow = platformData.m_nCmdShow;                   // Used to determine how your application's window will be displayed once it begins executing.

		m_Description = windowDescription;
		const LPCWSTR className = ConvertToLPCWSTR(m_Description.m_Name).c_str();

		// Contains window class information. It is used with the RegisterClassEx function.
		WNDCLASSEX wndClass = {};
		wndClass.cbSize = sizeof(WNDCLASSEX);					  // The size in bytes of this structure. Set this to sizeof(WNDCLASSEX).
		wndClass.style = CS_HREDRAW | CS_VREDRAW;				  // Class style(s). CS_VREDRAW and CS_HREDRAW: Redraws the entire window if a movement or size adjustment changes the width/height of the client area respectively. 
		wndClass.lpfnWndProc = Window::WindowProcStatic;		  // A pointer to the window procedure. 
		wndClass.cbClsExtra = 0;								  // The number of extra bytes to allocate following the window-class structure. The system initializes the bytes to zero.
		wndClass.cbWndExtra = WS_EX_NOPARENTNOTIFY;				  // The number of extra bytes to allocate following the window instance. The system initializes the bytes to zero. We are setting it so that the WM_PARENTNOTIFY message isn't sent to the parent window on creation/destruction.
		wndClass.hInstance = m_HINSTANCE;						  // A handle to the instance that contains the window procedure for the class.
		wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);		  // Handle to an icon resource. If NULL, the sytstem provides a default icon.
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);			  // Handle to a cursor resource. If NULL, an application must explictly set the cursor shape whenever the mouse moves into the application's window.
		wndClass.hbrBackground = g_hBrush;						  // Handle to the class background brush. It can be a color value or a handle to the brush to be used for painting the background.
		wndClass.lpszMenuName = NULL;							  // Pointer to a null-terminated character string that specifies the resource name of the class menu, as the name appears in the resource file.
		wndClass.lpszClassName = className; // Pointer to a null-terminated string.
		wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);			  // A handle to a small icon that is associated with the window class. If this is NULL, the system searches the icon resource specified by the hIcon member for an icon of the appropriate size to use as the small icon.

		if (!RegisterClassEx(&wndClass)) // Registers a window class for subsequent use in calls to the CreateWindow or CreateWindowEx function. 
		{
			return false;
		}

		int screenWidth = GetSystemMetrics(SM_CXSCREEN);		  // Width of the primary display monitor in pixels.
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);		  // Height of the primary display monitor in pixels.

		if (m_Description.m_IsFullscreen)
		{
			DEVMODE screenSettings; // Contains information about the initialization and environment of a printer/display device.
			memset(&screenSettings, 0, sizeof(screenSettings));
			screenSettings.dmSize = sizeof(screenSettings);		  // Specifies the size, in bytes, of the DEVMODE structure. 
			screenSettings.dmPelsWidth = screenWidth;			  // Specifies the width, in pixels of the visible device surface. Display drivers use this member, for example, in the ChangeDisplaySettings function. 
			screenSettings.dmPelsHeight = screenHeight;			  // Specifies the height, in pixels of the visible device surface. Display drivers use this member, for example, in the ChangeDisplaySettings function.
			screenSettings.dmBitsPerPel = 32;					  // Specifies the color resolution, in bits per pixel, of the display device. For example, 4 bits for 16 colors, 16 bits for 65,536 colors and so on. Display drivers use this member, for example, in the ChangeDisplaySettings function.
			screenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT; // Specifies whether certain members of the DEVMODE structure has been initialized. If initialized, its corresponding bit is set, otherwise the bit is clear. 

			if ((m_Description.m_Width != screenWidth) && (m_Description.m_Height != screenHeight))
			{
				/*
					Changes the settings of the default display device to the specified graphics mode. We pass in our DEVMODE struct that describes the new graphics mode in the first parameter.
					For the second parameter, we pass in flags that will indicate how the graphics mode should be changed. CDS_FULLSCREEN states that the mode is temporary in nature. If you change to and from another desktop, this mode will not be reset.
				*/
				if (ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) // If DISP_CHANGE_SUCCESSFUL is returned, the settings change was successful.
				{
					// if (MessageBox(NULL, "Fullscreen mode not supported.\n Switch to window mode?", "Error", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
					// {
					//
					// }
				}
			}
		}

		// DWORDs are an unsigned, 32-bit unit of data. Think of it as a mask.
		DWORD dwExStyle = 0;
		DWORD dwStyle = 0;

		// See flag definitions here: https://docs.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles.
		if (m_Description.m_IsFullscreen)
		{
			dwExStyle = WS_EX_APPWINDOW;
			dwStyle = WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN; // Specifies that the window is a pop-up window, is initially visible, clips child windows relative to each other and excludes the area occupied by child windows when drawing occurs within the parent window.
		}
		else
		{
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; // Window has a border with a raised edge.
			dwStyle = WS_SYSMENU | WS_CAPTION | WS_OVERLAPPED | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX; // Specifies that the window has a window menu on its title bar, has a title bar (hence must be enabled for WS_SYSMENU), is an overlapped window (which has a title bar and border), has a sizing border and has a minimize/maximize button.
		}

		RECT windowRect;
		windowRect.left = m_Description.m_X;
		windowRect.top = m_Description.m_Y;
		windowRect.right = m_Description.m_IsFullscreen ? (long)screenWidth : (long)m_Description.m_Width;
		windowRect.bottom = m_Description.m_IsFullscreen ? (long)screenHeight : (long)m_Description.m_Height;

		// Calculates the required size of the window rectangle based on the desired size of the client rectangle. The window rectangle can then be passed to the CreateWindowEx function to create a window whose client area is the desired size.
		AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle); // Pointer to a Rect of the desired client area, window style of the window, indicates whether the window has a menu and the extended window style of the window.

		g_WindowInCreation = this;
		m_HWND = CreateWindowEx(0, className, ConvertToLPCWSTR(m_Description.m_Title).c_str(), dwStyle, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL, m_HINSTANCE, NULL);

		BOOL isNonClientRenderingEnabled{ TRUE };
		// Specifies window attributes for Desktop Window Manager (DWM) non-client rendering.
		DwmSetWindowAttribute(m_HWND, DWMWA_NCRENDERING_ENABLED, &isNonClientRenderingEnabled, sizeof(isNonClientRenderingEnabled)); // Discovers whether non-client rendering is enabled. Note that this refers to non-client area of a window, such as the title bar, menu bar or window frame. A WM_NCPAINT message is sent whenever such areas must be updated.

		if (!m_HWND)
		{
			POLAROID_ERROR("Failed to create window.");
		}

		// Windows loves its specification checks. Thus, we will continue making sure that m_HWND isn't nullptr or else Windows will throw warnings at us.

		if (!m_Description.m_IsFullscreen && m_HWND != nullptr) 
		{
			// Center on screen.
			uint32_t x = (GetSystemMetrics(SM_CXSCREEN) - windowRect.right) / 2;
			uint32_t y = (GetSystemMetrics(SM_CYSCREEN) - windowRect.bottom) / 2;
			SetWindowPos(m_HWND, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE); // Retains the current Z order and current size.		
		}

		if (m_Description.m_IsVisible && m_HWND != nullptr)
		{
			ShowWindow(m_HWND, SW_SHOW); // Activates the window and displays it in its current size and position. 
			SetForegroundWindow(m_HWND); // Brings the thread that created the specified window into the foreground and activates the window. Keyboard input is directed to the window, and various visual cues are changed for the user. See: https://stackoverflow.com/questions/3940346/foreground-vs-active-window/28643729
			SetFocus(m_HWND);			 // Sets the keyboard focus to the specified window.
		}

		// Blur behind?

		return true;
	}

	void Window::SetSize(const uint32_t newWidth, const uint32_t newHeight)
	{
		RECT lpRect;

		if (GetWindowRect(m_HWND, &lpRect))
		{
			SetWindowPos(m_HWND, nullptr, lpRect.left, lpRect.top, newWidth, newHeight, 0);
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
		SetWindowText(m_HWND, ConvertToLPCWSTR(newTitle).c_str());
		m_Title = newTitle;
	}

	void Window::Destroy()
	{
		if (m_HWND != nullptr)
		{
			DestroyWindow(m_HWND);
			m_HWND = nullptr;
			m_IsDestroyed = true;
		}
	}

	void Window::ExecuteEventCallback(const Polaroid::Event& event)
	{
		if (m_EventCallback)
		{
			m_EventCallback(event);
		}
	}


	void Window::UpdateDescription(WindowDescription& description)
	{
	}

	LRESULT CALLBACK Window::WindowProcStatic(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Window* currentWindow;

		if (g_WindowInCreation != nullptr)
		{
			g_HWNDMap.emplace(hwnd, g_WindowInCreation);
			g_WindowInCreation->SetHWND(hwnd);
			currentWindow = g_WindowInCreation;
			g_WindowInCreation = nullptr;
		}
		else
		{
			auto doesWindowExist = g_HWNDMap.find(hwnd);
			currentWindow = doesWindowExist->second;
		}

		return currentWindow->WindowProc(msg, wParam, lParam);
	}

	LRESULT Window::WindowProc(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		MSG message;
		message.hwnd = m_HWND;			// A handle to the window whose window procedure receives the message.
		message.lParam = lParam;		// Additional information about the message. The exact meaning depends on the value of the message member.
		message.wParam = wParam;		// Additional information about the message. The exact meaning depends on the value of the message member.
		message.message = msg;			// The message identifer. Applications can only use the low word; the high word is reserved by the system.
		message.time = 0;				// The time at which the message was posted.

		LRESULT result = m_EventQueue->PushEvent(message, this);
		if (result > 0)
		{
			return result;
		}

		// Calls the default window procedure to provide default processing for any window messages that an application does not process. This function ensures that every message is processed.
		return DefWindowProc(m_HWND, msg, wParam, lParam); // Internally returns an LRESULT which is inherently the result of the message processing and differs based on the message.
	}

	std::wstring Window::ConvertToLPCWSTR(const std::string& string) 
	{
		const int stringLength = static_cast<int>(string.length() + 1); // For null-terminated character.
		const int wideStringLength = MultiByteToWideChar(CP_ACP, 0, string.c_str(), stringLength, nullptr, 0);
		wchar_t* const wideStringBuffer = new wchar_t[wideStringLength];
		MultiByteToWideChar(CP_ACP, 0, string.c_str(), stringLength, wideStringBuffer, wideStringLength);
		std::wstring result(wideStringBuffer);
		delete[] wideStringBuffer;
		return result;
	}
}