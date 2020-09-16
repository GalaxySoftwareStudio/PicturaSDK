#pragma once
#include "Graphics/GPU/GPUInstance.h"
#include "vulkan/vulkan.hpp"
#include "vulkan/vma.h"

namespace Pictura::Graphics::Vulkan
{
    class VKInstance : public GPUInstance
    {
    public:
        VKInstance();
        ~VKInstance();

    public:
        virtual void InitInstance();

    public:
        vk::Instance &GetVulkanInstance() { return m_VkInstance; }

    private:
        vk::Instance m_VkInstance;
    };
} // namespace Pictura::Graphics::Vulkan
