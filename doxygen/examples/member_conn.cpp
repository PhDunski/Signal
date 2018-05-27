#include <Signal.hpp>
#include <iostream>
using IntSignal = Tools::Signal<int>;
struct MyStruct{
    MyStruct(int v):value{v}{
    }
    int value;
    void addValue(int i){
        value+=i;
    }
    Tools::Connection conn;
    void connect(IntSignal & sig){
        conn = sig.connect([&](int i){addValue(i);});
    }
};
int main(){
    MyStruct a{5};
    std::cout<<"Starting a value "<<a.value<<"\n";
    Tools::Signal<int> sig;
    sig(5); // a.value stay unchanged since a.addValue isn't connected
    /* prints "Middle a value 5" */
    std::cout<<"Middle a value "<<a.value<<"\n";
    a.connect(sig); // a.addValue is now connected to signal
    sig(10); // calls a.addValue with 10 as parameter
    /* prints "Final a value  15
     * great: 5 + 10 = 15
     */
    std::cout<<"Final a value "<<a.value<<"\n";
    
}
