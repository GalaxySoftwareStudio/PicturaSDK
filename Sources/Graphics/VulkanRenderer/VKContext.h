#pragma once
#include "Graphics/GPUContext.h"
#include "VKInstance.h"
#include "VKDevice.h"

namespace Pictura::Graphics::Vulkan
{
    class VKContext : public GPUContext
    {
    public:
        VKContext();
        ~VKContext();

    public:
        virtual bool CreateContext();
        virtual void DestroyContext();

    public:
        VKInstance *VulkanInstance = nullptr;
        VKDevice *DefaultPhysicalDevice;

        Vector<VKDevice> PhysicalDevices = {};
    };
}