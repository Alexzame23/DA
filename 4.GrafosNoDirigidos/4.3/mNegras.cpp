
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
    int f, c;
    int auxi, auxj;
    vector<vector<bool>> visitados; // Marcador de nodos visitados
    const vector<pair<int,int>> aux = {{1,0},{0,1},{-1,0},{0,-1}};
    int tamano;

    void dfs(vector<string> const& g, int i, int j) {
        visitados[i][j] = true;
        tamano++;
        for (int h = 0; h < aux.size(); ++h) {
            auxi = i + aux[h].first;
            auxj = j + aux[h].second;
            if(posCorrecta(auxi, auxj) && g[auxi][auxj] == '#' && !visitados[auxi][auxj])
                dfs(g, auxi, auxj);
            
        }
    }

    bool posCorrecta(int i, int j){
        return (i >= 0 && i < f) && (j >= 0 && j < c);
    }

public:
    CaminosDFS(vector<string> const& g, int& maxTamano, int& nManchas) : f(g.size()), c(g[0].size()), visitados(f, vector<bool>(c, false)), tamano(0) {
        for (int i = 0; i < f; ++i) {
            for(int j = 0; j < c; ++j){
                if (!visitados[i][j] && g[i][j] == '#') {
                    tamano = 0;
                    dfs(g, i, j);
                    maxTamano = max(maxTamano, tamano);
                    nManchas++;
                }
            }
        }
    }
};

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int f, c;
    cin >> f >> c;
   
   if (!std::cin)  // fin de la entrada
      return false;

    vector<string> bitmap(f);

    for(string & l : bitmap)
        cin >> l;
   
   // resolver el caso posiblemente llamando a otras funciones
    int maxTam = 0;
    int nManchas = 0;
    CaminosDFS dfs(bitmap,maxTam,nManchas);
   // escribir la solución
    cout << nManchas << " " << maxTam << "\n";
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
