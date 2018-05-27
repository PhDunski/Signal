#define  CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <Signal.hpp>
/** @test ensure an signal can be blocked by the connection
  */
TEST_CASE("connection blocked"){
    Tools::Signal<> sig;
    int value=0;
    auto conn =sig.connect([&](){++value;});
    sig();
    REQUIRE(value == 1);
    conn.block();
    sig();
    REQUIRE(value ==1);

}
/** @test ensure an signal can be blocked by the signal himself
  */
TEST_CASE("Signal blocked"){
    Tools::Signal<> sig;
    int value=0;
    auto conn =sig.connect([&](){++value;});
    sig();
    REQUIRE(value == 1);
    sig.block();
    sig();
    REQUIRE(value ==1);

}


/** @test ensure an signal can be unblocked by the connection
  */
TEST_CASE("connection unblocked"){
    Tools::Signal<> sig;
    int value=0;
    auto conn =sig.connect([&](){++value;});
    conn.block();
    sig();
    conn.unblock();
    sig();
    REQUIRE(value ==1);

}
/** @test ensure an signal can be unblocked by the signal himself
  */
TEST_CASE("Signal unblocked"){
    Tools::Signal<> sig;
    int value=0;
    auto conn =sig.connect([&](){++value;});
    sig();
    sig.block();
    sig();
	sig.unblock();
    sig();
    REQUIRE(value ==2);

}
