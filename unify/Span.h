#pragma once

#include <cstddef>

namespace unify
{
    constexpr std::size_t DynamicExtent = -1;

    template<typename T, std::size_t T_Extent = DynamicExtent >
    class span
    {
        T* m_data;
        std::size_t m_size;
    public:
        span() = default;
        span(T* data, std::size_t size) : m_data(data), m_size(size) {}
    };
}