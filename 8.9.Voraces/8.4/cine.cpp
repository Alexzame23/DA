
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
    int n;
    cin >> n;
   
    if (n <= 0)
        return false;
    
    vector<int> inicios(n);
    char puntos;
    int auxh, auxm;
    vector<int> duracion(n);

    for(int i = 0; i < n; ++i){
        cin >> auxh;
        cin >> puntos;
        cin >> auxm;
        inicios[i] = (auxh*60) + auxm;
        cin >> auxm;
        duracion[i] = auxm;
    }
    
   
   // resolver el caso posiblemente llamando a otras funciones
    int sol = (n > 0) ? 1 : 0;
    
    for(int i = 0; i < n-1; ++i){
        if((inicios[i] + duracion[i]) + 10 <= inicios[i+1]) ++sol;
    }
   
   // escribir la solución

    cout << sol << "\n";

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
