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
        shaderc::Compiler compiler;
        shaderc::CompileOptions compileOptions;

        // Preprocess shader
        if (RawShaderCode.size() > 1)
        {
            shaderc::PreprocessedSourceCompilationResult result = compiler.PreprocessGlsl(String(RawShaderCode.begin(), RawShaderCode.end()), shaderc_shader_kind::shaderc_glsl_infer_from_source, ("PrecompiledShader_" + Types::ToString(AddressOf(PreprocessedShaderCode))).c_str(), compileOptions);
            if (result.GetCompilationStatus() != shaderc_compilation_status_success)
            {
                throw Exceptions::RuntimeException(ShaderName + " preprocessing failed !\n" + result.GetErrorMessage());
                return false;
            }

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
        shaderc::Compiler compiler;
        shaderc::CompileOptions compileOptions;

        Vector<char> preprocessedCode;
        bool preprocessResult = PreprocessShader(RawShaders->FragmentShader, preprocessedCode);

        if (preprocessResult)
        {
            shaderc::SpvCompilationResult spvModule = compiler.CompileGlslToSpv(String(preprocessedCode.begin(), preprocessedCode.end()), shaderc_shader_kind::shaderc_glsl_infer_from_source, ("CompiledShader_" + Types::ToString(AddressOf(preprocessedCode))).c_str(), compileOptions);
            if (spvModule.GetCompilationStatus() != shaderc_compilation_status::shaderc_compilation_status_success)
            {
                throw Exceptions::RuntimeException(ShaderName + " compilation failed !\n" + spvModule.GetErrorMessage());
                return false;
            }

            Debug::Log::GetFrameworkLog().Success(ShaderName + " compiled successfully !");
        }

        return preprocessResult;
    }
}