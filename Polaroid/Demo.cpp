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

	Polaroid::InitializePlatformData(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	while (true)
	{

	}

	#ifdef POLAROID_DEBUG
	FreeConsole();	
	fclose(pCout);
	#endif
}

#endif