#pragma once

#include <memory>

//Operating system detection
#ifdef _WIN32
    #ifdef _WIN64
        #define PLATFORM_WINDOWS
    #else
        #error "x86 Builds are not supported!"
#endif

#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #define PLATFORM_IOS
    #elif TARGET_OS_IPHONE == 1
        #define PLATFORM_IOS
    #elif TARGET_OS_MAC == 1
        #define PLATFORM_MACOS
    #else
        #error "Unknown Apple platform!"
    #endif
#elif defined(__ANDROID__)
    #define PLATFORM_ANDROID
#elif defined(__linux__)
    #define PLATFORM_LINUX
#else
    #error "Unknown platform!"
#endif

#ifdef PICTURA_DEBUG
    #if defined(PLATFORM_WINDOWS)
        #define CORE_DEBUGBREAK() __debugbreak()
    #elif defined(PLATFORM_LINUX)
        #include <signal.h>
        #define CORE_DEBUGBREAK() raise(SIGTRAP)
    #else
        #warning "Platform doesn't support debugbreak yet!"
    #endif

    #define ENABLE_ASSERTS
#else
    #define CORE_DEBUGBREAK()
#endif