
        uint32_t len = arr.size();
        array = new TYPE[len];

        for ( uint32_t i { 0u }; i < len; i++ ) {
            array[i] = arr[i];
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
            if ( std::is_integral_v<TYPE> ) {
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

    uint32_t len ()
    {
        return size;
    }

    TYPE *&data ()
    {
        return &*array;
    }

    bool is_sorted ()
    {
        for ( uint32_t i { 1u }; i < size; i++ ) {
            if ( array[i] > array[i-1u] ) return false; 
        }
        return true;
    }

    void sort ()
    {
        while (!is_sorted()) {
            for ( uint32_t i { 1u }; i < size; i++ ) {
                if ( array[i] > array[i-1u] ) {
                    TYPE X1 = array[i];
                    TYPE X2 = array[i-1u];
                    array[i] = X2;
                    array[i-1] = X1;
                }
            }
        }
    }

    void resize ( uint32_t x )
    {
        TYPE stackArr[x];
        if ( x > size ) {
            for ( uint32_t i { 0u }; i < x; i++ ) {
                if ( x-1 < size-1 ) {
                    if ( std::is_integral_v<TYPE> ) {
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

        if ( std::is_integral_v<TYPE> ) {
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

    void clear ()
    {
        if (std::is_integral_v<TYPE>) {
            for ( TYPE &i : array ) {
                i = 0;
            }
        } else {
            for ( TYPE &i : array ) {
                i = nullptr;
            }
        }
    }

    void emplace ( TYPE& value, uint32_t index )
    {
        if (index > size - 1u) {
            TYPE stackArray[index];
            for (uint32_t i { 0u }; i < size; i++) {
                stackArray[i] = array[i];
            }

            if (std::is_integral_v<TYPE>) {
                for ( TYPE &i : array ) {
                    i = 0;
                }
            } else {
                for ( TYPE &i : array ) {
                    i = nullptr;
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

    TYPE &front ()
    {
        return *array[0];
    }

    TYPE &back ()
    {
        return *array[size-1u];
    }

    TYPE &at ( uint32_t index )
    {
        if ( index > size ) throw std::out_of_range("idiot");
        return *array[index];
    }

    TYPE &operator[] ( uint32_t index )
    {
        return *array[index];
    }

    void operator= ( vector &vec )
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
    void operator+ ( vector &vec )
    {
        NUMBER_TYPE *arr = vec.data();
        uint32_t length = vec.len();
        if (!(std::is_integral_v<TYPE> && std::is_integral_v<NUMBER_TYPE>)) throw std::domain_error("LOOOOOL");

        if (length > size) {
            for (uint32_t i { 0u }; i < size; i++) {
                array[i] += static_cast<TYPE>(arr[i]);
            }
        } else if (size > length) {
            for (uint32_t i { 0u }; i < length; i++) {
                array[i] += static_cast<TYPE>(arr[i]);
            }
        } else {
            for (uint32_t i { 0u }; i < size; i++) {
                array[i] += static_cast<TYPE>(arr[i]);
            }
        }
    }

    template < typename NUMBER_TYPE >
    void operator- ( vector &vec )
    {
        NUMBER_TYPE *arr = vec.data();
        uint32_t length = vec.len();
        if (!(std::is_integral_v<TYPE> && std::is_integral_v<NUMBER_TYPE>)) throw std::domain_error("LOOOOOL");

        if (length > size) {
            for (uint32_t i { 0u }; i < size; i++) {
                array[i] -= static_cast<TYPE>(arr[i]);
            }
        } else if (size > length) {
            for (uint32_t i { 0u }; i < length; i++) {
                array[i] -= static_cast<TYPE>(arr[i]);
            }
        } else {
            for (uint32_t i { 0u }; i < size; i++) {
                array[i] -= static_cast<TYPE>(arr[i]);
            }
        }
    }

    template < typename NUMBER_TYPE >
    void operator* ( vector &vec )
    {
        NUMBER_TYPE *arr = vec.data();
        uint32_t length = vec.len();
        if (!(std::is_integral_v<TYPE> && std::is_integral_v<NUMBER_TYPE>)) throw std::domain_error("LOOOOOL");

        if (length > size) {
            for (uint32_t i { 0u }; i < size; i++) {
                array[i] *= static_cast<TYPE>(arr[i]);
            }
        } else if (size > length) {
            for (uint32_t i { 0u }; i < length; i++) {
                array[i] *= static_cast<TYPE>(arr[i]);
            }
        } else {
            for (uint32_t i { 0u }; i < size; i++) {
                array[i] *= static_cast<TYPE>(arr[i]);
            }
        }
    }

    template < typename NUMBER_TYPE >
    void operator/ ( vector &vec )
    {
        NUMBER_TYPE *arr = vec.data();
        uint32_t length = vec.len();
        if (!(std::is_integral_v<TYPE> && std::is_integral_v<NUMBER_TYPE>)) throw std::domain_error("LOOOOOL");

        if (length > size) {
            for (uint32_t i { 0u }; i < size; i++) {
                array[i] /= static_cast<TYPE>(arr[i]);
            }
        } else if (size > length) {
            for (uint32_t i { 0u }; i < length; i++) {
                array[i] /= static_cast<TYPE>(arr[i]);
            }
        } else {
            for (uint32_t i { 0u }; i < size; i++) {
                array[i] /= static_cast<TYPE>(arr[i]);
            }
        }
    }

    static void destroy ( vector &vec )
    {
        delete vec;
    }
};
