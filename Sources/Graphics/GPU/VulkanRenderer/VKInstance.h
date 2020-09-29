#pragma once
#include "Graphics/GPU/GPUInstance.h"
#include "Vulkan/vulkan.hpp"
#include "VulkanMemoryAllocator/vma.h"

namespace Pictura::Graphics::Vulkan
{
    class VKInstance : public GPUInstance
    {
    public:
        VKInstance();
        ~VKInstance();

    public:
        virtual void InitInstance();

    private:
        bool CheckValidationLayerSupport();

        static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                                  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) 
        {

            Debug::Log::GetFrameworkLog().Error("Vulkan Validation Layer : " + String(pCallbackData->pMessage + '\n'));
            return VK_FALSE;
        }

        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
            auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
            if (func != nullptr) {
                return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
            }
            else {
                return VK_ERROR_EXTENSION_NOT_PRESENT;
            }
        }

    public:
        vk::Instance &GetVulkanInstance() { return m_VkInstance; }

    private:
        vk::Instance m_VkInstance;
        VkDebugUtilsMessengerEXT DebugMessenger;
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

    #ifdef PICTURA_DEBUG
        const bool EnableValidationLayers = true;
    #else
        const bool EnableValidationLayers = false;
    #endif
    };
} // namespace Pictura::Graphics::Vulkan
