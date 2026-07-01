#ifndef INITIALISERLIST_HPP
#define INITIALLISTERLIST_HPP

namespace std {
template < typename _TYPE >
struct initialiser_list {
    private:
    const _TYPE* m_begin;
    const _TYPE* m_end;

    public:
    constexpr initialiser_list (const _TYPE* BEGIN, 
        const _TYPE* END) : m_begin(BEGIN), 
        m_end(END) {}
    
    constexpr const _TYPE* begin () const
    { 
        return m_begin;
    }

    constexpr const _TYPE* end () const
    {
        return m_end;
    }

    constexpr auto size () const
    {
        return m_end - m_begin;
    }
};
}

#endif
