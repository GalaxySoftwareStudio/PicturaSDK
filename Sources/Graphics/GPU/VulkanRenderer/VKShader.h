#pragma once
#include "Graphics/GPU/GPUShader.h"
#include "ShaderConductor/ShaderConductor.hpp"

namespace Pictura::Graphics::Vulkan
{
    class VKShader : public GPUShader
    {
    public:
        VKShader(String ShaderPath, String Name);
        ~VKShader() {}

    public:
        virtual String ShaderSuffixFromStage(Graphics::ShaderTypes Type);
        virtual bool CompileShader(Vector<char> RawShaderCode, Vector<uint32> &CompiledSpvShaderCode, Graphics::ShaderTypes ShaderStage = Graphics::ShaderTypes::VertexShader);
    };
}