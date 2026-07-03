
namespace std {
template < typename __TYPE >
class unique_ptr final
{
    protected:
    __TYPE* m_ptr;
    size_t m_ptrSize;

    public:
    explicit unique_ptr( __TYPE OBJECT ) noexcept
    {
        m_ptr = new __TYPE(OBJECT);
        m_ptrSize = sizeof(m_ptr);
    }

    unique_ptr(
        unique_ptr&& OTHER_UNIQUE_PTR
    ) noexcept 
    {
        if ( this != &OTHER_UNIQUE_PTR ) {
            m_ptr = OTHER_UNIQUE_PTR->m_ptr;
            OTHER_UNIQUE_PTR = nullptr;

            m_ptrSize = sizeof(m_ptr);
        }
    }

    unique_ptr(
        const unique_ptr& OTHER_UNIQUE_PTR
    ) noexcept
    {
        if ( this != OTHER_UNIQUE_PTR ) {
            m_ptr = OTHER_UNIQUE_PTR->m_ptr;
            m_ptrSize = sizeof(m_ptr);
        }
    }

    ~unique_ptr()
    {
        delete m_ptr;
    }

    void operator= ( unique_ptr&& OTHER_UNIQUE_PTR ) = delete;
    void operator= ( const unique_ptr& OTHER_UNIQUE_PTR ) = delete;

    __TYPE& get ( )
    {
        return m_ptr;
    }

    void release ()
    {
        delete m_ptr;

        m_ptr = nullptr;
        m_ptrSize = 0;
    }

    void reset ( __TYPE& OBJECT )
    {
        delete m_ptr;
        m_ptr = new __TYPE(OBJECT);
    }

    void swap ( unique_ptr OTHER_UNIQUE_PTR )
    {
        __TYPE Cpy_stackVal = *OTHER_UNIQUE_PTR->m_ptr;
        
        OTHER_UNIQUE_PTR->m_ptr = m_ptr;
        delete m_ptr;
        m_ptr = new __TYPE(Cpy_stackVal);
    }
};
}
