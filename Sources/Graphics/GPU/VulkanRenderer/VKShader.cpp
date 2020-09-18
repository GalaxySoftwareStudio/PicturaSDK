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

    VKShader::~VKShader()
    {
    }

    bool VKShader::PreprocessShader(Vector<char> RawShaderCode, Vector<char> &PreprocessedShaderCode)
    {
        // Prepare compiler objects and compiler options

        // Preprocess shader
        if (RawShaderCode.size() > 1)
        {
            //TODO: Complete preprocessing code
            Vector<char> result;
            PreprocessedShaderCode = {result.begin(), result.end()};
        }
        else
        {
            Debug::Log::GetFrameworkLog().Warning("A component of " + ShaderName + " is empty! Ignoring preprocessing stage for this component...");
            return false;
        }

        return true;
    }

    bool VKShader::CompileShader(Vector<char> RawShaderCode, Vector<char> &CompiledSpvShaderCode)
    {
        Vector<char> preprocessedCode;
        bool preprocessResult = PreprocessShader(RawShaders->FragmentShader, preprocessedCode);

        if (preprocessResult)
        {
            //TODO: Complete compilation code

            Debug::Log::GetFrameworkLog().Success(ShaderName + " compiled successfully !");
        }

        return preprocessResult;
    }
}