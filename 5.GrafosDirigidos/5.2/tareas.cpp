
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <deque>
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

class OrdenTopologico {
private:
    std::vector<bool> visit;
    std::deque<int> _orden; // ordenación topológica
    void dfs(Digrafo const& g, int v) {
        visit[v] = true;
        for (int w : g.ady(v))
            if (!visit[w])
                dfs(g, w);
        _orden.push_front(v);
    }
public:
    // g es DAG
    OrdenTopologico(Digrafo const& g) : visit(g.V(), false) {
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v])
                dfs(g, v);
    }
    // devuelve la ordenación topológica
    std::deque<int> const& orden() const {
        return _orden;
    }

};

bool resuelveCaso() {

    // leer los datos de la entrada
    int n, m;
    cin >> n >> m;

    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo tareas(n);
    int x, y;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        tareas.ponArista(x - 1, y - 1);
    }

    // resolver el caso posiblemente llamando a otras funciones

    CicloDirigido ciclo(tareas);

    if (ciclo.hayCiclo()) {
        cout << "IMPOSIBLE\n";
    }
    else {
        OrdenTopologico sol(tareas);
        deque<int> aux = sol.orden();

        while (!aux.empty()) {
            cout << aux.front() + 1 << " ";
            aux.pop_front();
        }

        cout << "\n";
    }

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
