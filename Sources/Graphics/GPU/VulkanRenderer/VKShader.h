#pragma once
#include "Graphics/GPU/GPUShader.h"

namespace Pictura::Graphics::Vulkan
{
    class VKShader : public GPUShader
    {
    public:
        VKShader(String ShaderPath, String Name);
        ~VKShader();

    public:
        virtual bool PreprocessShader(Vector<char> RawShaderCode, Vector<char> &PreprocessedShaderCode);
        virtual bool CompileShader(Vector<char> RawShaderCode, Vector<char> &CompiledSpvShaderCode);
    };
}