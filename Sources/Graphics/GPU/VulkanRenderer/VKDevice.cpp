#include "PicturaPCH.h"
#include "VKDevice.h"

namespace Pictura::Graphics::Vulkan
{
    void VKDevice::FindQueueFamilies()
    {
        //Find queue family with graphics support
        //Check if a transfer queue is necessary to copy vertices to the gpu or can a graphics queue handle that?
        Vector<vk::QueueFamilyProperties> queueFamilies = GetVulkanDevice().getQueueFamilyProperties();

        Debug::Log::GetFrameworkLog().Debug("PhysicalDevice has " + Types::ToString(queueFamilies.size()) + " queue families");

        bool foundGraphicsQueueFamily = false;
        bool foundPresentQueueFamily = false;

        for (uint32_t i = 0; i < queueFamilies.size(); i++)
        {
            vk::Bool32 presentSupport = m_PhysicalDevice.getSurfaceSupportKHR(i, m_VulkanSurface);
            if (queueFamilies[i].queueCount > 0 && queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics)
            {
                m_GraphicsQueueFamily = i;
                foundGraphicsQueueFamily = true;

                if (presentSupport)
                {
                    m_PresentQueueFamily = i;
                    foundPresentQueueFamily = true;
                    break;
                }
            }

            if (!foundPresentQueueFamily && presentSupport)
            {
                m_PresentQueueFamily = i;
                foundPresentQueueFamily = true;
            }
        }

        if (foundGraphicsQueueFamily)
        {
            Debug::Log::GetFrameworkLog().Debug("Queue family #" + Types::ToString(m_GraphicsQueueFamily) + " supports graphics");

            if (foundPresentQueueFamily)
            {
                Debug::Log::GetFrameworkLog().Debug("queue family #" + Types::ToString(m_PresentQueueFamily) + " supports presentation");
            }
            else
            {
                throw GPUException("Could not find a valid queue family with present support");
                return;
            }
        }
        else
        {
            throw GPUException("Could not find a valid queue family with graphics support");
            return;
        }
    }

    void VKDevice::CreateLogicalDevices()
    {
        float queuePriority = 1.f;

        vk::DeviceQueueCreateInfo queueCreateInfo[2] = {};

        queueCreateInfo[0] = vk::DeviceQueueCreateInfo{{}, m_GraphicsQueueFamily, 1, &queuePriority};
        queueCreateInfo[1] = vk::DeviceQueueCreateInfo{{}, m_PresentQueueFamily, 1, &queuePriority};

        const char *deviceExtensions = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

        VkDeviceCreateInfo deviceCreateInfo = {};

        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pQueueCreateInfos = ReinterpretCastTo<const VkDeviceQueueCreateInfo *>(queueCreateInfo);
        deviceCreateInfo.queueCreateInfoCount = (m_GraphicsQueueFamily == m_PresentQueueFamily) ? 1 : 2;
        deviceCreateInfo.enabledExtensionCount = 1;
        deviceCreateInfo.ppEnabledExtensionNames = &deviceExtensions;

        m_LogicalDevice = m_PhysicalDevice.createDevice(deviceCreateInfo);

        GraphicsQueue = m_LogicalDevice.getQueue(m_GraphicsQueueFamily, 0);
        PresentationQueue = m_LogicalDevice.getQueue(m_PresentQueueFamily, 0);
    }

    void VKDevice::CreateSemaphores()
    {
        ImageAvailablesSemaphore = m_LogicalDevice.createSemaphore({});
        RenderingFinishedSemaphore = m_LogicalDevice.createSemaphore({});
    }
}