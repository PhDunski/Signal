#include <Signal.hpp>
#include <iostream>
class MyClass{
public:
   Tools::Signal<int> sig;
};

int main(){
    MyClass obj;
   /* nous pouvons transmettre obj.sig à n'importe quelle fonction s'attendant
    * à recevoir une référence sur un objet de type Tools::Signal<int> afin d'y 
    * connecter un slot particulier
    */
    
}
