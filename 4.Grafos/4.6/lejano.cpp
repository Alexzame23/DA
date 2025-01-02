
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
    vector<int> dist;
    //vector<int> tamanoComponente;

    void bfs(Grafo const& g, int origen, int& alcanzables, int ttl) {
        queue<int> q;
        dist[origen] = 0;
        //int dist = 0;
        //vector<int> nodos;

        q.push(origen);
        visitado[origen] = true;
        alcanzables = 0;

        while (!q.empty()) {
            int v = q.front(); q.pop();
            //nodos.push_back(v);

            for (int w : g.ady(v)) {
                if (!visitado[w]) {
                    visitado[w] = true;
                    dist[w] = dist[v] + 1;
                    q.push(w);
                    if(dist[w] <= ttl) alcanzables++;
                }
            }
            //dist++;
        }

    }

public:
    caminosBFS(Grafo const& g, int origen, int& alcanzables, int ttl) : visitado(g.V(), false), dist(g.V(), -1) {
        bfs(g, origen, alcanzables, ttl);
    }

};

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int n,c;
    cin >> n >> c;
   
    if (!std::cin)  // fin de la entrada
        return false;

    Grafo red(n);
    int x, y;

    for(int i = 0; i < c; ++i){
        cin >> x >> y;
        red.ponArista(x-1,y-1);
    }
   
   // resolver el caso posiblemente llamando a otras funciones
    
    int k, origen, ttl, alcanzables = 0;
    cin >> k;

    for(int i = 0; i < k; ++i){
        cin >> origen >> ttl;
        caminosBFS(red,origen-1,alcanzables,ttl);
        cout << n-1-alcanzables << "\n";
    }

    cout << "---\n";
   
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
