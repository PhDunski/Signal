#define  CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <Signal.hpp>
#include <TestingStructs.hpp>
TEST_CASE("Signal works with free functions"){
	Tools::Signal<> sig;
    auto conn=sig.connect(Tests::addOne);
	for(int i=1;i<=4;++i){
        sig();
        REQUIRE(Tests::externValue == i);
    }
}
TEST_CASE("Signal works with free functions with params"){
    Tools::Signal<int> sig;
    Tests::externValue = 0;
    auto conn = sig.connect(Tests::addValue);
    sig(4);
    REQUIRE(Tests::externValue == 4);
}
TEST_CASE("Signal works with static member functions"){
    Tools::Signal<> sig;
    auto conn = sig.connect(Tests::StaticStruct::addOne);
    REQUIRE(Tests::StaticStruct::value == 0);
    for(int i=1; i<=4; ++i){
        sig();
        REQUIRE(Tests::StaticStruct::value == i);
    }
}

TEST_CASE("Signal works wit static member function waiting parameters"){
    Tests::StaticStruct::value = 0;
    Tools::Signal<int> sig;
    auto conn = sig.connect(Tests::StaticStruct::add);
    int total{0};
    for(int i = 1; i<=4; ++i){
        total+=i;
        sig(i);
        REQUIRE(Tests::StaticStruct::value == total);
    }
}
TEST_CASE("Signal works with lamda expression"){
	Tools::Signal<> sig;
	int value{0};
    auto conn = sig.connect([&](){++value;});
    for(int i = 1; i<=4; ++i){
        sig();
        REQUIRE(value == i);
    }
}
TEST_CASE("Signal works with lambda expression waiting parameter"){
    Tools::Signal<int> sig;
    int value{0};
    auto conn = sig.connect([&](int i){value+=i;});
    int total{0};
    for(int i = 1; i<=4; ++i){
        total+=i;
        sig(i);
        REQUIRE(value == total);
    }
}
TEST_CASE("Member function no param"){
    Tests::NoStatic s;
    Tools::Signal<> sig;
    auto conn = sig.connect([&](){s.addOne();});
    for(int i = 1; i<=4; ++i){
        sig();
        REQUIRE(s.value == i);
    }
}
TEST_CASE("Member function param"){

    Tests::NoStatic s;
    Tools::Signal<int> sig;
    auto conn = sig.connect([&](int i){s.add(i);});
    int total=0;
    for(int i = 1; i<=4; ++i){
        sig(i);
        total+=i;
        REQUIRE(s.value == total);
    }
}
TEST_CASE("Signal works with std::bind"){
    
    Tests::NoStatic s;
    Tools::Signal<> sig;
    auto fun = std::bind(&Tests::NoStatic::addOne,&s);
    auto conn =sig.connect(fun);
    for(int i = 1; i<=4; ++i){
        sig();
        REQUIRE(s.value == i);
    }
}
TEST_CASE("Signal works with std::bind with parameters"){
    
    Tests::NoStatic s;
    Tools::Signal<int> sig;
    auto fun = std::bind(&Tests::NoStatic::add, &s, std::placeholders::_1);
    auto conn=sig.connect(fun);
    int total{s.value};
    for(int i = 1; i<=4; ++i){
        sig(5);
        total+=5;
        REQUIRE(s.value == total);
    }
}
