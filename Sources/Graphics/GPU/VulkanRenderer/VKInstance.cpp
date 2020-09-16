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
        Debug::Log::GetFrameworkLog().Debug("Destroying vulkan instance [@" + Types::ToString(this) + "]");
        m_VkInstance.destroy();
    }

    void VKInstance::InitInstance()
    {
        try
        {
            vk::ApplicationInfo InstanceApplicationInfo(String("Pictura_VulkanInstance_" + Types::ToString(this)).c_str(), 1, "Pictura_VulkanRenderer", 1, VK_API_VERSION_1_2);
            vk::InstanceCreateInfo InstanceCreationInfo({}, &InstanceApplicationInfo);

            Vector<vk::ExtensionProperties> extensionProperties = vk::enumerateInstanceExtensionProperties();
            // sort the extensions alphabetically
            std::sort(extensionProperties.begin(),
                      extensionProperties.end(),
                      [](vk::ExtensionProperties const &a, vk::ExtensionProperties const &b) {
                          return strcmp(a.extensionName, b.extensionName) < 0;
                      });

            Vector<char const *> enabledExtensions;
            for (auto const &ep : extensionProperties)
            {
                enabledExtensions.push_back(ep.extensionName);
            }
            InstanceCreationInfo.setPEnabledExtensionNames(enabledExtensions);

            m_VkInstance = vk::createInstance(InstanceCreationInfo);
        }
        catch (vk::SystemError &err)
        {
            throw Exceptions::GPUException("Vulkan instance creation failed !\n" + String(err.what()));
        }
    }
}