#include "PicturaPCH.h"
#include "VKContext.h"

namespace Pictura::Graphics::Vulkan
{
    VKContext::VKContext()
    {
    }

    VKContext::~VKContext()
    {
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

            Debug::Log::GetFrameworkLog().Success("Vulkan context created successfully !");
            //Print context informations

            return (DefaultPhysicalDevice != nullptr);
        }
        catch (const std::exception &e)
        {
            Debug::Log::GetFrameworkLog().Fatal("Vulkan context creation failed !\n" + String(e.what()));
            return false;
        }
    }

    void VKContext::DestroyContext()
    {
        delete VulkanInstance;
    }
}