
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

#include "Matriz.h"
#include "EnterosInf.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

EntInf devolver_cambio(vector<pair<int,int>> const& M, int C) {
    int n = M.size(), aux;
    EntInf posible;
    Matriz<EntInf> monedas(n+1, C+1, Infinito);
    monedas[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        monedas[i][0] = 0;
        for (int j = 1; j <= C; ++j){
            monedas[i][j] = monedas[i - 1][j];
            for(int k = 1; k <= M[i-1].second; ++k){
                aux = k * M[i-1].first;
                if (aux > j) break;
                else if (monedas[i - 1][j - aux] != Infinito) {
                    posible = monedas[i - 1][j - aux] + k;
                    if (posible < monedas[i][j]) {
                        monedas[i][j] = posible;
                    }
                }
            }

        }

    }
    return monedas[n][C];
}

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int n;
    cin >> n;
   
    if (!std::cin)  // fin de la entrada
        return false;

    vector<pair<int, int>> monedas(n);
    int precio;

    for(int i = 0; i < n; ++i){
        cin >> monedas[i].first; 
    }
   
    for(int i = 0; i < n; ++i){
        cin >> monedas[i].second; 
    }
    cin >> precio;
   // resolver el caso posiblemente llamando a otras funciones
    
    EntInf sol = devolver_cambio(monedas, precio);

   
   // escribir la solución

    if(sol != Infinito){
        cout << "SI " << sol << "\n";
    }
    else{
        cout << "NO\n";
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
