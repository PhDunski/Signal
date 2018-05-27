#include <Signal.hpp>
void exampleFunction(int int){
}
int main(){
    /* définit un signal auquel pourra se connecter n'importe quelle fonction s'attendant
     * à recevoir deux entiers comme paramètre
     */
    Tools::Signal<int, int> sig;
   /* ... */
}
