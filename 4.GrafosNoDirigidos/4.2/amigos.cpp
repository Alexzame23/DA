
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <deque>
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

class CaminosDFS {
private:
    vector<bool> visitados; // Marcador de nodos visitados
    int tamano;

    void dfs(Grafo const& g, int v) {
        visitados[v] = true;
        tamano++;
        for (int w : g.ady(v)) {
            if (!visitados[w]) {
                dfs(g, w);
            }
        }
    }

public:
    CaminosDFS(Grafo const& g, int& maxTamano) : visitados(g.V(), false), tamano(0) {
        for (int v = 0; v < g.V(); ++v) {
            if (!visitados[v]) {
                tamano = 0;
                dfs(g, v);
                maxTamano = max(maxTamano, tamano);
            }
        }
    }
};

void resuelveCaso() {
   
   // leer los datos de la entrada
   int n,m,x,y;

   cin >> n >> m;

   Grafo amigos(n);

   for(int i = 0; i < m; ++i){
        cin >> x >> y;
        amigos.ponArista(x-1,y-1);
   }
   int sol = 0;
   CaminosDFS dfs(amigos,sol);

   // resolver el caso posiblemente llamando a otras funciones
   
   // escribir la solución
   cout << sol << "\n";
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
