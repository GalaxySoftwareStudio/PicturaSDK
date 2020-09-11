#pragma once
#include "Exception.h"

namespace Pictura::Exceptions
{
    class GPUException : public Exception
    {
    public:
        explicit GPUException(String Message) : Exception(Message, "GPUException") {}
    };
}