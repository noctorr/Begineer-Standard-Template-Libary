#include "type_traits.hpp"

constexpr int INT_SIZE { static_cast<int>(sizeof(int)) * 8 };

consteval bool Check ()
{
    if constexpr ( INT_SIZE == 32 ) 
        return true;
    else
        return false;
}

#ifndef CSTDINT_HPP
#define CSTDINT_HPP

namespace std {
using fast_uint32 = unsigned int;
using fast_uint64 = unsigned long long;
using fast_int8 = char;
using fast_int16 = short;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint64 = unsigned long long;

// trying to work on a more performant and faster way to do this instead of using objects
using uint32 = typename decltype([]{
    if constexpr (Check()) 
        return std::TYPE_IDENTITY<unsigned int>{ };
    else
        return std::TYPE_IDENTITY<unsigned long>{ };
}())::selfType;

constexpr uint32 UINT32_MAX { 4294967278 };
}

#endif
