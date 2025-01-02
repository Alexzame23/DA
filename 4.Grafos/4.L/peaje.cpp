
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


class caminoBFS {
private:
    std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    std::vector<int> ant; // ant[v] = último vértice antes de llegar a v
    std::vector<int> dist; // dist[v] = aristas en el camino s-v más corto
    int s;
    void bfs(Grafo const& g) {
        std::queue<int> q;
        dist[s] = 0; visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
public:
    caminoBFS(Grafo const& g, int s) : visit(g.V(), false),
    ant(g.V()), dist(g.V()), s(s) {
        bfs(g);
    }
    // ¿hay camino del origen a v?
    bool hayCamino(int v) const {
        return visit[v];
    }
    // número de aristas entre s y v
    int distancia(int v) const {
        return dist[v];
    }
  /*  // devuelve el camino más corto desde el origen a v (si existe)
    vector<int> camino(int v) const {
        if (!hayCamino(v)) throw std::domain_error("No existe camino");
        vector<int> cam;
        for (int x = v; x != s; x = ant[x])
            cam.push_front(x);
        cam.push_front(s);
        return cam;
    }*/
};


bool resuelveCaso() {
   
   // leer los datos de la entrada
    int n,c,alex,lucas,trabajo;
    cin >> n >> c >> alex >> lucas >> trabajo;
   
    if (!std::cin)  // fin de la entrada
        return false;
    
    Grafo calles(n);
    int x,y;

    for(int i = 0; i < c; ++i){
        cin >> x >> y;
        calles.ponArista(x-1,y-1);
    }

   // resolver el caso posiblemente llamando a otras funciones

    caminoBFS cAlex(calles, alex-1);
    caminoBFS cLucas(calles, lucas-1);
    caminoBFS cTrabajo(calles, trabajo-1);

    int aux, min = cAlex.distancia(0) + cLucas.distancia(0) + cTrabajo.distancia(0);
    for(int i = 1; i < n; ++i){
        aux = cAlex.distancia(i) + cLucas.distancia(i) + cTrabajo.distancia(i);

        if(aux < min)
            min = aux;
    }
   
   // escribir la solución

   cout << min << "\n";

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
