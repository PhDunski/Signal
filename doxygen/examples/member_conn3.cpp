#include <Signal.hpp>
#include <iostream>
using IntSignal = Tools::Signal<int>;
struct MyStruct{
    MyStruct(int v, IntSignal & sig):value{v}{
        conn = sig.connect([&](int i){addValue(i);});
    }
    int value;
    void addValue(int i){
        value+=i;
    }
    Tools::Connection conn;
};
int main(){
    Tools::Signal<int> sig;
    MyStruct a{5, sig};
    std::cout<<"Starting a value "<<a.value<<"\n";
    sig(10); // calls a.addValue with 10 as parameter
    /* prints "Final a value  15
     * great: 5 + 10 = 15
     */
    std::cout<<"Final a value "<<a.value<<"\n";
    
}
