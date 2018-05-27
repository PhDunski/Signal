#include <Signal.hpp>
#include <iostream>
struct MyStruct{
   static int staticValue;
   static void addValue(int toAdd){
        staticValue+=toAdd;
   }
};
int MyStruct::staticValue = 0;
int main(){
    /* prints "Starting value 0" */
    std::cout<<"Starting value "<<MyStruct::staticValue<<"\n";
    Tools::Signal<int> sig;
    auto conn = sig.connect(MyStruct::addValue);
    sig(5);// calls MyStruct::addValue with 5 as parameter
    /* prints "Final value 5".  
     * Great : 0 + 5 = 5
     */
    std::cout<<"Final value "<<MyStruct::staticValue<<"\n";
}
