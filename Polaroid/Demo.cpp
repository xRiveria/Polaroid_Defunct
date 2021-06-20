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

	std::shared_ptr<Polaroid::Window> demoWindow = std::make_shared<Polaroid::Window>();
	Polaroid::InitializePlatformData(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	Polaroid::EventQueue eventQueue;
	Polaroid::WindowDescription demoWindowDescription;
	demoWindowDescription.m_Name = "Polaroid";
	demoWindowDescription.m_Title = "Polaroid Window";
	demoWindowDescription.m_IsVisible = true;
	demoWindowDescription.m_Width = 1280;
	demoWindowDescription.m_Height = 720;

	demoWindow->Create(demoWindowDescription, eventQueue); // Event Queue

	bool demoEngineRunning = true;

	while (demoEngineRunning)
	{
		// Application Logic
		
		// Window Updates
		eventQueue.Tick();

		while (!eventQueue.Empty())
		{
			const Polaroid::Event event = eventQueue.Front();
			eventQueue.Pop();

			// Hook into Polaroid events here.
			switch (event.RetrieveEventType())
			{
				case Polaroid::EventType::MouseMoved:
					//Polaroid::MouseMoveData* mouseMoveData = static_cast<Polaroid::MouseMoveData*>(event.RetrieveEventData());
					break;

				case Polaroid::EventType::Close:
					POLAROID_INFO("Window closed.");
					break;

				default:
					//POLAROID_INFO("Event received.");
					break;
			}
		}

		if (demoWindow->IsDestroyed()) // Naturally, we can also reuse the pointer and create the window again.
		{
			demoEngineRunning = false;
		}
	}

	#ifdef POLAROID_DEBUG
	FreeConsole();	
	fclose(pCout);
	#endif
}

#endif