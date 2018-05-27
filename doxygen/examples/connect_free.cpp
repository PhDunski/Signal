#include <Signal.hpp>
#include <iostream>
int externValue{0};
void addValue(int i){
    externValue+=i;
}
int main(){
    Tools::Signal<int> sig;
    sig.connect(addValue);
    /* prints "Starting value 0" */
    std::cout<<"Starting value "<<externValue<<"\n";
    sig(5); // calls addValue with 5 as parameter
    /* prints "Final value 5".  
     * Great : 0 + 5 = 5
     */
    std::cout<<"Final value "<<externValue<<"\n";

}
