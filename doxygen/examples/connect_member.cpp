#include <Signal.hpp>
#include <functional>
#include <iostream>

struct MyStruct{
    MyStruct(int v):value{v}{
    }
    int value;
    void addValue(int i){
        value+=i;
    }
};
int main(){
    MyStruct a{0};
    MyStruct b{10};
    /* prints "Starting a value 0" */
    std::cout<<"Starting a value "<<a.value<<"\n";
    /* prints "Starting b value 10" */
    std::cout<<"Starting b value "<<b.value<<"\n";
    Tools::Signal<int> sig;
    /* connects a.value function to sig */
    auto connA = sig.connect([&](int i){a.addValue(i);});
    /* connects b.value function to sig */
    auto connb = sig.connect([&](int i){b.addValue(i);});
    sig(5); // calls a.addValue and b.addValue with 5 as parameter
    /* prints "Final a value 5".  
     * Great : 0 + 5 = 5
     */
    std::cout<<"Final a value "<<a.value<<"\n";
    /* prints "Final b value 15".  
     * Great : 10 + 5 = 15
     */
    std::cout<<"Final b value "<<b.value<<"\n";
    
}
