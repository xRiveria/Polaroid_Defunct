#include "PlatformData.h"
#include <iostream>

namespace Polaroid
{
	namespace Data
	{
		PlatformData m_PlatformData;
	}

	bool InitializePlatformData(ARGUMENTS)
	{		
		Data::m_PlatformData = PlatformData(ARGUMENTS_DEFINITION);
		POLAROID_INFO("Initialized Platform Data.");
		return true;
	}

	const PlatformData& RetrievePlatformData()
	{
		return Data::m_PlatformData;
	}
}