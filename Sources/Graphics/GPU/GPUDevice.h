#pragma once
#include "Core/CoreFramework.h"
#include "Core/Exceptions/Exceptions.h"

namespace Pictura::Graphics
{
    class GPUDevice
    {
    public:
        GPUDevice() {}
        virtual ~GPUDevice() {}
    };
} // namespace Pictura::Graphics