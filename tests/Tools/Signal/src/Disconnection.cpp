#define  CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <Signal.hpp>
TEST_CASE("connection disconnect works"){
	
    Tools::Signal<> sig;
    int value=0;
    auto conn =sig.connect([&](){++value;});
	REQUIRE(conn.connected() == true);
	conn.disconnect();
	REQUIRE(conn.connected() == false);
    sig();
    REQUIRE(value == 0);

}
TEST_CASE("Connection advised on signal desruction"){
   int value=0;
	Tools::Connection conn;
	{
		Tools::Signal<> sig;
		conn = sig.connect([&](){++value;});
		REQUIRE(conn.connected()==true);
	}
	REQUIRE(conn.connected()==false);
}
