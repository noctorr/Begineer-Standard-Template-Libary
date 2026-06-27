#ifndef TYPETRAITS_HPP
#define TYPETRAITS_HPP

namespace std {

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

}

#endif
}

#endif
