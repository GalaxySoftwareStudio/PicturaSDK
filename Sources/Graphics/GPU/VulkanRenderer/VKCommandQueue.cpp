#include "PicturaPCH.h"
#include "VKCommandQueue.h"

namespace Pictura::Graphics::Vulkan
{
    VKCommandQueue::VKCommandQueue(VKSwapchain &swapchain) : VulkanSwapchain(&swapchain)
    {
    }

    VKCommandQueue::~VKCommandQueue()
    {
    }

    void VKCommandQueue::CreateCommandQueue()
    {
        try
        {
            // Create presentation command pool
            vk::CommandPoolCreateInfo poolCreateInfo({}, VulkanSwapchain->VulkanDevice->GetPresentQueueIndex());
            m_commandPool = VulkanSwapchain->VulkanDevice->GetLogicalDevice().createCommandPool(poolCreateInfo);

            m_commandBuffers.resize(VulkanSwapchain->GetSwapchainImages().size());

            vk::CommandBufferAllocateInfo allocateInfo(m_commandPool, vk::CommandBufferLevel::ePrimary, (uint32)VulkanSwapchain->GetSwapchainImages().size());
            m_commandBuffers = VulkanSwapchain->VulkanDevice->GetLogicalDevice().allocateCommandBuffers(allocateInfo);
        }
        catch (const std::exception &e)
        {
            throw GPUException("Failed to create a vulkan command pool !\n" + String(e.what()));
        }
    }

    void VKCommandQueue::Begin()
    {
    }

    void VKCommandQueue::End()
    {
    }
}