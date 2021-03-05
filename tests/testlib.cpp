#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
//#include <phulkan_generator/gpu.hpp>
#include <const_str/const_str.hpp>


using namespace std;


consteval int kiss (){return 0;}

TEST_CASE( "Quick check", "[kiss]" ) {
    constexpr auto s1 = const_str {"hej"};
    char const* s2 = s1;
    cout << s2 << endl;
    string s3 = s1;
    cout << s3 << endl;
//      cout << GPU_0_MAX_IMAGE_DIMENSION_1D << endl;
//    cout << gpu<0>::features::fillModeNonSolid << endl;
	std::cout << "hi" << std::endl;
    REQUIRE( kiss () == 0 );
}


