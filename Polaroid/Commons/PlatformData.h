#pragma once
#include "PolaroidDefinitions.h"
#ifdef POLAROID_WIN32
#include <Windows.h>
#endif

/*
	Contains initialization data for our respective windows. The parameters are named 1:1 with their native platform counterparts. 
	The information here is then passed into the Window class for creation.

	- ARGUMENTS: Native argument declarations.
	- ARGUMENTS_DEFINITION: Native arguments without declarations.
*/

namespace Polaroid
{
	struct PlatformData
	{
		#ifdef POLAROID_WIN32

		#define ARGUMENTS HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
		#define ARGUMENTS_DEFINITION hInstance, hPrevInstance, lpCmdLine, nCmdShow

		HINSTANCE m_HINSTANCE;
		HINSTANCE m_hPrevInstance;
		LPSTR	  m_lpCmdLine;
		int		  m_nCmdShow;

		PlatformData() = default;
		PlatformData(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) : m_HINSTANCE(hInstance), m_hPrevInstance(hPrevInstance), m_lpCmdLine(lpCmdLine), m_nCmdShow(nCmdShow)
		{

		}

		#elif POLAROID_COCOA

		#endif
	};

	bool InitializePlatformData(ARGUMENTS);
	const PlatformData& RetrievePlatformData();
}