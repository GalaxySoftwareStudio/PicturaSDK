#pragma once
#include "Core/CoreFramework.h"
#include "Core/Exceptions/Exceptions.h"

namespace Pictura::Graphics
{
    class GPUSwapchain
    {
    public:
        GPUSwapchain() {}
        virtual ~GPUSwapchain() {}

    public:
        virtual bool CheckSwapchainSupport() = 0;
        virtual bool CreateSwapchain() = 0;
    };
}