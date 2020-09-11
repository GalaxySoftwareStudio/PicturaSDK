#pragma once
#include "Graphics/GPUDevice.h"
#include "vulkan/vulkan.hpp"
#include "vulkan/vma.h"

namespace Pictura::Graphics::Vulkan
{
    class VKDevice : public GPUDevice
    {
    public:
        VKDevice() {}
        VKDevice(vk::PhysicalDevice device) : m_PhysicalDevice(device)
        {
            m_DeviceProperties = device.getProperties();
            m_DeviceFeatures = device.getFeatures();
            m_DeviceMemoryProperties = device.getMemoryProperties();

            m_PhysicalDeviceLimits = m_DeviceProperties.limits;
            m_DeviceName = String(m_DeviceProperties.deviceName.begin(), m_DeviceProperties.deviceName.end());
        
            m_apiVersion = m_DeviceProperties.apiVersion;
        }

        ~VKDevice() {}

    public:
        vk::PhysicalDevice &GetVulkanDevice() { return m_PhysicalDevice; }
        vk::PhysicalDeviceProperties &GetProperties() { return m_DeviceProperties; }
        vk::PhysicalDeviceLimits &GetDeviceLimits() { return m_PhysicalDeviceLimits; }
        vk::PhysicalDeviceFeatures &GetDeviceFeatures() { return m_DeviceFeatures; }
        vk::PhysicalDeviceMemoryProperties &GetMemoryProperties() { return m_DeviceMemoryProperties; }

        uint32 &GetApiVersion() { return m_apiVersion; }
        String &GetName() { return m_DeviceName; }

    private:
        uint32 m_apiVersion;
        String m_DeviceName;
        vk::PhysicalDevice m_PhysicalDevice;
        vk::PhysicalDeviceLimits m_PhysicalDeviceLimits;
        vk::PhysicalDeviceProperties m_DeviceProperties;
        vk::PhysicalDeviceFeatures m_DeviceFeatures;
        vk::PhysicalDeviceMemoryProperties m_DeviceMemoryProperties;
    };
} // namespace Pictura::Graphics::Vulkan
