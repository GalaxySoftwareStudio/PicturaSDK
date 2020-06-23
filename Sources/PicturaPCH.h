#pragma once
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <chrono>
#include <ctime>
#include <time.h>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include <thread>
#include <mutex>
#include <shared_mutex>

#include "Core/PlatformMacro.h"

#ifdef PLATFORM_WINDOWS
	#include <Windows.h>
	#ifdef __cplusplus
		#include <wrl.h>
		using namespace Microsoft::WRL;
	#endif
#endif