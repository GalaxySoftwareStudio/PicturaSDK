#pragma once
#include "Core/CoreFramework.h"
#include "Core/Exceptions/Exceptions.h"

namespace Pictura::Graphics
{
    class GPUCommandQueue
    {
    public:
        GPUCommandQueue() {}
        virtual ~GPUCommandQueue() {}

    public:
        virtual void CreateCommandQueue() = 0;
        virtual void Begin() = 0;
        virtual void End() = 0;
    };
}