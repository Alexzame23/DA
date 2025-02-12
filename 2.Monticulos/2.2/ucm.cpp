
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

struct usuarios
{
    int id;
    int prioridad;
    int periodicidad;
};

bool operator<(usuarios const& a, usuarios const& b){
    return a.prioridad < b.prioridad || (a.prioridad == b.prioridad && a.id < b.id);
}


bool resuelveCaso() {
   
   // leer los datos de la entrada
    int n;
    cin >> n;
   
    if (n <= 0)
        return false;
    
    PriorityQueue<usuarios> users;
    int a,b;
    for(int i = 0; i < n; ++i){
        cin >> a >> b;
        users.push({a,b,b});
    }
   
   // resolver el caso posiblemente llamando a otras funciones
    int k;
    usuarios aux;
    cin >> k;
    for(int i = 0; i < k; ++i){
        cout << users.top().id << "\n";
        aux = users.top();
        users.pop();
        users.push({aux.id, (aux.prioridad + aux.periodicidad) , aux.periodicidad});
    }
   
   // escribir la solución
    cout << "---\n";

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
