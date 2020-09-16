#pragma once
#include "Core/CoreFramework.h"
#include "Core/Exceptions/Exceptions.h"
#include "Graphics/Color.h"

namespace Pictura::Graphics
{
    class GPUContext
    {
    public:
        GPUContext() {}
        virtual ~GPUContext() {}

    public:
        virtual bool CreateContext(Handle windowHandle) = 0;
        virtual void DestroyContext() = 0;

        virtual void InitSurface(Handle WindowHandle) = 0;
        virtual void CreateGraphicsPipeline() = 0;

        virtual void PrintDebugInformations() = 0;

    private:
        Handle m_WindowHandle;

    public:
        ComplexHandle GPUSurface;
        bool VerboseContext = false;
    };
} // namespace Pictura::Graphics
