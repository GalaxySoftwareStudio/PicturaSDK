#pragma once
#include "Core/CoreFramework.h"
#include "Core/Exceptions/Exceptions.h"

namespace Pictura::Graphics
{
    class GPUContext
    {
    public:
        GPUContext() {}
        virtual ~GPUContext() {}

    public:
        virtual bool CreateContext() = 0;
        virtual void DestroyContext() = 0;

        virtual void InitSurface(Handle WindowHandle) = 0;

        virtual void PrintDebugInformations() = 0;

    public:
        ComplexHandle GPUSurface;
        bool VerboseContext = false;
    };
} // namespace Pictura::Graphics
