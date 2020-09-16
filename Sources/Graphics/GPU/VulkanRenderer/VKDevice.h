#pragma once
#include "Graphics/GPU/GPUDevice.h"
#include "vulkan/vulkan.hpp"
#include "vulkan/vma.h"

namespace Pictura::Graphics::Vulkan
{
    struct Version
    {
        Version()
            : vulkan_major(0), vulkan_minor(0), vulkan_patch(0) {}
        Version(uint32_t version)
            : Version()
        {
            *this = version;
        }

        Version &operator=(uint32_t version)
        {
            memcpy(this, &version, sizeof(uint32_t));
            return *this;
        }

        operator uint32_t() const
        {
            uint32_t result;
            memcpy(&result, this, sizeof(uint32_t));
            return result;
        }

        bool operator>=(const Version &other) const
        {
            return (operator uint32_t()) >= (other.operator uint32_t());
        }

        std::string toString() const
        {
            std::stringstream buffer;
            buffer << vulkan_major << "." << vulkan_minor << "." << vulkan_patch;
            return buffer.str();
        }

        const uint32_t vulkan_patch : 12;
        const uint32_t vulkan_minor : 10;
        const uint32_t vulkan_major : 10;
    };

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
            m_DeviceName.erase(std::remove(m_DeviceName.begin(), m_DeviceName.end(), '\n'), m_DeviceName.end());

            m_apiVersion = m_DeviceProperties.apiVersion;
            m_driverVersion = m_DeviceProperties.driverVersion;
        }

        ~VKDevice() {}

    public:
        vk::PhysicalDevice &GetVulkanDevice() { return m_PhysicalDevice; }
        vk::PhysicalDeviceProperties &GetProperties() { return m_DeviceProperties; }
        vk::PhysicalDeviceLimits &GetDeviceLimits() { return m_PhysicalDeviceLimits; }
        vk::PhysicalDeviceFeatures &GetDeviceFeatures() { return m_DeviceFeatures; }
        vk::PhysicalDeviceMemoryProperties &GetMemoryProperties() { return m_DeviceMemoryProperties; }

        Version &GetApiVersion() { return m_apiVersion; }
        Version &GetDriverVersion() { return m_driverVersion; }
        String &GetName() { return m_DeviceName; }

    private:
        Version m_apiVersion;
        Version m_driverVersion;
        String m_DeviceName;
        vk::PhysicalDevice m_PhysicalDevice;
        vk::PhysicalDeviceLimits m_PhysicalDeviceLimits;
        vk::PhysicalDeviceProperties m_DeviceProperties;
        vk::PhysicalDeviceFeatures m_DeviceFeatures;
        vk::PhysicalDeviceMemoryProperties m_DeviceMemoryProperties;
    };
} // namespace Pictura::Graphics::Vulkan
