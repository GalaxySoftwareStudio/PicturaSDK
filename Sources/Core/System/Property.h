#pragma once
#include "Core/CoreFramework.h"
#include "Core/Events/EventArgs/EventArgs.h"

namespace Pictura
{
    template <typename T>
    class Property
    {
    public:
        using PropertyChangedSignature = void(const T &newValue);

    public:
        Property(T t) : m_Value(t) {}

        template <typename U>
        Property(T t, U *thisPtr, void (U::*onPropertyChanged)(const T &)) : m_Value(t), OnPropertyChanged(std::bind(onPropertyChanged, thisPtr, std::placeholders::_1)) {}

        virtual ~Property() {}
        virtual T &operator=(const T &f)
        {
            if (OnPropertyChanged)
            {
                OnPropertyChanged(f);
            }
            return m_Value = f;
        }
        virtual const T &operator()() const { return m_Value; }
        virtual T *operator->() { return &m_Value; }

        operator T() const { return m_Value; }

    public:
        void Set(T value) { m_Value = value; }

    protected:
        T m_Value;
        Function<PropertyChangedSignature> OnPropertyChanged;
    };
} // namespace Pictura