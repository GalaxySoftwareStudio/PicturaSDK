#pragma once

#include "PlatformMacro.h"

#ifdef PLATFORM_WINDOWS
	#include <Windows.h>
	#ifdef __cplusplus
		#include <wrl.h>
		using namespace Microsoft::WRL;
	#endif
#endif

#include "TypesAliases.h"