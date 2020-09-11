#pragma once

#include <memory>

//Platform detection
#ifdef _WIN32
    #ifdef _WIN64
        #define PLATFORM_WINDOWS
        #define VK_USE_PLATFORM_WIN32_KHR
        #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
            #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
        #endif
    #else
        #error "x86 Builds are not supported by Pictura!"
#endif

#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #define PLATFORM_IOS
        #define VK_USE_PLATFORM_IOS_MVK
    #elif TARGET_OS_IPHONE == 1
        #define PLATFORM_IOS
        #define VK_USE_PLATFORM_IOS_MVK
    #elif TARGET_OS_MAC == 1
        #define PLATFORM_MACOS
        #define VK_USE_PLATFORM_MACOS_MVK
    #else
        #error "Unknown Apple platform!"
    #endif
#elif defined(__ANDROID__)
    #define PLATFORM_ANDROID
    #define VK_USE_PLATFORM_ANDROID_KHR
#elif defined(__linux__)
    #define PLATFORM_LINUX
    #define VK_USE_PLATFORM_XCB_KHR
    #define VK_USE_PLATFORM_WAYLAND_KHR
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

#define VK_ENABLE_BETA_EXTENSIONS