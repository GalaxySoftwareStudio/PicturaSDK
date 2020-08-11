#pragma once
#include "Core/CoreFramework.h"

namespace Pictura
{
	template <typename T>
    class Property
    {
    public:
        virtual ~Property() {}
        virtual T& operator= (const T& f) { return m_Value = f; }
        virtual const T& operator() () const { return m_Value; }
        virtual explicit operator const T& () const { return m_Value; }
        virtual T* operator->() { return &m_Value; }

    protected:
        T m_Value;
    };
}