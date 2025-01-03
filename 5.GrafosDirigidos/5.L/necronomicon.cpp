
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

class CicloDirigido {
private:
    std::vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
    std::vector<int> ant; // ant[v] = vértice anterior en el camino a v
    std::vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
    //deque<int> _ciclo; // ciclo dirigido (vacío si no existe)         //NO IMPORTA EN ESTE EJERCICIO
    bool hayciclo;

    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (hayciclo) // si hemos encontrado un ciclo terminamos
                return;
            if (!visit[w]) { // encontrado un nuevo vértice, seguimos
                ant[w] = v; dfs(g, w);
            }
            else if (apilado[w]) { // hemos detectado un ciclo
                // se recupera retrocediendo
                hayciclo = true;
                /*for (int x = v; x != w; x = ant[x])       //No necesario ya que no necesitamos saber el orden del ciclo
                    _ciclo.push_front(x);
                _ciclo.push_front(w); _ciclo.push_front(v);*/
            }
        }
        apilado[v] = false;
    }
public:
    CicloDirigido(Digrafo const& g) : visit(g.V(), false), ant(g.V()),
        apilado(g.V(), false), hayciclo(false) {
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v])
                dfs(g, v);
    }
    bool hayCiclo() const { return hayciclo; }
    //deque<int> const& ciclo() const { return _ciclo; }
};

class BFSDirigido {
private:
    std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    std::vector<int> ant; // ant[v] = último vértice antes de llegar a v
    std::vector<int> dist; // dist[v] = aristas en el camino s->v más corto
    long long int s;
    void bfs(Digrafo const& g) {
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
    BFSDirigido(Digrafo const& g, int s) : visit(g.V(), false), ant(g.V()), dist(g.V()), s(s) {
        bfs(g);
    }
    bool hayCamino(int v) const {
        return visit[v];
    }
    int distancia(int v) const {
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
    int l;
    cin >> l;
   
    if (!std::cin)  // fin de la entrada
        return false;
    
    Digrafo instrucciones(l+1);
    char aux;
    int y;
    for(int i = 0; i < l; ++i){
        cin >> aux;
        switch (aux)
        {
        case 'A':
            instrucciones.ponArista(i, i+1);
            break;
        case 'C':
            instrucciones.ponArista(i,i+1);
            cin >> y;
            instrucciones.ponArista(i,y-1);
            break;
        case 'J':
            cin >> y;
            instrucciones.ponArista(i,y-1);
            break;        
        default:
            break;
        } 
    }

   // resolver el caso posiblemente llamando a otras funciones

    BFSDirigido finaliza(instrucciones, 0);
    if(finaliza.hayCamino(l)){
        CicloDirigido ciclo(instrucciones);
        if(ciclo.hayCiclo()) cout << "A VECES\n";
        else cout << "SIEMPRE\n";
    }
    else{
        cout << "NUNCA\n";
    }
   //instrucciones.print();
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
