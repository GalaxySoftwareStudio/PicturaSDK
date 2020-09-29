#include "PicturaPCH.h"
#include "Core/System/Runtime/Application.h"
#include "VKContext.h"

namespace Pictura::Graphics::Vulkan
{
    VKContext::VKContext()
    {
    }

    VKContext::~VKContext()
    {
        this->DestroyContext();
        Debug::Log::GetFrameworkLog().Info("Vulkan context [@" + Types::ToString(this) + "] destroyed !");
    }

    bool VKContext::CreateContext(Handle windowHandle)
    {
        try
        {
            VulkanInstance = new VKInstance();
            InitSurface(windowHandle);

            for (auto &&physDevices : VulkanInstance->GetVulkanInstance().enumeratePhysicalDevices())
            {
                PhysicalDevices.push_back(VKDevice(physDevices, ReinterpretCastTo<VkSurfaceKHR>(GPUSurface)));
            }

            DefaultPhysicalDevice = &PhysicalDevices[0];
            VulkanSwapchain = new VKSwapchain(*DefaultPhysicalDevice, GPUSurface);
            CreateGraphicsPipeline();

            if (VerboseContext)
            {
                PrintDebugInformations();
            }

            Debug::Log::GetFrameworkLog().Success("Vulkan context [@" + Types::ToString(this) + "] created successfully !");
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

    void VKContext::InitSurface(Handle WindowHandle)
    {
        VkSurfaceCreateInfoKHR surfaceInfo{VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR, nullptr, 0, VK_MODULE_HANDLE, WindowHandle};
        VkSurfaceKHR surface;
        VkResult result = vkCreateSurfaceKHR(VulkanInstance->GetVulkanInstance(), &surfaceInfo, nullptr, &surface);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::GPUException("Vulkan surface creation failed !");
            return;
        }

        this->GPUSurface = (ComplexHandle)surface;
    }

    void VKContext::CreateGraphicsPipeline()
    {
        VKShader ExampleShader = VKShader(DefaultPhysicalDevice, "Ressources\\Shaders\\Example", "ExampleShader");

        vk::ShaderModule vertexShaderModule = ExampleShader.CreateShaderModule(ExampleShader.CompiledShaders->PixelShader);
        vk::ShaderModule fragmentShaderModule = ExampleShader.CreateShaderModule(ExampleShader.CompiledShaders->VertexShader);

        vk::PipelineShaderStageCreateInfo vertStageCreateInfo({}, vk::ShaderStageFlagBits::eVertex, vertexShaderModule, "main");
        vk::PipelineShaderStageCreateInfo fragStageCreateInfo({}, vk::ShaderStageFlagBits::eFragment, fragmentShaderModule, "main");
        vk::PipelineShaderStageCreateInfo shaderStages[] = {vertStageCreateInfo, fragStageCreateInfo};

        //TODO: Fixed functions
        //...
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
            Debug::Log::GetFrameworkLog().Debug("\t\tHeap[" + Types::ToString(i) + "] : Flags" + vk::to_string(heap.flags) + " (" + Types::ToString(heap.size) + ")");
        }

        Debug::Log::GetFrameworkLog().Debug("\t - Memory Types : " + Types::ToString(DefaultPhysicalDevice->GetMemoryProperties().memoryTypeCount));
        for (size_t i = 0; i < DefaultPhysicalDevice->GetMemoryProperties().memoryTypeCount; ++i)
        {
            const auto &type = DefaultPhysicalDevice->GetMemoryProperties().memoryTypes[i];
            Debug::Log::GetFrameworkLog().Debug("\t\tType[" + Types::ToString(i) + "] : Flags" + vk::to_string(type.propertyFlags) + " heapIndex[" + Types::ToString(type.heapIndex) + "]");
        }
    }
}