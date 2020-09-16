#pragma once
#include "Graphics/GPU/GPUCommandQueue.h"
#include "VKSwapchain.h"

namespace Pictura::Graphics::Vulkan
{
    class VKCommandQueue : public GPUCommandQueue
    {
    public:
        VKCommandQueue(VKSwapchain &swapchain);
        ~VKCommandQueue();

    public:
        virtual void CreateCommandQueue();
        virtual void Begin();
        virtual void End();

    public:
        Vector<vk::CommandBuffer> &GetCommandBuffers() { return m_commandBuffers; }
        vk::CommandPool &GetCommandPool() { return m_commandPool; }

    public:
        VKSwapchain *VulkanSwapchain = nullptr;

    private:
        Vector<vk::CommandBuffer> m_commandBuffers;
        vk::CommandPool m_commandPool;
    };
}