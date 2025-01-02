
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class caminosBFS {
private:
    vector<bool> visitado;
    vector<int> tamanoComponente;

    void bfs(Grafo const& g, int origen) {
        queue<int> q;
        vector<int> nodos;

        q.push(origen);
        visitado[origen] = true;
        int tamano = 0;

        while (!q.empty()) {
            int v = q.front(); q.pop();
            nodos.push_back(v);
            tamano++;

            for (int w : g.ady(v)) {
                if (!visitado[w]) {
                    visitado[w] = true;
                    q.push(w);
                }
            }
        }

        // Actualizar los tamaños para todos los nodos de la componente
        for (int nodo : nodos) {
            tamanoComponente[nodo] = tamano;
        }
    }

public:
    caminosBFS(Grafo const& g) : visitado(g.V(), false), tamanoComponente(g.V(), 0) {
        for (int i = 0; i < g.V(); ++i) {
            if (!visitado[i]) {
                bfs(g, i);
            }
        }
    }

    int obtenerTamano(int nodo) const {
        return tamanoComponente[nodo];
    }
};

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int n, m;
    cin >> n >> m;
   
    if (!std::cin)  // fin de la entrada
        return false;
   
    Grafo usuarios(n);
    int nug, x, y;

    for(int i = 0; i < m; ++i){
        cin >> nug;
        if(nug > 0) cin >> x;
        for(int j = 1; j < nug; ++j){
            cin >> y;
            usuarios.ponArista(x-1,y-1);
        }
    }

   // resolver el caso posiblemente llamando a otras funciones
    caminosBFS sol(usuarios);

    for(int i = 0; i < n; ++i){
        cout << sol.obtenerTamano(i) << " ";
    }
    cout << "\n";
   
   // escribir la solución

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
