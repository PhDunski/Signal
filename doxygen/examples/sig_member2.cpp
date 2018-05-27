#include <Signal.hpp>
#include <iostream>
class MyClass{
public:
    /* un alias de type sur le slot qui sera utilisé 
     * pour nous faciliter la vie
     */
    using slot_type = typename Tools::Signal<int>::slot_type;
    Toos::Connection onSignalEmission(slot_type slot){
        return sig.connect(slot);
    }
private:
   Tools::Signal<int> sig;
};

int main(){
    MyClass obj;
   /* nous pouvons transmettre obj à n'importe quelle fonction s'attendant
    * à recevoir une référence sur un objet de type MyClass afin d'y connecter
    * un slot particulier
    */
    
}
