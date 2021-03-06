#pragma once
#include <iostream>
#include <string>
using namespace std;



template <int N>
class const_str
{
    size_t m_size;
    char m_str [N];
    
public:
    
    constexpr const_str (char const (& str) [N]) : m_size (N), m_str()
    {
        std::copy (str, str + N, m_str);
    }
    
    constexpr auto size () const -> size_t
    {
        return m_size;
    }
    
    const_str (const_str&& other) : m_size (N), m_str ()
    {
        copy (other.m_str, other.m_str + N, m_str);
    }
    
    const_str (const_str const& other) : m_size (N), m_str ()
    {
        copy (other.m_str, other.m_str + N, m_str);
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
    
    template <size_t J>
    friend constexpr auto operator== (const_str const& lhs, const_str <J> const& rhs) -> bool
    {
        if constexpr (N != J)
            return false;
        
        for (int i = 0; i < N; ++i)
        {
            if (lhs.m_str [i] != rhs.m_str[i])
                return false;
        }
        return true;
    }

    
    template <size_t J>
    friend constexpr auto operator== (const_str const& lhs, char const(&rhs) [J]) -> bool
    {
        if constexpr (N != J)
            return false;
        
        for (int i = 0; i < N; ++i)
        {
            if (lhs.m_str [i] != rhs[i])
                return false;
        }
        return true;
        
        return false;
    }

    

    constexpr friend auto operator== (const_str const& lhs, char const* rhs) -> bool
    {
//        cout << strlen(rhs) << endl << N << endl;
        if (strlen(rhs) != N - 1)
            return false;
        
        for (int i = 0; i < N; ++i)
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
    
    auto c_str () const -> char const*
    {
        char* ret = (char*) __builtin_alloca (N);
        strcpy (ret, m_str);
        return ret;
    }
    
    constexpr operator char const* () const
    {
        char* ret = (char*) __builtin_alloca (N);
        strcpy (ret, m_str);
        return ret;
    }
    
    operator string () const
    {
        return m_str;
    }
    
};


template <size_t N>
const_str (char const(& str) [N]) -> const_str <N>;




template <char... c>
struct _str
{
    inline static constexpr char str [sizeof... (c)] {c...};
    friend ostream& operator<< (ostream& os, struct _str const& s)
    {
        os << s.str;
        return os;
    }
};

template <unsigned int N>
constexpr char getch (char const (&s) [N], unsigned int i)
{
    return i >= N ? '\0' : s[i];
}

#define _MACRO(z, n, text) BOOST_PP_COMMA_IF(n) getch (text, n)
#define STR(s) decltype (_str<BOOST_PP_REPEAT (BOOST_PP_LIMIT_REPEAT, _MACRO, s)> {})



/**
namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}


    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);

*/
