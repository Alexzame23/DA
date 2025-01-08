
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

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int n;
    cin >> n;
   
    if (n <= 0)
        return false;

    PriorityQueue<long long int> datos;
    long long int aux;
    for(int i = 0; i < n; ++i){
        cin >> aux;
        datos.push(aux);
    }
        
   
   // resolver el caso posiblemente llamando a otras funciones

    long long int a = 0, b = 0, esfuerzo = 0;
    aux = 0;
    if(datos.size()>1){
        while(datos.size() > 1){
            a = datos.top();
            datos.pop();
            b = datos.top();
            datos.pop();
            aux = a + b;
            esfuerzo += aux;
            datos.push(aux);
        }
    }

   // escribir la solución

    cout << esfuerzo << "\n";

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
