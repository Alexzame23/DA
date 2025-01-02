
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "EnterosInf.h"
#include "Matriz.h"
using namespace std;

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


Matriz<EntInf> construyeMatriz(vector<int> v, int valor, int S) {
   Matriz<EntInf> sol(S + 1, valor + 1, Infinito);

   for(int i = 0; i <= valor; i++) {
      sol[0][i] = Infinito;
   }

   for (int i = 0; i <= S; i++) {
      sol[i][0] = 0;
   }
   
   for(int i = 1; i < S + 1; i++) { // v[i]
      for(int j = 1; j < valor + 1; j++) {
         // cout << "( " << v[i-1] << " > " << j <<  " )";
         if (v[i-1] > j) { // Si cojemos
            // cout << "NC ";
            sol[i][j] = sol[i-1][j];
         } else { // Si no cojemos
            // cout << "SC ";
            sol[i][j] = min( sol[i-1][j] , sol[i][j-v[i-1]] + 1);
         }
      }
      // cout << '\n';
   }

   return sol;
}

vector<int> reconstruirSolucion(Matriz<EntInf> m, vector <int> sectores,  int S, int valor) {
   vector<int> sol;

   int k = 0;
   if (m[S][valor] != Infinito) {
      int i = S;
      int j = valor;
      while( j > 0 ) {
         if (sectores[i-1] <= j && (m[i][j] != m[i-1][j] || (m[i][j - sectores[i-1]]+1) == m[i-1][j])) {
            sol.push_back(sectores[i-1]);
            j = j - sectores[i-1];
         } else {
           
            i--;
         }
      }
   }
   
   return sol;
}

bool resuelveCaso() {
   
   int valor, S;
   cin >> valor >> S;
   
   if (!std::cin)  // fin de la entrada
      return false;

   vector<int> v;

   int s;
   for(int i = 0; i < S; i++) {
      cin >> s;
      v.push_back(s);
   }

   
   //cout << "Objetivo: " << valor << " con los " << S << " sectores\n";
   Matriz<EntInf> m = construyeMatriz(v, valor, S);
   // cout << m << '\n';
   
   if (m[S][valor] != Infinito) {
      cout << m[S][valor];
      vector<int> sol = reconstruirSolucion(m, v, S, valor);
      cout << ": ";
      for(int i = 0; i < sol.size(); i++) {
         cout << sol[i];
         if (i != sol.size() - 1) {cout << ' ';}
      }

   } else {
      cout << "Imposible";
   }

   cout << '\n';

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
