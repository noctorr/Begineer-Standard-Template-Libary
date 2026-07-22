#include "type_traits.hpp"
#include "cstdint.hpp"
#include "initialiser_list.hpp"
#include <stdexcept>

#ifndef VECTOR_HPP
#define VECTOR_HPP

// rewriting vector class for the fifth time now, there is major flaws and need to add an iterator
namespace std {
template < typename __TYPE >
class vector final
{
    protected:
    __TYPE* m_selfArray { nullptr };
    std::uint32 m_size { 0 };
    std::uint32 m_capacity { 0 };

    public:
    explicit vector () noexcept {
        m_selfArray = new __TYPE[10];
        m_capacity = 10;
    }

    explicit vector (
        std::initialiser_list<__TYPE> LIST
    ) noexcept {
        std::uint32 size = LIST.size();
        m_selfArray = new __TYPE[size];

        __TYPE* back = LIST.back();
        for ( std::uint32 i { 0 }; i < size; i++ ) {
            m_selfArray[i] = *(back + i);
        }
        m_size = size;
        m_capacity = size;
    }

    vector(vector&& vec) {
        if ( this == &vec ) throw std::logic_error("Cannot move own vector.");
        delete[] m_selfArray;

        m_selfArray = vec.m_selfArray;
        m_size = vec.m_size;
        m_capacity = vec.m_capacity;
        
    }

    vector(const vector& vec) noexcept {
        delete[] m_selfArray;

        m_selfArray = vec.m_selfArray;
        m_size = vec.m_size;
        m_capacity = vec.m_capacity;
    }

    void operator= ( const vector& vec ) noexcept
    {
        delete[] m_selfArray;

        m_selfArray = vec.m_selfArray;
        m_size = vec.m_size;
        m_capacity = vec.m_capacity;
    }

    vector& operator= ( vector&& vec ) noexcept
    {
        if ( this != &vec ) {
            delete[] m_selfArray;

            m_selfArray = vec.m_selfArray;
            m_size = vec.m_size;
            m_capacity = vec.m_capacity;

            vec.m_selfArray = nullptr;
            vec.m_size = 0;
            vec.m_capacity = 0;
        }

        return *this;
    }

    ~vector () {
        delete[] m_selfArray;
    }

    void push_back ( __TYPE VALUE ) noexcept
    {
        __TYPE stackArray[m_size+1];
        for ( std::uint32 i { 0 }; i < m_size; i++ ) {
            stackArray[i] = m_selfArray[i];
        }
        stackArray[m_size+1] = VALUE;
        m_size += 1;
        m_capacity += 1;

        delete[] m_selfArray;

        m_selfArray = new __TYPE[m_capacity];

        for ( std::uint32 i { 0 }; i < m_size; i++ ) {
            m_selfArray[i] = stackArray[i];
        }
    }

    std::uint32 size () const noexcept
    {
        return m_size;
    }

    std::uint32 capacity () const noexcept
    {
        return m_capacity;
    }

    consteval std::uint32 c_size () const noexcept
    {
        return m_size;
    }

    consteval std::uint32  c_capacity () const noexcept
    {
        return m_capacity;
    }

    __TYPE* data () const noexcept
    {
        return m_selfArray;
    }

    const bool empty () const noexcept
    {
        return (m_size == 0);
    }

    const bool is_sorted () const noexcept requires std::IS_INTEGRAL<__TYPE>
    {
        for ( std::uint32 i { 1 }; i < m_size; i++ ) {
            if ( m_selfArray[i] < m_selfArray[i-1] ) return false;
        }
        return true;
    }

    void sort () requires std::IS_INTEGRAL<__TYPE>
    {
        while ( !is_sorted() ) {
            for ( std::uint32 i { 1 }; i < m_size; i++ ) {
                if ( m_selfArray[i] < m_selfArray[i-1] ) {
                    __TYPE greaterNum = m_selfArray[i-1];
                    __TYPE smallerNum = m_selfArray[i];
                    m_selfArray[i] = smallerNum;
                    m_selfArray[i-1] = greaterNum;
                }
            }
        }
    } 

    void release ()
    {
        if constexpr ( std::IS_INTEGRAL<__TYPE> ) {
            for ( std::uint32 i { 0 }; i < m_size; i++ ) {
                m_selfArray[i] = static_cast<__TYPE>(0);
            }
        } else {
            for ( std::uint32 i { 0 }; i < m_size; i++ ) {
                m_selfArray[i] = nullptr;
            }
        }
    }

    void resize ( std::uint32 NEW_CAPACITY ) noexcept
    {
        if ( NEW_CAPACITY == m_capacity ) return;

        __TYPE* Cpy_heapArray = new __TYPE[NEW_CAPACITY];
        if ( NEW_CAPACITY > m_size && std::IS_INTEGRAL<__TYPE> ) {
            for ( std::uint32 i { 0 }; i < m_capacity; i++ ) {
                Cpy_heapArray[i] = m_selfArray[i];
            }

            for ( std::uint32 i { m_size+1 }; i < NEW_CAPACITY; i++ ) {
                Cpy_heapArray[i] = static_cast<__TYPE>(0);
            }
        } else if ( m_capacity > NEW_CAPACITY ) {
            for ( std::uint32 i { 0 }; i < NEW_CAPACITY; i++ ) {
                Cpy_heapArray[i] = m_selfArray[i];
            }
        } else {
            for ( std::uint32 i { 0 }; i < m_size; i++ ) {
                Cpy_heapArray[i] = m_selfArray[i];
            }
        }

        delete[] m_selfArray;

        m_selfArray = new __TYPE[NEW_CAPACITY];

        for ( std::uint32 i { 0 }; i < NEW_CAPACITY; i++ ) {
            m_selfArray[i] = Cpy_heapArray[i];
        }

        m_capacity = NEW_CAPACITY;
        delete[] Cpy_heapArray;
    }

    void clear () noexcept
    {
        if constexpr ( std::IS_INTEGRAL<__TYPE> ) {
            for ( std::uint32 i { 0 }; i < m_size; i++ ) {
                m_selfArray[i] = static_cast<__TYPE>(0);
            }
        } else {
            for ( std::uint32 i { 0 }; i < m_size; i++ ) {
                m_selfArray[i] = nullptr;
            }
        }
    }

    void emplace ( std::uint32 index, __TYPE& value ) noexcept
    {
        if ( index > m_capacity - 1 ) {
            __TYPE* Cpy_heapArray = new __TYPE[index];

            for ( std::uint32 i { 0 }; i < m_size; i++ ) {
                Cpy_heapArray[i] = m_selfArray[i];
            }

            Cpy_heapArray[index] = value;
            m_capacity = index + 5;

            delete[] m_selfArray;

            m_selfArray = new __TYPE[index + 5];

            for ( std::uint32 i { 0 }; i < m_size; i++ ) {
                m_selfArray[i] = Cpy_heapArray[i];
            }

            m_size = index;

            m_selfArray[index] = value;

            delete[] Cpy_heapArray;
        } else {
            m_selfArray[index] = value;
        }
    }

    void insert ( std::uint32 index, __TYPE& value ) noexcept
    {
        if ( index > m_capacity - 1 ) throw std::out_of_range("Out of vector's range.");

        m_selfArray[index] = value;
    }

    void reserve ( std::uint32 capacity )
    {
        if ( m_capacity + capacity < m_capacity ) throw std::out_of_range("Capacity leads to the reset of the vector's capacity.");

        std::uint32 newCap = m_capacity + capacity;
        __TYPE Cpy_heapArray = new __TYPE[newCap];
        for ( std::uint32 i { 0 }; i < m_capacity; i++ ) {
            Cpy_heapArray[i] = m_selfArray[i];
        }

        delete[] m_selfArray;

        m_selfArray = new __TYPE[newCap];

        for ( std::uint32 i { 0 }; i < m_capacity; i++ ) {
            m_selfArray[i] = Cpy_heapArray[i];
        }

        m_capacity += capacity;

        delete[] Cpy_heapArray;
    }

    void reverse () requires std::IS_INTEGRAL<__TYPE>
    {
        __TYPE Cpy_stackArray[m_size] = *m_selfArray;
        std::uint32 medianNumber = (m_size % 2 == 0) ? 
            m_size / 2 : 
            std::uint32(double(m_size) / 2.0) + 2;
        
        for ( std::uint32 i { 0 }; i <= m_size - 1; i++ ) {
            if ( i >= medianNumber ) {
                m_selfArray[i] = Cpy_stackArray[m_size - i];
            } else {
                m_selfArray[i] = m_selfArray[m_size - i];
            }
        }
    }

    __TYPE& begin () const
    {
        if ( m_size == 0 ) throw std::logic_error("Empty vector.");
        return m_selfArray[0];
    }

    __TYPE& end () const
    {
        if ( m_size == 0 ) throw std::logic_error("Empty vector.");
        return m_selfArray[m_size - 1];
    }

    __TYPE& at ( std::uint32 index ) const
    {
        if ( index > m_size ) throw std::out_of_range("Index is larger than the vector's size.");
        return m_selfArray[index];
    }

    __TYPE& operator[] ( std::uint32 index ) const
    {
        return m_selfArray[index];
    }

    template < typename __NUMBER_TYPE >
    requires std::IS_INTEGRAL<__TYPE> && std::IS_INTEGRAL<__NUMBER_TYPE>
    consteval auto operator+ ( const vector& vec ) noexcept
    {
        using RESULT_TYPE = decltype(__NUMBER_TYPE { } + __TYPE { });
        constexpr std::uint32 length = vec.c_size();
        vector<RESULT_TYPE> result;
        result.resize((length > m_size) ? m_size : length);

        if ( length > m_size ) {
            for ( std::uint32 i { 0 }; i < m_size; i++ ) {
                m_selfArray[i] += static_cast<__TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(m_selfArray[i]);
            }
        } else if ( m_size > length ) {
            for ( std::uint32 i { 0 }; i < length; i++ ) {
                m_selfArray[i] += static_cast<__TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(m_selfArray[i]);
            }
        } else {
            for ( std::uint32 i { 0 }; i < length; i++ ) {
                m_selfArray[i] += static_cast<__TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(m_selfArray[i]);
            }
        }

        return result;
    }

    template < typename __NUMBER_TYPE >
    requires std::IS_INTEGRAL<__TYPE> && std::IS_INTEGRAL<__NUMBER_TYPE>
    consteval auto operator- ( const vector& vec ) noexcept
    {
        using RESULT_TYPE = decltype(__NUMBER_TYPE { } + __TYPE { });
        constexpr std::uint32 length = vec.c_size();
        vector<RESULT_TYPE> result;
        result.resize((length > m_size) ? m_size : length);

        if ( length > m_size ) {
            for ( std::uint32 i { 0 }; i < m_size; i++ ) {
                m_selfArray[i] -= static_cast<__TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(m_selfArray[i]);
            }
        } else if ( m_size > length ) {
            for ( std::uint32 i { 0 }; i < length; i++ ) {
                m_selfArray[i] -= static_cast<__TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(m_selfArray[i]);
            }
        } else {
            for ( std::uint32 i { 0 }; i < length; i++ ) {
                m_selfArray[i] -= static_cast<__TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(m_selfArray[i]);
            }
        }

        return result;
    }

    template < typename __NUMBER_TYPE >
    requires std::IS_INTEGRAL<__TYPE> && std::IS_INTEGRAL<__NUMBER_TYPE>
    consteval auto operator* ( const vector& vec ) noexcept
    {
        using RESULT_TYPE = decltype(__NUMBER_TYPE { } + __TYPE { });
        constexpr std::uint32 length = vec.c_size();
        vector<RESULT_TYPE> result;
        result.resize((length > m_size) ? m_size : length);

        if ( length > m_size ) {
            for ( std::uint32 i { 0 }; i < m_size; i++ ) {
                m_selfArray[i] *= static_cast<__TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(m_selfArray[i]);
            }
        } else if ( m_size > length ) {
            for ( std::uint32 i { 0 }; i < length; i++ ) {
                m_selfArray[i] *= static_cast<__TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(m_selfArray[i]);
            }
        } else {
            for ( std::uint32 i { 0 }; i < length; i++ ) {
                m_selfArray[i] *= static_cast<__TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(m_selfArray[i]);
            }
        }

        return result;
    }

    template < typename __NUMBER_TYPE >
    requires std::IS_INTEGRAL<__TYPE> && std::IS_INTEGRAL<__NUMBER_TYPE>
    consteval auto operator/ ( const vector& vec ) noexcept
    {
        using RESULT_TYPE = decltype(__NUMBER_TYPE { } + __TYPE { });
        constexpr std::uint32 length = vec.c_size();
        vector<RESULT_TYPE> result;
        result.resize((length > m_size) ? m_size : length);

        if ( length > m_size ) {
            for ( std::uint32 i { 0 }; i < m_size; i++ ) {
                m_selfArray[i] /= static_cast<__TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(m_selfArray[i]);
            }
        } else if ( m_size > length ) {
            for ( std::uint32 i { 0 }; i < length; i++ ) {
                m_selfArray[i] /= static_cast<__TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(m_selfArray[i]);
            }
        } else {
            for ( std::uint32 i { 0 }; i < length; i++ ) {
                m_selfArray[i] /= static_cast<__TYPE>(vec[i]);
                result[i] = static_cast<RESULT_TYPE>(m_selfArray[i]);
            }
        }

        return result;
    }
};
}

#endif
