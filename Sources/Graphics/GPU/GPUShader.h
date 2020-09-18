#pragma once
#include "Core/CoreFramework.h"
#include "Core/Exceptions/Exceptions.h"

namespace Pictura::Graphics
{
    enum ShaderTypes
    {
        Vertex,
        Fragment,
        Tessellation,
        Geometry,
        Compute,
        RayGen,
        RayHit
    };

    struct ShaderSet
    {
        Vector<char> VertexShader;
        Vector<char> FragmentShader;
        Vector<char> TessellationShader;
        Vector<char> GeometryShader;
    };

    class GPUShader
    {
    public:
        GPUShader() {}

        GPUShader(String ShaderPath, String Name) {}
        virtual ~GPUShader() {}

    public:
        virtual bool PreprocessShader(Vector<char> RawShaderCode, Vector<char> &PreprocessedShaderCode) = 0;
        virtual bool CompileShader(Vector<char> RawShaderCode, Vector<char> &CompiledSpvShaderCode) = 0;

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
        ShaderSet *RawShaders = {0};
        ShaderSet *CompiledShaders = {0};
    };
}