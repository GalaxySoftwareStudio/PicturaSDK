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
        virtual bool CompileShader(Vector<char> RawShaderCode, Vector<char> &CompiledSpvShaderCode);
    };
}