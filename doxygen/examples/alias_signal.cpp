#include <Signal.hpp>
/* Alias de type sur un signal auquel pourra se connecter n'importe quelle
 * fonction n'attendant aucun paramètre
 */
using VoidSignal = Tools::Signal<>;
/* Alias de type sur un signal auquel pourra se connecter n'importe quelle
 * sontction s'attendant à recevoir un entier comme paramètre
 */
using IntSignal = Tools::Signal<int>;
struct Point{
   /* ... */
}; 
/* Alias de type sur un signal auquel pourra se connecter n'importe quelle
 * sontction s'attendant à recevoir un point comme paramètre
 */
using PointSignal = Tools::Signal<Point>;
/* Alias de type sur un signal auquel pourra se connecter n'importe quelle
 * sontction s'attendant à recevoir un point  et un entier comme paramètre
 */
using PointIntSignal = Tools::Signal<Point, int>;
int main(){
   /* la définition des signaux peut alors utiliser les alias de type définis
    */
   VoidSignal sigVoid;
   IntSignal sigInt;
   PointSignal sigPoint;
   PointIntSignal sigPointInt
   /* ... */
}
