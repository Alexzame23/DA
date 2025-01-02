
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//#include "../grafo.h"  // propios o los de las estructuras de datos de clase
#include "Grafo.h"
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

 bool ciclo(int nodo, int padre, Grafo const& grafo, vector<bool>& visitado) {
    visitado[nodo] = true;

    for (int vecino : grafo.ady(nodo)) {
        if (!visitado[vecino]) {
            if (ciclo(vecino, nodo, grafo, visitado)) {
                return true;
            }
        } else if (vecino != padre) {
            return true; // Encontramos un ciclo
        }
    }
    return false;
}

bool esLibre(Grafo const& grafo) {
    int V = grafo.V();
    int A = grafo.A();

    // Si el número de aristas no es V-1, no puede ser un árbol
    if (A != V - 1) {
        return false;
    }

    // Verificar conectividad y ciclos con DFS
    vector<bool> visitado(V, false);
    if (ciclo(0, -1, grafo, visitado)) {
        return false; // Tiene ciclos
    }

    // Verificar si todos los nodos fueron visitados (conexidad)
    for (bool v : visitado) {
        if (!v) {
            return false; // No todos los nodos son alcanzables
        }
    }

    return true;
}

bool resuelveCaso() {

    int v,a;
    cin >> v >> a;

    if (!std::cin)  // fin de la entrada
        return false;

    Grafo grafo(v);
    int x,y;

    for(int i = 0; i < a; i++){
        cin >> x >> y;
        grafo.ponArista(x,y);
    }

    // leer los datos de la entrada
    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución

    if (esLibre(grafo)) {
            cout << "SI" << endl;
        } else {
            cout << "NO" << endl;
        }

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
