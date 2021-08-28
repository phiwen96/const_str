// #include "test_co"
#include <const_str/const_str.hpp>
#include <catch2/catch.hpp>
#include <ph_concepts/concepts.hpp>

using namespace ph::concepts;
using namespace ph;
using std::cout, std::endl;

SCENARIO ("main testing const_expr", "[construction]")
{
    SECTION ("default", "[construction]")
    {
        constexpr auto str = const_str {""};
    }
    
    SECTION ("move", "[construction]")
    {
        constexpr auto s_0 = const_str {"hej"};
        
        REQUIRE (not StringHelper <const_str <3>> {}.dynamic);
        REQUIRE (StringHelper <const_str <3>> {}.is_string);

        
        SECTION ("copy")
        {
            constexpr auto s_1 = s_0;
        }
    }
}

