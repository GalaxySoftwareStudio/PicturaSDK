#include "PicturaPCH.h"
#include "VKInstance.h"

namespace Pictura::Graphics::Vulkan
{
    VKInstance::VKInstance()
    {
        InitInstance();
    }

    VKInstance::~VKInstance()
    {
        Debug::Log::GetFrameworkLog().Info("Destroying a vulkan instance");
        m_VkInstance.destroy();
    }

    void VKInstance::InitInstance()
    {
        try
        {
            vk::ApplicationInfo InstanceApplicationInfo("Pictura_VulkanInstance", 1, "Pictura_VulkanRenderer", 1, VK_API_VERSION_1_2);
            vk::InstanceCreateInfo InstanceCreationInfo({}, &InstanceApplicationInfo);

            m_VkInstance = vk::createInstance(InstanceCreationInfo);
        }
        catch (vk::SystemError &err)
        {
            throw Exceptions::GPUException("Vulkan instance creation failed !\n" + String(err.what()));
        }
    }
}