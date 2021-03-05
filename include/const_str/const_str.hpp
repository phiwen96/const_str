#pragma once
#include <iostream>
using namespace std;

template <int N>
class const_str
{
    size_t m_size;
    char m_str [N];
    
public:
    
    consteval const_str (char const(& str) [N]) : m_size (N), m_str()
    {
        std::copy (str, str + N, m_str);
    }
    
    consteval auto size () const -> size_t
    {
        return m_size;
    }
    
//    template <int M>
//    constexpr auto operator== (const_str <M> const&) -> bool
//    {
//        return false;
//    }
    

    constexpr auto operator[] (int i) const -> char
    {
        return m_str [i];
    }
    
    template <size_t I, size_t J>
    friend constexpr auto operator== (const_str <I> const& lhs, const_str <J> const& rhs) -> bool
    {
        if constexpr (I != J)
            return false;
        
        for (int i = 0; i < N; ++i)
        {
            if (lhs.m_str [i] != rhs.m_str[i])
                return false;
        }
        return true;
    }

    
    template <size_t I, size_t J>
    friend constexpr auto operator== (const_str <I> const& lhs, char const(&rhs) [J]) -> bool
    {
        if constexpr (I != J)
            return false;
        
        for (int i = 0; i < I; ++i)
        {
            if (lhs.m_str [i] != rhs[i])
                return false;
        }
        return true;
        
        return false;
    }

    
    template <size_t M>
    friend auto operator== (const_str <M> const& lhs, char const* rhs) -> bool
    {
        if (strlen(rhs) != M)
            return false;
        
        for (int i = 0; i < M; ++i)
        {
            if (lhs.m_str [i] != rhs[i])
                return false;
        }
        return true;
    }
    
    friend auto operator<< (ostream& os, const_str const& s) -> ostream&
    {
        os << s.m_str;
        return os;
    }
};
