#pragma once
#include "Graphics/GPUContext.h"
#include "VKInstance.h"
#include "VKDevice.h"

namespace Pictura::Graphics::Vulkan
{
    class VKContext : public GPUContext
    {
    public:
        VKContext();
        ~VKContext();

    public:
        virtual bool CreateContext();
        virtual void DestroyContext();

        virtual void PrintDebugInformations();

    private:
        String toHumanSize(size_t size)
        {
            static const std::vector<std::string> SUFFIXES{{"B", "KB", "MB", "GB", "TB", "PB"}};
            size_t suffixIndex = 0;
            while (suffixIndex < SUFFIXES.size() - 1 && size > 1024)
            {
                size >>= 10;
                ++suffixIndex;
            }

            std::stringstream buffer;
            buffer << size << " " << SUFFIXES[suffixIndex];
            return buffer.str();
        }

    public:
        VKInstance *VulkanInstance = nullptr;
        VKDevice *DefaultPhysicalDevice;

        Vector<VKDevice> PhysicalDevices = {};
    };
}