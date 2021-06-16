#include "Win32_Window.h"

namespace Polaroid
{
	Window::Window()
	{
		
	}

	void Window::Create(const WindowDescription& windowDescription)
	{

	}

	void Window::SetSize(const uint32_t newWidth, const uint32_t newHeight)
	{
		RECT lpRect;

		if (GetWindowRect(m_Handle, &lpRect))
		{
			SetWindowPos(m_Handle, nullptr, lpRect.left, lpRect.top, newWidth, newHeight, 0);
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
			SetWindowText(m_Handle, titleInWideString);
			delete titleInWideString;
			m_Title = newTitle;
		}
	}

	void Window::Destroy()
	{
		if (m_Handle != nullptr)
		{
			DestroyWindow(m_Handle);
			m_Handle = nullptr;
			m_IsDestroyed = true;
		}
	}

	wchar_t* Window::ConvertToLPCWSTR(const char* charArray)
	{
		wchar_t* wideString = new wchar_t[4096];
		MultiByteToWideChar(CP_ACP, 0, charArray, -1, wideString, 4096);
		return wideString;
	}
}