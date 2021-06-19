#include "Win32_Window.h"

// To be safe, use Windows data types whenever possible. This is because their range/formats are what Windows functions rely on. See :https://stackoverflow.com/questions/2995251/why-in-c-do-we-use-dword-rather-than-unsigned-int

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
	bool Window::Create(const WindowDescription& windowDescription, EventQueue& eventQueue)
	{
		m_EventQueue = &eventQueue;
		const PlatformData& platformData = RetrievePlatformData();

		m_HINSTANCE = platformData.m_HINSTANCE;                   // A hInstance is used to identify the executable (EXE) when it is loaded in memory. Also known as a "handle to an instance". It is used by Windows as a reference to your application for event handling, message processing and various other duties.
		HINSTANCE hPrevInstance = platformData.m_hPrevInstance;   // Tends to always be null. Used in the past to detect previous instances of an application to get yourself up from the ground faster. See: https://devblogs.microsoft.com/oldnewthing/20040615-00/?p=38873
		LPSTR lpCmdLine = platformData.m_lpCmdLine;               // A pointer string that is used to hold any command-line arguments that may have been specified when the application began. For example, if the user opened the Run application and typed myapp.exe "myparameter 123", then lpCmdLine would be "myparameter 123".
		int nCmdShow = platformData.m_nCmdShow;                   // Used to determine how your application's window will be displayed once it begins executing.

		m_Description = windowDescription;

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
		wndClass.lpszClassName = ConvertToLPCWSTR(m_Description.m_Name.c_str()); // Pointer to a null-terminated string.
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

		if (m_Description.m_IsFullscreen)
		{
			dwExStyle = WS_EX_APPWINDOW; // Forces a top-level window onto the taskbar when the window is visible.
			dwStyle = WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN; // Specifies that the window is a pop-up window, is initially visible, clips child windows relative to each other and excludes the area occupied by child windows when drawing occurs within the parent window.
		}
		else
		{

		}

		// Rect.


		// Create Window

		if (!m_HWND)
		{
			POLAROID_ERROR("Failed to create window.");
		}
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
		if (wchar_t* titleInWideString = ConvertToLPCWSTR(newTitle.c_str()))
		{
			SetWindowText(m_HWND, titleInWideString);
			m_Title = newTitle;
		}
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

	wchar_t* Window::ConvertToLPCWSTR(const char* charArray) 
	{
		wchar_t* wideString = new wchar_t[4096];
		MultiByteToWideChar(CP_ACP, 0, charArray, -1, wideString, 4096);
		return wideString;
	}
}