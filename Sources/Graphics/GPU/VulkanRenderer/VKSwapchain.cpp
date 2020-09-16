#include "PicturaPCH.h"
#include "VKSwapchain.h"

namespace Pictura::Graphics::Vulkan
{
    VKSwapchain::VKSwapchain(VKDevice &vkDevice, ComplexHandle &vkSurface)
    {
        VulkanDevice = &vkDevice;
        VulkanSurface = &vkSurface;
    }

    VKSwapchain::~VKSwapchain()
    {
    }

    bool VKSwapchain::CheckSwapchainSupport()
    {
        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(VulkanDevice->GetVulkanDevice(), nullptr, &extensionCount, nullptr);

        if (extensionCount == 0)
        {
            throw Exceptions::GPUException("PhysicalDevice has no extensions loaded !");
            return false;
        }

        std::vector<VkExtensionProperties> deviceExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(VulkanDevice->GetVulkanDevice(), nullptr, &extensionCount, deviceExtensions.data());

        for (const auto &extension : deviceExtensions)
        {
            if (strcmp(extension.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0)
            {
                Debug::Log::GetFrameworkLog().Debug("PhysicalDevice supports swapchains");
                return true;
            }
        }

        Debug::Log::GetFrameworkLog().Warning("PhysicalDevice doesn't support swapchains");
        return false;
    }

    bool VKSwapchain::CreateSwapchain()
    {
        try
        {
            // Find surface capabilities
            if (!CheckSwapchainSupport())
            {
                return false;
            }
            vk::SurfaceCapabilitiesKHR surfaceCapabilities = VulkanDevice->GetVulkanDevice().getSurfaceCapabilitiesKHR((VkSurfaceKHR)*VulkanSurface);

            //Find surface formats
            Vector<vk::SurfaceFormatKHR> surfaceFormats = VulkanDevice->GetVulkanDevice().getSurfaceFormatsKHR((VkSurfaceKHR)*VulkanSurface);

            // Find supported present modes
            Vector<vk::PresentModeKHR> presentModes = VulkanDevice->GetVulkanDevice().getSurfacePresentModesKHR((VkSurfaceKHR)*VulkanSurface);

            // Determine number of images for swap chain
            uint32_t imageCount = surfaceCapabilities.minImageCount + 1;
            if (surfaceCapabilities.maxImageCount != 0 && imageCount > surfaceCapabilities.maxImageCount)
            {
                imageCount = surfaceCapabilities.maxImageCount;
            }
            Debug::Log::GetFrameworkLog().Debug("Using " + Types::ToString(imageCount) + " images for swap chain");

            // Select a surface format
            vk::SurfaceFormatKHR surfaceFormat = GetSurfaceFormat(surfaceFormats);
            SwapchainImageFormat = surfaceFormat.format;

            // Select swap chain size
            VkExtent2D swapChainExtent = GetSwapExtent(surfaceCapabilities);

            // Check if swap chain supports being the destination of an image transfer
            if (!(surfaceCapabilities.supportedUsageFlags & vk::ImageUsageFlagBits::eTransferDst))
            {
                throw GPUException("Swapchain image does not support ImageTransferDestination usage !");
                return false;
            }

            // Determine transformation to use (preferring no transform)
            vk::SurfaceTransformFlagBitsKHR surfaceTransform;
            if (surfaceCapabilities.supportedTransforms & vk::SurfaceTransformFlagBitsKHR::eIdentity)
            {
                surfaceTransform = vk::SurfaceTransformFlagBitsKHR::eIdentity;
            }
            else
            {
                surfaceTransform = surfaceCapabilities.currentTransform;
            }

            // Choose presentation mode (preferring triple buffering)
            vk::PresentModeKHR presentMode = GetPresentMode(presentModes);

            // Create swapchain object
            vk::SwapchainCreateInfoKHR swapchainCreateInfo({}, (VkSurfaceKHR)VulkanSurface, imageCount, surfaceFormat.format,
                                                           surfaceFormat.colorSpace, swapChainExtent, 1,
                                                           vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eTransferDst,
                                                           vk::SharingMode::eExclusive, nullptr, surfaceTransform, vk::CompositeAlphaFlagBitsKHR::eOpaque,
                                                           presentMode, true);

            VulkanSwapchain = VulkanDevice->GetLogicalDevice().createSwapchainKHR(swapchainCreateInfo);

            // Store the images used by the swap chain
            // Note: these are the images that swap chain image indices refer to
            // Note: actual number of images may differ from requested number, since it's a lower bound
            uint32_t actualImageCount = 0;
            SwapchainImages = VulkanDevice->GetLogicalDevice().getSwapchainImagesKHR(VulkanSwapchain);
            if (SwapchainImages.size() == 0)
            {
                throw GPUException("Failed to acquire swapchain images !");
                return false;
            }

            SwapchainImages.resize(actualImageCount);

            Debug::Log::GetFrameworkLog().Success("Vulkan swapchain [@" + Types::ToString(this) + "] created successfully !");
            return true;
        }
        catch (const std::exception &e)
        {
            throw Exceptions::GPUException("Vulkan swapchain creation failed !\n" + String(e.what()));
            return false;
        }
    }

    void VKSwapchain::CreateImageViews()
    {
        try            
        {
            ImageViews.resize(SwapchainImages.size());
            for (size_t i = 0; i < SwapchainImages.size(); i++)
            {
                vk::ImageViewCreateInfo createInfo({}, SwapchainImages[i], vk::ImageViewType::e2D, SwapchainImageFormat,
                                                {vk::ComponentSwizzle::eIdentity,
                                                    vk::ComponentSwizzle::eIdentity,
                                                    vk::ComponentSwizzle::eIdentity,
                                                    vk::ComponentSwizzle::eIdentity}, {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});

                ImageViews = VulkanDevice->GetLogicalDevice().createImageView(createInfo);
            }
        }
        catch(const std::exception& e)
        {
            throw GPUException("Failed to create swapchain image views !\n" + String(e.what());
        }
    }
}