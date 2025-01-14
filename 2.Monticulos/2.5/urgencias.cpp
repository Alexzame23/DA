
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

struct hospital{
    string paciente;
    int prioridad;
    int entrada;
};

bool operator<(hospital const& a, hospital const& b){
    return (a.prioridad > b.prioridad) || (a.prioridad == b.prioridad) && a.entrada < b.entrada;
}

bool resuelveCaso() {
   
   // leer los datos de la entrada
    
    int n;
    cin >> n;
   
    if (n <= 0)
        return false;
   
   // resolver el caso posiblemente llamando a otras funciones

    char accion;
    int prio=0;
    string nombre;
    PriorityQueue<hospital> h;    

    for(int i = 0; i < n; ++i){
        cin >> accion;
        switch (accion)
        {
        case 'I':
            cin >> nombre >> prio;
            h.push({nombre, prio, i});
            break;
        case 'A':
            cout << h.top().paciente << "\n";
            h.pop();
        default:
            break;
        }
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
