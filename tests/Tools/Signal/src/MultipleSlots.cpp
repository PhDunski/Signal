#define  CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <Signal.hpp>
#include <TestingStructs.hpp>
TEST_CASE("Multiple static functions No param"){
     Tools::Signal<> sig;
    auto conn1 = sig.connect(&Tests::StaticStruct::addOne);
    auto conn2 = sig.connect(&Tests::StaticStruct::removeOne);
    REQUIRE(Tests::StaticStruct::value == 0);
    for(int i=1; i<=4; ++i){
        sig();
        REQUIRE(Tests::StaticStruct::value == 0);
    }

}

TEST_CASE("Multiple Static functions param"){
	Tools::Signal<int> sig;
    auto conn1 = sig.connect(&Tests::StaticStruct::add);
    auto conn2 = sig.connect(&Tests::StaticStruct::remove);
    REQUIRE(Tests::StaticStruct::value == 0);
    for(int i=1; i<=4; ++i){
        sig(i);
        REQUIRE(Tests::StaticStruct::value == 0);
    }
}
TEST_CASE("Multiple member functions no param"){
    Tests::NoStatic s;
	Tools::Signal<> sig;
    auto conn1 = sig.connect([&](){s.addOne();});
    auto conn2 = sig.connect([&](){s.removeOne();});
    for(int i = 1; i<=4; ++i){
        sig();
        REQUIRE(s.value == 0);
    }
}
TEST_CASE("Multiple member functions param"){
    Tests::NoStatic s;
    Tools::Signal<int> sig;
    auto conn1 = sig.connect([&](int i){s.add(i);});
    auto conn2 = sig.connect([&](int i){s.remove(i);});
    for(int i = 1; i<=4; ++i){
        sig(i);
        REQUIRE(s.value == 0);
    }
}
TEST_CASE("Multiple free functions no param"){
     Tools::Signal<> sig;
     auto conn1=sig.connect(&Tests::addOne);
     auto conn2=sig.connect(&Tests::removeOne);
    for(int i = 1; i<=4; ++i){
        sig();
        REQUIRE(Tests::externValue== 0);
    }
}

TEST_CASE("Multiple free functions param"){
     Tools::Signal<int> sig;
     auto conn1=sig.connect(&Tests::addValue);
     auto conn2=sig.connect(&Tests::removeValue);
    for(int i = 1; i<=4; ++i){
        sig(i);
        REQUIRE(Tests::externValue== 0);
    }
}
TEST_CASE("Slot combinaison 1"){
     Tools::Signal<> sig;
     Tests::StaticStruct::value = 0;
     Tests::externValue = 0;
     Tests::NoStatic s;
     auto conn1 = sig.connect(&Tests::StaticStruct::addOne);
     auto conn2 = sig.connect([&](){s.addOne();});
     auto conn3 = sig.connect(&Tests::addOne);
     for(int i = 1; i<=4;++i){
        sig();
        REQUIRE(Tests::externValue == i);
        REQUIRE(Tests::StaticStruct::value == i);
        REQUIRE(s.value == i);
     }
}

TEST_CASE("Slot combinaison 2"){
     Tools::Signal<int> sig;
     Tests::StaticStruct::value = 0;
     Tests::externValue = 0;
     Tests::NoStatic s;
     auto conn1 = sig.connect(Tests::StaticStruct::add);
     auto conn2 = sig.connect([&](int i){s.add(i);});
     auto conn3 = sig.connect(Tests::addValue);
     int total{0};
     for(int i = 1; i<=4;++i){
        total+= i;
        sig(i);
        REQUIRE(Tests::externValue == total);
        REQUIRE(Tests::StaticStruct::value == total);
        REQUIRE(s.value == total);
     }

}
TEST_CASE("Same Slot called") {
	Tools::Signal<> sig;
	int value{ 0 };
	auto conn1 = sig.connect([&]() { ++value; });
	auto conn2 = sig.connect([&]() { ++value; });
	sig();
	REQUIRE(value == 2);
}