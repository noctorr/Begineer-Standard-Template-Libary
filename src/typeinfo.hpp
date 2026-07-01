#ifndef TYPEINFO_HPP
#define TYPEINFO_HPP

namespace std {

template <  class TYPE , TYPE VALUE > struct GENERIC_TYPE_ID {
    static constexpr const char value = VALUE;
};

template < typename TYPE > struct SET_TYPE_ID_PRIMITIVE : GENERIC_TYPE_ID < const char , 'g' > { };

template < > struct SET_TYPE_ID_PRIMITIVE < int > : GENERIC_TYPE_ID < const char , 'i' > { };
template < > struct SET_TYPE_ID_PRIMITIVE < char > : GENERIC_TYPE_ID < const char , 'c' > { };
template < > struct SET_TYPE_ID_PRIMITIVE < short > : GENERIC_TYPE_ID < const char , 's' > { };
template < > struct SET_TYPE_ID_PRIMITIVE < long long > : GENERIC_TYPE_ID < const char, 'l' > { };
template < > struct SET_TYPE_ID_PRIMITIVE < bool > : GENERIC_TYPE_ID < const char, 'b' > { };
template < > struct SET_TYPE_ID_PRIMITIVE < float > : GENERIC_TYPE_ID < const char , 'f' > { };
template < > struct SET_TYPE_ID_PRIMITIVE < double > : GENERIC_TYPE_ID < const char , 'd' > { };
template < > struct SET_TYPE_ID_PRIMITIVE < unsigned int > : GENERIC_TYPE_ID < const char , 'k' > { };
template < > struct SET_TYPE_ID_PRIMITIVE < unsigned char > : GENERIC_TYPE_ID < const char , 'p' > { };
template < > struct SET_TYPE_ID_PRIMITIVE < unsigned short > : GENERIC_TYPE_ID < const char , 'm' > { };
template < > struct SET_TYPE_ID_PRIMITIVE < unsigned long long > : GENERIC_TYPE_ID < const char, 'z' > { };
template < > struct SET_TYPE_ID_PRIMITIVE < const char* > : GENERIC_TYPE_ID < const char , 'x' > { };

template < typename TYPE >
constexpr const char PrimitiveTypeId ( TYPE X ) noexcept
{
    return SET_TYPE_ID_PRIMITIVE<TYPE>::value;
}

}

#endif
