#include "Polaroid.h"

#ifdef POLAROID_WIN32

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	#ifdef POLAROID_DEBUG	
	AllocConsole();
	FILE* pCout;
	freopen_s(&pCout, "CONOUT$", "w+", stdout);
	std::cout.clear();
	#endif

	//std::shared_ptr<Polaroid::Window> demoWindow;
	Polaroid::InitializePlatformData(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	Polaroid::WindowDescription demoWindowDescription;
	demoWindowDescription.m_Name = "Polaroid";
	demoWindowDescription.m_Title = "Editor Example";
	demoWindowDescription.m_IsVisible = true;
	demoWindowDescription.m_Width = 1920;
	demoWindowDescription.m_Height = 1080;

	//demoWindow->Create(demoWindowDescription); // Event Queue

	bool demoEngineRunning = true;

	while (demoEngineRunning)
	{
		// Application Logic
		
		/// Window Updates


		//if (demoWindow->IsDestroyed()) // Naturally, we can also reuse the pointer and create the window again.
		//{
		//	demoEngineRunning = false;
		//}
	}

	#ifdef POLAROID_DEBUG
	FreeConsole();	
	fclose(pCout);
	#endif
}

#endif