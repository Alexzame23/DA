
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct super{
    int id;
    int segs;
};

bool operator<(super const& a, super const& b){
    return (a.segs < b.segs) || (a.segs == b.segs) && a.id < b.id;
}


bool resuelveCaso() {
   
   // leer los datos de la entrada
    int n,c;
    cin >> n >> c;
    
    if (n <= 0 && c <= 0)
        return false;

   
    PriorityQueue<super> cajas;
    for(int i = 0; i < n; ++i){
        cajas.push({i+1,0});
    }
   
   // resolver el caso posiblemente llamando a otras funciones
    
    int segundos = 0;
    super aux;

    for(int i = 0; i < c; ++i){
        cin >> segundos;
        aux = cajas.top();
        cajas.pop();
        cajas.push({aux.id, aux.segs + segundos});
    }
   
   // escribir la solución
    
    cout << cajas.top().id << "\n";

   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
