#pragma once
#include "Graphics/GPU/GPUContext.h"
#include "VKInstance.h"
#include "VKDevice.h"
#include "VKSwapchain.h"
#include "VKShader.h"

namespace Pictura::Graphics::Vulkan
{
    class VKContext : public GPUContext
    {
    public:
        VKContext();
        ~VKContext();

    public:
        virtual bool CreateContext(Handle windowHandle);
        virtual void DestroyContext();

        virtual void InitSurface(Handle WindowHandle);
        virtual void CreateGraphicsPipeline();

        virtual void PrintDebugInformations();

    private:
        vk::ShaderModule CreateShaderModule(const Vector<uint32> &code);

    public:
        VKInstance *VulkanInstance = nullptr;
        VKSwapchain *VulkanSwapchain = nullptr;
        VKDevice *DefaultPhysicalDevice = nullptr;

        Vector<VKDevice> PhysicalDevices = {};
    };
}