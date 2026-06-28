#include <stdexcept>
#include <initializer_list>
#include "type_traits.hpp"

using uint32_t = unsigned int;

#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace std {
template < typename TYPE >
class vector 
{
    private:
    TYPE* array { nullptr };
    uint32_t size { 0u };

    public:
    explicit vector() {
        array = new TYPE[1u];
        size = 1u;
    }

    explicit vector(
        std::initializer_list<TYPE> arr
    ) {
        uint32_t len = arr.size();
        array = new TYPE[len];

        auto BACK = arr.back();
        for ( uint32_t i { 0u }; i < len; i++ ) {
            array[i] = *(BACK + i);
        }
        size = len;
    }

    ~vector() {
        delete[] array;
    }

    void push_back ( TYPE value ) noexcept
    {
        TYPE stackArr[size+1u];
        for ( uint32_t i { 0u }; i < size; i++ ) {
            stackArr[i] = array[i];
            if ( std::IS_INTEGRAL<TYPE> ) {
                array[i] = 0;
            } else {
                array[i] = nullptr;
            }
        }
        stackArr[size+1u] = value;
        delete[] array;
        size += 1u;
        array = new TYPE[size];
        for ( uint32_t i { 0u }; i < size; i++ ) {
            array[i] = stackArr[i];
        }
    }

    constexpr uint32_t len () const noexcept
    {
        return size;
    }

    TYPE *data () const noexcept
    {
        return array;
    }

    const bool is_sorted () const noexcept
    {
        for ( uint32_t i { 1u }; i < size; i++ ) {
            if ( array[i] < array[i-1u] ) return false; 
        }
        return true;
    }

    const bool empty () const noexcept
    {
        return (size == 0u);
    }

    void sort ()
    {
        if (!std::IS_INTEGRAL<TYPE>) throw std::runtime_error("Cannot sort a non-number list.");
        while (!is_sorted()) {
            for ( uint32_t i { 1u }; i < size; i++ ) {
                if ( array[i] < array[i-1u] ) {
                    TYPE X1 = array[i];
                    TYPE X2 = array[i-1u];
                    array[i] = X2;
                    array[i-1u] = X1;
                }
            }
        }
    }

    void resize ( uint32_t x ) noexcept
    {
        TYPE stackArr[x];
        if ( x > size ) {
            for ( uint32_t i { 0u }; i < x; i++ ) {
                if ( i > size-1u ) {
                    if ( std::IS_INTEGRAL<TYPE> ) {
                        stackArr[i] = 0;
                    } else {
                        stackArr[i] = nullptr;
                    }
                } else {
                    stackArr[i] = array[i];
                }
            }
        } else if ( x < size ) {
            for ( uint32_t i { 0u }; i < x; i++ ) {
                stackArr[i] = array[i];
            }
        } else {
            return;
        }

        if ( std::IS_INTEGRAL<TYPE> ) {
            for ( uint32_t i { 0u }; i < size; i++ ) {
                array[i] = 0;
            }
        } else {
            for ( uint32_t i { 0u }; i < size; i++ ) {
                array[i] = nullptr;
            }
        }

        delete[] array;

        array = new TYPE[x];

        for ( uint32_t i { 0u }; i < x; i++ ) {
            array[i] = stackArr[i];
        }
        size = x;
    }

    void clear () noexcept
    {
        if (std::IS_INTEGRAL<TYPE>) {
            for ( uint32_t i { 0u }; i < size; i++ ) {
                array[i] = 0;
            }
        } else {
            for ( uint32_t i { 0u }; i < size; i++ ) {
                array[i] = nullptr;
            }
        }
    }

    void emplace ( TYPE& value, uint32_t index ) noexcept
    {
        if (index > size - 1u) {
            TYPE stackArray[index];
            for (uint32_t i { 0u }; i < size; i++) {
                stackArray[i] = array[i];
            }

            if (std::IS_INTEGRAL<TYPE>) {
                for ( uint32_t i { 0u }; i < size; i++ ) {
                    array[i] = 0;
                }
            } else {
                for ( uint32_t i { 0u }; i < size; i++ ) {
                    array[i] = nullptr;
                }
            }

            delete[] array;

            stackArray[index] = value;
            array = new TYPE[index];

            for ( uint32_t i { 0u }; i < index; i++ ) {
                array[i] = stackArray[i];
            }

            size = index;
        } else {
            array[index] = value;
        }
    }

    void insert ( TYPE& value, uint32_t index )
    {
        if (index > size - 1u) throw std::out_of_range("Index larger than vector.");

        array[index] = value;
    }

    void reserve ( uint32_t capacity )
    {
        if (size + capacity < size) throw std::out_of_range("Capacity parameter leads to reset of size.");
        size += capacity;

        TYPE stackArray[size];
        for ( uint32_t i { 0u }; i < size; i++ ) {
            stackArray[i] = array[i];
            if ( std::IS_INTEGRAL<TYPE> ) {
                array[i] = 0;
            } else {
                array[i] = nullptr;
            }
        }

        delete[] array;

        array = new TYPE[size];

        for ( uint32_t i { 0u }; i < size; i++ ) {
            array[i] = stackArray[i];
        }
    }

    TYPE &front () const
    {
        if ( size == 0 ) throw std::runtime_error("Empty vector.");
        return *array[0];
    }

    TYPE &back () const
    {
        if ( size == 0 ) throw std::runtime_error("Empty vector.");
        return *array[size-1u];
    }

    TYPE &at ( uint32_t index ) const
    {
        if ( index > size ) throw std::out_of_range("idiot");
        return *array[index];
    }

    TYPE &operator[] ( uint32_t index ) const noexcept
    {
        return *array[index];
    }

    void operator= ( vector &vec ) noexcept
    {
        TYPE *arr = vec.data();
        uint32_t length = vec.len();
        TYPE stackArr[length];
        size = length;

        for (uint32_t i { 0u }; i < length; i++) {
            stackArr[i] = arr[i];
        }

        delete[] array;

        array = new TYPE[length];

        for (uint32_t i { 0u }; i < length; i++) {
            array[i] = stackArr[i];
        }
    }

    template < typename NUMBER_TYPE >
    requires std::IS_INTEGRAL<TYPE> && std::IS_INTEGRAL<NUMBER_TYPE>
    auto operator+ ( vector<NUMBER_TYPE> &vec ) noexcept
    {
        using RESULT_TYPE = decltype(TYPE{} + NUMBER_TYPE{});
        constexpr uint32_t length = vec.len();
        vector<RESULT_TYPE> result;
        result.resize((length > size) ? size : length);

        if ( length > size ) {
            for ( uint32_t i { 0u }; i < size; i++ ) {
                array[i] += static_cast<TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(array[i]);
            }
        } else if ( size > length ) {
            for ( uint32_t i { 0u }; i < length; i++ ) {
                array[i] +=  static_cast<TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(array[i]);
            }
        } else {
            for ( uint32_t i { 0u }; i < length; i++ ) {
                array[i] += static_cast<TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(array[i]);
            }
        }

        return result;
    }

    template < typename NUMBER_TYPE >
    requires std::IS_INTEGRAL<TYPE> && std::IS_INTEGRAL<NUMBER_TYPE>
    auto operator- ( vector<NUMBER_TYPE> &vec ) noexcept
    {
        using RESULT_TYPE = decltype(TYPE{} + NUMBER_TYPE{});
        constexpr uint32_t length = vec.len();
        vector<RESULT_TYPE> result;
        result.resize((length > size) ? size : length);

        if ( length > size ) {
            for ( uint32_t i { 0u }; i < size; i++ ) {
                array[i] -= static_cast<TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(array[i]);
            }
        } else if ( size > length ) {
            for ( uint32_t i { 0u }; i < length; i++ ) {
                array[i] -=  static_cast<TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(array[i]);
            }
        } else {
            for ( uint32_t i { 0u }; i < length; i++ ) {
                array[i] -= static_cast<TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(array[i]);
            }
        }

        return result;
    }


    template < typename NUMBER_TYPE >
    requires std::IS_INTEGRAL<TYPE> && std::IS_INTEGRAL<NUMBER_TYPE>
    auto operator* ( vector<NUMBER_TYPE> &vec ) noexcept
    {
        using RESULT_TYPE = decltype(TYPE{} + NUMBER_TYPE{});
        constexpr uint32_t length = vec.len();
        vector<RESULT_TYPE> result;
        result.resize((length > size) ? size : length);

        if ( length > size ) {
            for ( uint32_t i { 0u }; i < size; i++ ) {
                array[i] *= static_cast<TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(array[i]);
            }
        } else if ( size > length ) {
            for ( uint32_t i { 0u }; i < length; i++ ) {
                array[i] *=  static_cast<TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(array[i]);
            }
        } else {
            for ( uint32_t i { 0u }; i < length; i++ ) {
                array[i] *= static_cast<TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(array[i]);
            }
        }

        return result;
    }


    template < typename NUMBER_TYPE >
    requires std::IS_INTEGRAL<TYPE> && std::IS_INTEGRAL<NUMBER_TYPE>
    auto operator/ ( vector<NUMBER_TYPE> &vec ) noexcept
    {
        using RESULT_TYPE = decltype(TYPE{} + NUMBER_TYPE{});
        constexpr uint32_t length = vec.len();
        vector<RESULT_TYPE> result;
        result.resize((length > size) ? size : length);

        if ( length > size ) {
            for ( uint32_t i { 0u }; i < size; i++ ) {
                array[i] /= static_cast<TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(array[i]);
            }
        } else if ( size > length ) {
            for ( uint32_t i { 0u }; i < length; i++ ) {
                array[i] /=  static_cast<TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(array[i]);
            }
        } else {
            for ( uint32_t i { 0u }; i < length; i++ ) {
                array[i] /= static_cast<TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(array[i]);
            }
        }

        return result;
    }


    static void destroy ( vector &vec )
    {
        delete vec;
    }
};
}

#endif
