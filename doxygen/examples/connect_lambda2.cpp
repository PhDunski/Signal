#include <Signal.hpp>
#include <iostream>
int externValue{0};
void addValue(int i, int j){
    externValue = i + j;
}
struct MyStruct{
    static int staticValue;
    static void addValue(int i, int j){
        staticValue = i + j;
    }
};
int MyStruct::staticValue = 0;
int main(){
    /* prints "Starting external value 0" */
    std::cout<<"Starting external value "<<externValue<<"\n";
    /* prints "Starting static value 0" */
    std::cout<<"Starting static value "<<MyStruct::staticValue<<"\n";
    Tools::Signal<int> sig;
    auto conn =sig.connect([](int i){addValue(i, 9);});
    auto conn2 =sig.connect([](int i){MyStruct::addValue(i, 10);});
    sig(5);// calls MyStruct::addValue with 5 as parameter
           // calls addValue free function with 5 as parameter
    /* prints "Final external value 14".  
     * Great : 5 + 9 = 14
     */
    std::cout<<"Final external value "<<externValue<<"\n";
    /* prints "Final static value 15".  
     * Great : 5 + 10 = 15
     */
    std::cout<<"Final static value "<<MyStruct::staticValue<<"\n";
}
