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

    bool VKInstance::CheckValidationLayerSupport()
    {
        Vector<vk::LayerProperties> availableLayers = vk::enumerateInstanceLayerProperties();

        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

    void VKInstance::InitInstance()
    {
        try
        {
            vk::ApplicationInfo InstanceApplicationInfo(String("Pictura_VulkanInstance_" + Types::ToString(this)).c_str(), 1, "Pictura_VulkanRenderer", 1, VK_API_VERSION_1_2);
            vk::InstanceCreateInfo InstanceCreationInfo({}, &InstanceApplicationInfo);

            if (CheckValidationLayerSupport())
            {
                if (EnableValidationLayers)
                {
                    InstanceCreationInfo.setPEnabledLayerNames(validationLayers);
                }
            }
            else
            {
                Debug::Log::GetFrameworkLog().Warning("Validation layers requested, but not available!");
            }

            Vector<vk::ExtensionProperties> extensionProperties = vk::enumerateInstanceExtensionProperties();
            // sort the extensions alphabetically
            std::sort(extensionProperties.begin(),
                      extensionProperties.end(),
                      [](vk::ExtensionProperties const &a, vk::ExtensionProperties const &b) {
                          return strcmp(a.extensionName, b.extensionName) < 0;
                      });

            Vector<char const *> enabledExtensions;
            enabledExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            for (auto const &ep : extensionProperties)
            {
                enabledExtensions.push_back(ep.extensionName);
            }
            InstanceCreationInfo.setPEnabledExtensionNames(enabledExtensions);

            VkDebugUtilsMessengerCreateInfoEXT DebugCreateInfo;
            DebugCreateInfo = {};
            DebugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            DebugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            DebugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            DebugCreateInfo.pfnUserCallback = VulkanDebugCallback;
            InstanceCreationInfo.setPNext((VkDebugUtilsMessengerCreateInfoEXT*)&DebugCreateInfo);

            m_VkInstance = vk::createInstance(InstanceCreationInfo);

            if (EnableValidationLayers)
            {
                if (CreateDebugUtilsMessengerEXT(m_VkInstance, &DebugCreateInfo, nullptr, &DebugMessenger) != VK_SUCCESS) {
                    Debug::Log::GetFrameworkLog().Warning("Failed to set up debug messenger!");
                }
            }
        }
        catch (vk::SystemError &err)
        {
            throw Exceptions::GPUException("Vulkan instance creation failed !\nError message : " + String(err.what()));
        }
    }
}