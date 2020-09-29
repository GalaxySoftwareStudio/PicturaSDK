#include "PicturaPCH.h"
#include "VKShader.h"

namespace Pictura::Graphics::Vulkan
{
    VKShader::VKShader(GPUDevice *device, String ShaderPath, String Name)
    {
        PhysicalDevice = device;
        ShaderName = Name;

        RawShaders->VertexShader = ReadShaderFile(ShaderPath + "VS.hlsl");
        CompileShader(RawShaders->VertexShader, CompiledShaders->VertexShader);

        RawShaders->PixelShader = ReadShaderFile(ShaderPath + "PS.hlsl");
        CompileShader(RawShaders->PixelShader, CompiledShaders->PixelShader);

        std::cout << RawShaders->PixelShader.data() << std::endl
                  << std::endl
                  << std::endl;

        std::cout << CompiledShaders->PixelShader.data() << std::endl;

        RawShaders->HullShader = ReadShaderFile(ShaderPath + "HS.hlsl");
        CompileShader(RawShaders->HullShader, CompiledShaders->HullShader);

        RawShaders->DomainShader = ReadShaderFile(ShaderPath + "DS.hlsl");
        CompileShader(RawShaders->DomainShader, CompiledShaders->DomainShader);

        RawShaders->ComputeShader = ReadShaderFile(ShaderPath + "CS.hlsl");
        CompileShader(RawShaders->ComputeShader, CompiledShaders->ComputeShader);

        RawShaders->GeometryShader = ReadShaderFile(ShaderPath + "GS.hlsl");
        CompileShader(RawShaders->GeometryShader, CompiledShaders->GeometryShader);
    }

    vk::ShaderModule VKShader::CreateShaderModule(const Vector<uint32> &code)
    {
        try
        {
            vk::ShaderModuleCreateInfo moduleCreateInfo(vk::ShaderModuleCreateFlags(), code.size() * sizeof(uint32), code.data());
            vk::ShaderModule shaderModule = CastTo<VKDevice *>(PhysicalDevice)->GetLogicalDevice().createShaderModule(moduleCreateInfo);
            return shaderModule;
        }
        catch (const std::exception &e)
        {
            throw GPUException("Failed to create a vulkan shader module !\n" + String(e.what()));
        }
    }

    String VKShader::ShaderSuffixFromStage(Graphics::ShaderTypes Type)
    {
        switch (Type)
        {
            case ShaderTypes::VertexShader:
                return "VS.hlsl";
                break;
            case ShaderTypes::PixelShader:
                return "PS.hlsl";
                break;
            case ShaderTypes::HullShader:
                return "HS.hlsl";
                break;
            case ShaderTypes::DomainShader:
                return "DS.hlsl";
                break;
            case ShaderTypes::GeometryShader:
                return "GS.hlsl";
                break;
            case ShaderTypes::ComputeShader:
                return "CS.hlsl";
                break;
            default:
                Debug::Log::GetFrameworkLog().Warning("Unrecognized shader type passed to suffix conversion !");
                return "VS.hlsl";
                break;
        }
    }

    bool VKShader::CompileShader(Vector<char> RawShaderCode, Vector<uint32> &CompiledSpvShaderCode, Graphics::ShaderTypes ShaderStage)
    {
        if (RawShaderCode.empty())
        {
            return false;
        }
        const char *ShaderFileName = (ShaderPath + ShaderSuffixFromStage(ShaderStage)).c_str();
        ShaderConductor::ShaderStage Stage = (ShaderConductor::ShaderStage)ShaderStage;
        ShaderConductor::Compiler::SourceDesc ShaderSourceDescription{ReinterpretCastTo<char *>(RawShaderCode.data()),
                                                                      ShaderFileName,
                                                                      "main", Stage, nullptr, 0, [](const char *IncludeName) -> ShaderConductor::Blob * {
                                                                          //TODO : Handle include files in shader using Pictura Filesystem
                                                                          //Loop though shader include directories and create a blob of include files

                                                                          ShaderConductor::Blob *IncludesBlob = ShaderConductor::CreateBlob(nullptr, 0);

                                                                          return IncludesBlob;
                                                                      }};

        ShaderConductor::Compiler::Options CompilerOptions;
        CompilerOptions.disableOptimizations = false;
        CompilerOptions.enableDebugInfo = true;
        CompilerOptions.optimizationLevel = 3;

        Array<ShaderConductor::Compiler::TargetDesc, 1> Targets = {{ShaderConductor::ShadingLanguage::SpirV, "1_0", false}};

        ShaderConductor::Compiler::ResultDesc CompilationResult;
        ShaderConductor::Compiler::Compile(ShaderSourceDescription, CompilerOptions, Targets.data(), CastTo<uint32>(Targets.size()), &CompilationResult);

        if (CompilationResult.hasError)
        {
            StringView CompilationErrorMessage(ReinterpretCastTo<const char *>(CompilationResult.errorWarningMsg->Data()), CompilationResult.errorWarningMsg->Size());

            Debug::Log::GetFrameworkLog().Error("Failed to compile shader " + String(ShaderFileName) + " : " + String(CompilationErrorMessage));
            return false;
        }

        uint32 *SpirV = ReinterpretCastTo<uint32 *>(ConstCast<void *>(CompilationResult.target->Data()));
        CompiledSpvShaderCode = Vector<uint32>(SpirV, SpirV + (CompilationResult.target->Size() / sizeof(uint32)));

        Debug::Log::GetFrameworkLog().Success(ShaderName + " compiled successfully !");

        return true;
    }
}