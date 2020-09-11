#include "PicturaPCH.h"
#include "VKContext.h"

namespace Pictura::Graphics::Vulkan
{
    VKContext::VKContext()
    {
    }

    VKContext::~VKContext()
    {
        Debug::Log::GetFrameworkLog().Info("Vulkan context [@" + Types::ToString(this) + "] destroyed !");
    }

    bool VKContext::CreateContext()
    {
        try
        {
            VulkanInstance = new VKInstance();
            for (auto &&physDevices : VulkanInstance->GetVulkanInstance().enumeratePhysicalDevices())
            {
                PhysicalDevices.push_back(VKDevice(physDevices));
            }

            DefaultPhysicalDevice = &PhysicalDevices[0];

            Debug::Log::GetFrameworkLog().Success("Vulkan context [@" + Types::ToString(this) + "] created successfully !");
            if (VerboseContext)
            {
                PrintDebugInformations();
            }

            return (DefaultPhysicalDevice != nullptr);
        }
        catch (const std::exception &e)
        {
            throw Exceptions::GPUException("Vulkan context creation failed !\n" + String(e.what()));
            return false;
        }
    }

    void VKContext::DestroyContext()
    {
        delete VulkanInstance;
    }

    void VKContext::PrintDebugInformations()
    {
        Debug::Log::GetFrameworkLog().Debug("\t - API Version : " + DefaultPhysicalDevice->GetApiVersion().toString());
        Debug::Log::GetFrameworkLog().Debug("\t - API Version : " + DefaultPhysicalDevice->GetApiVersion().toString());
        Debug::Log::GetFrameworkLog().Debug("\t - Device Name : " + Types::ToString(DefaultPhysicalDevice->GetName()));
        Debug::Log::GetFrameworkLog().Debug("\t - Device Type : " + vk::to_string(DefaultPhysicalDevice->GetProperties().deviceType));
        Debug::Log::GetFrameworkLog().Debug("\t - Memory Heaps : " + Types::ToString(DefaultPhysicalDevice->GetMemoryProperties().memoryHeapCount));
        for (size_t i = 0; i < DefaultPhysicalDevice->GetMemoryProperties().memoryHeapCount; ++i)
        {
            const auto &heap = DefaultPhysicalDevice->GetMemoryProperties().memoryHeaps[i];
            Debug::Log::GetFrameworkLog().Debug("\t\tHeap[" + Types::ToString(i) + "] : Flags" + vk::to_string(heap.flags) + " (" + toHumanSize(heap.size) + ")");
        }

        Debug::Log::GetFrameworkLog().Debug("\t - Memory Types : " + Types::ToString(DefaultPhysicalDevice->GetMemoryProperties().memoryTypeCount));
        for (size_t i = 0; i < DefaultPhysicalDevice->GetMemoryProperties().memoryTypeCount; ++i)
        {
            const auto &type = DefaultPhysicalDevice->GetMemoryProperties().memoryTypes[i];
            Debug::Log::GetFrameworkLog().Debug("\t\tType[" + Types::ToString(i) + "] : Flags" + vk::to_string(type.propertyFlags) + " heapIndex[" + Types::ToString(type.heapIndex) + "]");
        }
    }
}