#define  CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <Signal.hpp>
#include <TestingStructs.hpp>
TEST_CASE("scope check"){
    Tests::NoStatic s;
    Tools::Signal<> sig;
	{
		auto conn= sig.connect([&](){s.addOne();});
		sig();
		REQUIRE(s.value == 1);
    }
	sig();
	REQUIRE(s.value == 1);
}
