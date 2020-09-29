#pragma once
#include "Graphics/GPU/GPUShader.h"
#include "ShaderConductor/ShaderConductor.hpp"
#include "VKDevice.h"

namespace Pictura::Graphics::Vulkan
{
    class VKShader : public GPUShader
    {
    public:
        VKShader(GPUDevice *device, String ShaderPath, String Name);
        ~VKShader() {}

    public:
        vk::ShaderModule CreateShaderModule(const Vector<uint32> &code);

    public:
        virtual String ShaderSuffixFromStage(Graphics::ShaderTypes Type);
        virtual bool CompileShader(Vector<char> RawShaderCode, Vector<uint32> &CompiledSpvShaderCode, Graphics::ShaderTypes ShaderStage = Graphics::ShaderTypes::VertexShader);
    };
}