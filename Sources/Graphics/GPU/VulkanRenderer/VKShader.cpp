#include "PicturaPCH.h"
#include "VKShader.h"

namespace Pictura::Graphics::Vulkan
{
    VKShader::VKShader(String ShaderPath, String Name)
    {
        ShaderName = Name;

        RawShaders->VertexShader = ReadShaderFile(ShaderPath + ".vert");
        CompileShader(RawShaders->VertexShader, CompiledShaders->VertexShader);

        RawShaders->FragmentShader = ReadShaderFile(ShaderPath + ".frag");
        CompileShader(RawShaders->FragmentShader, CompiledShaders->FragmentShader);

        std::cout << RawShaders->FragmentShader.data() << std::endl
                  << std::endl
                  << std::endl;

        std::cout << CompiledShaders->FragmentShader.data() << std::endl;

        RawShaders->TessellationShader = ReadShaderFile(ShaderPath + ".tess");
        CompileShader(RawShaders->TessellationShader, CompiledShaders->TessellationShader);

        RawShaders->GeometryShader = ReadShaderFile(ShaderPath + ".geom");
        CompileShader(RawShaders->GeometryShader, CompiledShaders->GeometryShader);
    }

    bool VKShader::CompileShader(Vector<char> RawShaderCode, Vector<char> &CompiledSpvShaderCode)
    {
        bool compilationSuccess = false;

        //TODO: Complete compilation code
        Debug::Log::GetFrameworkLog().Success(ShaderName + " compiled successfully !");

        return compilationSuccess;
    }
}