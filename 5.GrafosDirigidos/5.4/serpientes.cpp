
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class BFSDirigido {
private:
    std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    std::vector<long long int> ant; // ant[v] = último vértice antes de llegar a v
    std::vector<long long int> dist; // dist[v] = aristas en el camino s->v más corto
    long long int s;
    void bfs(Digrafo const& g) {
        std::queue<long long int> q;
        dist[s] = 0; visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            long long int v = q.front(); q.pop();
            for (long long int w : g.ady(v)) {
                if (!visit[w]) {
                    ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
public:
    BFSDirigido(Digrafo const& g, long long int s) : visit(g.V(), false), ant(g.V()), dist(g.V()), s(s) {
        bfs(g);
    }
    bool hayCamino(long long int v) const {
        return visit[v];
    }
    long long int distancia(long long int v) const {
        return dist[v];
    }
    /*Camino camino(long long int v) const {
        if (!hayCamino(v)) throw std::domain_error("No existe camino");
        Camino cam;
        for (long long int x = v; x != s; x = ant[x])
            cam.push_front(x);
        cam.push_front(s);
        return cam;
    }*/
};

bool resuelveCaso() {
   
   // leer los datos de la entrada

    long long int n,m,s,e;
    cin >> n >> m >> s >> e;
   
    if ((n == 0) && (n == 0) && (s == 0) && (e == 0))
      return false;
    
    Digrafo tablero(n*n);
    long long int x,y;
    for(long long int i = 0; i < n*n-1; ++i){
        tablero.ponArista(i,i+1);
    }
    for(long long int i = 0; i < s+e; ++i){
        cin >> x >> y;
        tablero.ponArista(x-1,y-1);
    }
   // resolver el caso posiblemente llamando a otras funciones

    BFSDirigido recorrido(tablero, 0);
    int sol = 0;
    int a = recorrido.distancia(n*n-1);
    if(a != 0){
        sol = a/m;
        if(a%m != 0) ++sol;
    }

    cout << sol << "\n";
   
   // escribir la solución
    //tablero.prlong long int();
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
