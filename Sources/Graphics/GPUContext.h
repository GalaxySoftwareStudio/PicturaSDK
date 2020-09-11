#pragma once
#include "Core/CoreFramework.h"
#include "Core/Exceptions/Exceptions.h"

namespace Pictura::Graphics
{
    class GPUContext
    {
    public:
        GPUContext();
        ~GPUContext();

    public:
        virtual bool CreateContext() = 0;
        virtual void DestroyContext() = 0;
    };
} // namespace Pictura::Graphics
