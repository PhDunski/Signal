#define  CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <Signal.hpp>

/** @test ensure connection may be default constructed
  */
TEST_CASE("default connection works"){
	Tools::Connection conn;
	REQUIRE(conn.connected() == false);
	REQUIRE(conn.blocked() == true);
}
/** @test ensure connection may be copied
  */
TEST_CASE("connection copy generate multi calls"){

    Tools::Signal<> sig;
    int value=0;
    auto conn =sig.connect([&](){++value;});
	Tools::Connection c2{conn};
	sig();
	REQUIRE(value == 2);
}
/** @test ensure connection may be assigned to another one
  */
TEST_CASE("connection assignment operator works"){
    Tools::Signal<> sig;
    int value=0;
	Tools::Connection conn;
	{
		
		auto conn2 =sig.connect([&](){++value;});
		conn = conn2;
	}
	sig();
	REQUIRE(value == 1);
}
/** @test enusre connetion assignement generate multi calls
  *
  */
TEST_CASE("Connection assignment generate multi calls"){

    Tools::Signal<> sig;
    int value=0;
	Tools::Connection conn{sig.connect([&](){++value;})};
	auto conn2 = conn;
	sig();
	REQUIRE(value == 2);
}
