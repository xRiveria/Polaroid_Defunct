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
		void Create(const WindowDescription& windowDescription);
		void SetSize(const uint32_t newWidth, const uint32_t newHeight);
		void Maximize();
		void Minimize();

		void SetTitle(const std::string& newTitle);
		const std::string& RetrieveTitle() const { m_Title; }

		const bool IsDestroyed() const { return m_IsDestroyed; }
		void Destroy();

	private:
		wchar_t* ConvertToLPCWSTR(const char* charArray);

	private:
		std::string m_Title = "Polaroid";
		bool m_IsDestroyed = false;

		// Application Instance
		HINSTANCE m_Instance;

		// Window Handle
		HWND m_Handle;
	};
}