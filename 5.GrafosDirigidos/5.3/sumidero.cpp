
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
    std::vector<pair<bool,int>> visit; // visit[v] = ¿hay camino de s a v?
    std::vector<int> ant; // ant[v] = último vértice antes de llegar a v
    std::vector<int> dist; // dist[v] = aristas en el camino s->v más corto
    void bfs(Digrafo const& g, int s) {
        std::queue<int> q;
        dist[s] = 0; visit[s].first = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w].first) {
                    ant[w] = v; dist[w] = dist[v] + 1; visit[w].first = true;
                    visit[w].second++;
                    q.push(w);
                }
                else{
                    visit[w].second++;
                }
            }
        }
    }
public:
    BFSDirigido(Digrafo const& g) : visit(g.V(), {false, 0}), ant(g.V()), dist(g.V()) {
        for(int i = 0; i < g.V(); ++i){
            if(!visit[i].first)
                bfs(g, i);
        }

    }
    bool hayCamino(int v) const {
        return visit[v].first;
    }
    int distancia(int v) const {
        return dist[v];
    }
    int grado(int v) const{
        return visit[v].second;
    }
    /*Camino camino(int v) const {
        if (!hayCamino(v)) throw std::domain_error("No existe camino");
        Camino cam;
        for (int x = v; x != s; x = ant[x])
            cam.push_front(x);
        cam.push_front(s);
        return cam;
    }*/
};

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int v,a;
    cin >> v >> a;
   
    if (!std::cin)  // fin de la entrada
        return false;
    
    int x,y;
    Digrafo g(v);

    for(int i = 0; i < a; ++i){
        cin >> x >> y;
        g.ponArista(x,y);
    }

   // resolver el caso posiblemente llamando a otras funciones

    BFSDirigido sol(g);
    int aux = 0;
    queue<int> sumideros;

    for(int i = 0; i < v; ++i){
        aux = sol.grado(i);
        if(aux == v - 1) sumideros.push(i);
    }
   
   // escribir la solución

    if(!sumideros.empty()){
        cout << "SI ";
        while(!sumideros.empty()){
            cout << sumideros.front() << " ";
            sumideros.pop();
        }
        cout << "\n";
    } 
   else cout << "NO\n";

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
