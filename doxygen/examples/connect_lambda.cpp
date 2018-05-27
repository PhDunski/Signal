#include <Signal.hpp>
#include <iostream>
int main(){
    int localValue{0};
    /* prints "Starting value 0" */
    std::cout<<"Starting value "<<localValue<<"\n";
    Tools::Signal<int> sig;
    auto conn = sig.connect([&](int i){localValue+=i;});
    sig(5);// calls the lambda expression with 5 as parameter
    /* prints "Final value 5".  
     * Great : 0 + 5 = 5
     */
    std::cout<<"Final value "<<localValue<<"\n";
}
