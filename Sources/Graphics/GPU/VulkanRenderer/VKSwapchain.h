#pragma once
#include "Graphics/GPU/GPUSwapchain.h"
#include "VKDevice.h"

namespace Pictura::Graphics::Vulkan
{
    class VKSwapchain : public GPUSwapchain
    {
    public:
        VKSwapchain(VKDevice &vkDevice, ComplexHandle &vkSurface);
        ~VKSwapchain();

    public:
        virtual bool CheckSwapchainSupport();
        virtual bool CreateSwapchain();

    private:
        void CreateImageViews();

    public:
        Vector<vk::Image> &GetSwapchainImages() { return SwapchainImages; }

    private:
        vk::SurfaceFormatKHR GetSurfaceFormat(const Vector<vk::SurfaceFormatKHR> &availableFormats)
        {
            // We can either choose any format
            if (availableFormats.size() == 1 && availableFormats[0].format == vk::Format::eUndefined)
            {
                return vk::SurfaceFormatKHR{vk::Format::eR8G8B8A8Unorm, vk::ColorSpaceKHR::eSrgbNonlinear};
            }

            // Select the standard format (If available)
            for (const auto &availableSurfaceFormat : availableFormats)
            {
                if (availableSurfaceFormat.format == vk::Format::eR8G8B8A8Unorm)
                {
                    return availableSurfaceFormat;
                }
            }

            //Fall back to the first available one
            return availableFormats[0];
        }

        vk::Extent2D GetSwapExtent(const vk::SurfaceCapabilitiesKHR &surfaceCapabilities)
        {
            if (surfaceCapabilities.currentExtent.width == -1)
            {
                VkExtent2D swapChainExtent = {};

                swapChainExtent.width = min(max(640, surfaceCapabilities.minImageExtent.width), surfaceCapabilities.maxImageExtent.width);
                swapChainExtent.height = min(max(480, surfaceCapabilities.minImageExtent.height), surfaceCapabilities.maxImageExtent.height);

                return swapChainExtent;
            }
            else
            {
                return surfaceCapabilities.currentExtent;
            }
        }

        vk::PresentModeKHR GetPresentMode(const Vector<vk::PresentModeKHR> PresentModes)
        {
            for (const auto &presentMode : PresentModes)
            {
                if (presentMode == vk::PresentModeKHR::eMailbox)
                {
                    return presentMode;
                }
            }

            // If mailbox is unavailable, fall back to FIFO
            return vk::PresentModeKHR::eFifo;
        }

    private:
        vk::SwapchainKHR VulkanSwapchain;
        vk::Format SwapchainImageFormat;
        Vector<vk::Image> SwapchainImages;
        Vector<vk::ImageView> ImageViews;

    public:
        VKDevice *VulkanDevice = nullptr;
        ComplexHandle *VulkanSurface = nullptr;
    };
}