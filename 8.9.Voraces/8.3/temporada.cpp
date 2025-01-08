
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
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

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int n,m;
    cin >> n >> m;
   
    if (!std::cin)  // fin de la entrada
        return false;

    PriorityQueue<int, greater<int>> jugadores, equipaciones;
    int aux;

    for(int i = 0; i < n; ++i){
        cin >> aux;
        jugadores.push(aux);
    }

    for(int i = 0; i < m; ++i){
        cin >> aux;
        equipaciones.push(aux);
    }
   
   // resolver el caso posiblemente llamando a otras funciones

    int sol = 0;

    while(!equipaciones.empty() && !jugadores.empty()){
        if(jugadores.top() + 1 >= equipaciones.top() && jugadores.top()-1 <= equipaciones.top()){
            ++sol;
            jugadores.pop();
            equipaciones.pop();
        }
        else if(jugadores.top() > equipaciones.top())   jugadores.pop();
        else if(equipaciones.top() > jugadores.top())   equipaciones.pop();
    }
   
   // escribir la solución

    cout << n - sol << "\n";

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
