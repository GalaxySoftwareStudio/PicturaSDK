#pragma once
#include "Core/CoreFramework.h"
#include "Core/Exceptions/Exceptions.h"

namespace Pictura::Graphics
{
    enum class ShaderTypes
    {
        VertexShader,
        PixelShader,
        GeometryShader,
        HullShader,
        DomainShader,
        ComputeShader,
    };

    template<typename T = char>
    struct ShaderSet
    {
        Vector<T> VertexShader;
        Vector<T> PixelShader;
        Vector<T> GeometryShader;
        Vector<T> HullShader;
        Vector<T> DomainShader;
        Vector<T> ComputeShader;
    };

    class GPUShader
    {
    public:
        GPUShader() {}

        GPUShader(String ShaderPath, String Name) {}
        virtual ~GPUShader() {}

    public:
        virtual String ShaderSuffixFromStage(ShaderTypes Type) = 0;
        virtual bool CompileShader(Vector<char> RawShaderCode, Vector<uint32> &CompiledSpvShaderCode, ShaderTypes ShaderStage = ShaderTypes::VertexShader) = 0;

    protected:
        virtual Vector<char> ReadShaderFile(String ShaderPath)
        {
            std::ifstream file(ShaderPath, std::ios::ate | std::ios::binary);

            size_t fileSize = (size_t)file.tellg();
            Vector<char> buffer(fileSize);

            file.seekg(0);
            file.read(buffer.data(), fileSize);

            file.close();
            return buffer;
        }

    public:
        String ShaderName;
        String ShaderPath;
        ShaderSet<char> *RawShaders = {0};
        ShaderSet<uint32> *CompiledShaders = {0};
    };
}