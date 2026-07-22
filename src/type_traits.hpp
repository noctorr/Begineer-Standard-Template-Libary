#ifndef TYPETRAITS_HPP
#define TYPETRAITS_HPP

namespace std {

/*
going to replace the current "INTEGRAL_CONSTANT" with this because the name actually makes more sense and it is more cleaner.
template < bool val >
    struct __Arithmetic_Static_Memory
    {
        static constexpr bool value = val;
    };

    template < typename __TYPE >
    struct is_arithmetic : __Arithmetic_Static_Memory<false> {};

    template <>
    struct is_arithmetic<char> : __Arithmetic_Static_Memory<true> {};

    template <>
    struct is_arithmetic<short> : __Arithmetic_Static_Memory<true> {};

    template <>
    struct is_arithmetic<int> : __Arithmetic_Static_Memory<true> {};

    template <>
    struct is_arithmetic<long> : __Arithmetic_Static_Memory<true> {};

    template <>
    struct is_arithmetic<long long> : __Arithmetic_Static_Memory<true> {};

    template <>
    struct is_arithmetic<unsigned char> : __Arithmetic_Static_Memory<true> {};

    template <>
    struct is_arithmetic<unsigned short> : __Arithmetic_Static_Memory<true> {};

    template <>
    struct is_arithmetic<unsigned int> : __Arithmetic_Static_Memory<true> {};

    template <>
    struct is_arithmetic<unsigned long> : __Arithmetic_Static_Memory<true> {};

    template <>
    struct is_arithmetic<unsigned long long> : __Arithmetic_Static_Memory<true> {};

    template <>
    struct is_arithmetic<float> : __Arithmetic_Static_Memory<true> {};

    template <>
    struct is_arithmetic<double> : __Arithmetic_Static_Memory<true> {};

    template <>
    struct is_arithmetic<long double> : __Arithmetic_Static_Memory<true> {};

    template < typename __TYPE >
    static constexpr bool is_arithmetic_v = is_arithmetic<__TYPE>::value;
*/
template < class TYPE, TYPE VAL >
struct INTEGRAL_CONSTANT
{
    static constexpr TYPE VALUE = VAL;
};

template < typename TYPE >
struct ISA_INTEGRAL : INTEGRAL_CONSTANT<bool, false> { };

template < >
struct ISA_INTEGRAL<int> : INTEGRAL_CONSTANT<bool, true> { };

template < >
struct ISA_INTEGRAL<double> : INTEGRAL_CONSTANT<bool, true> { };

template < >
struct ISA_INTEGRAL<float> : INTEGRAL_CONSTANT<bool, true> { };

template < >
struct ISA_INTEGRAL<short> : INTEGRAL_CONSTANT<bool, true> { };

template < >
struct ISA_INTEGRAL<long long> : INTEGRAL_CONSTANT<bool, true> { };

template < >
struct ISA_INTEGRAL<unsigned short> : INTEGRAL_CONSTANT<bool, true> { };

template < >
struct ISA_INTEGRAL<unsigned long long> : INTEGRAL_CONSTANT<bool, true> { };

template < >
struct ISA_INTEGRAL<unsigned int> : INTEGRAL_CONSTANT<bool, true> { };

template < typename TYPE >
inline constexpr bool IS_INTEGRAL = ISA_INTEGRAL<TYPE>::VALUE;

template < typename __TYPE >
struct TYPE_IDENTITY {
    using selfType = __TYPE;
};
}

#endif
