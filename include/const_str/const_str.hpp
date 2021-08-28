#pragma once
#include <iostream>
#include <string>
#include <ph_concepts/concepts.hpp>
//using namespace std;
using namespace ph::concepts;


#define cexpr inline static constexpr




template <Size auto N, Char C = char>
class const_str
{
    size_t m_size;
    C m_str [N];
    
public:
    
    constexpr const_str (C const (& str) [N]) noexcept : m_size (N), m_str()
    {
        std::copy (str, str + N, m_str);
    }
    
    constexpr auto size () const noexcept -> size_t
    {
        return m_size;
    }
    
    const_str (const_str&& other) noexcept : m_size (N), m_str ()
    {
        std::copy (other.m_str, other.m_str + N, m_str);
    }
    
    constexpr const_str (const_str const& other) noexcept : m_size (N), m_str ()
    {
        std::copy (other.m_str, other.m_str + N, m_str);
    }
    
    
    
//    template <int M>
//    constexpr auto operator== (const_str <M> const&) -> bool
//    {
//        return false;
//    }
    

    constexpr auto operator[] (int i) const noexcept -> C
    {
        return m_str [i];
    }
    
    template <size_t J>
    friend constexpr auto operator== (const_str const& lhs, const_str <J> const& rhs) noexcept -> bool
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
    friend constexpr auto operator== (const_str const& lhs, C const(&rhs) [J]) noexcept -> bool
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

    

    constexpr friend auto operator== (const_str const& lhs, C const* rhs) noexcept -> bool
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
    
    friend auto operator<< (std::ostream& os, const_str const& s) noexcept -> std::ostream&
    {
        os << s.m_str;
        return os;
    }
    
    auto c_str () const noexcept -> C const*
    {
        char* ret = (C*) __builtin_alloca (N);
        strcpy (ret, m_str);
        return ret;
    }
    
    constexpr operator C const* () const noexcept
    {
        char* ret = (char*) __builtin_alloca (N);
        strcpy (ret, m_str);
        return ret;
    }
    
    operator std::string () const noexcept
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
    friend std::ostream& operator<< (std::ostream& os, struct _str const& s)
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


namespace ph::concepts
{
    template <template <Size auto, typename...> typename T, Size auto n>
    struct StringHelper <T <n>>
    {
        cexpr bool is_string = requires (T <n> t, size_t i)
        {
            {t [i]} -> Char;
        };
        
        cexpr bool known_bounds = requires (T <n> t)
        {
            {t.size ()} -> Size;
        };
        
        cexpr bool dynamic = requires (T <n> t)
        {
            t = "nej";
        };
        
        static inline constexpr auto size () noexcept -> Size auto
        {
            return n;
        }
    };
}


#undef cexpr
