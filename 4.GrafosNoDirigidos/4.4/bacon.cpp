/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "Grafo.h"
using namespace std;

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 La solución utiliza un grafo no dirigido donde los nodos representan actores
 y las aristas representan colaboraciones en películas. Usamos un recorrido
 en anchura (BFS) para calcular las distancias mínimas desde Kevin Bacon
 a los demás actores. El coste de la solución es O(V + E), donde V es
 el número de actores y E el número de colaboraciones.
 
 @ </answer> */

bool resuelveCaso() {
   int p; // número de películas
   cin >> p;

   if (!cin) // fin de la entrada
      return false;

   unordered_map<string, int> actorToIndex;
   unordered_map<int, string> indexToActor;
   int actorIndex = 0;

   Grafo g(50000); // Creación de un grafo con capacidad suficiente

   // Lectura de las películas y sus actores
   for (int i = 0; i < p; ++i) {
      string pelicula;
      int numActores;
      cin >> pelicula >> numActores;

      vector<int> actoresPelicula;
      for (int j = 0; j < numActores; ++j) {
         string actor;
         cin >> actor;

         if (actorToIndex.find(actor) == actorToIndex.end()) {
            actorToIndex[actor] = actorIndex;
            indexToActor[actorIndex] = actor;
            actorIndex++;
         }

         actoresPelicula.push_back(actorToIndex[actor]);
      }

      for (size_t u = 0; u < actoresPelicula.size(); ++u) {
         for (size_t v = u + 1; v < actoresPelicula.size(); ++v) {
            g.ponArista(actoresPelicula[u], actoresPelicula[v]);
         }
      }
   }

   // Lectura de los actores para calcular sus números de Bacon
   int n; // número de actores a consultar
   cin >> n;

   vector<string> actoresConsulta(n);
   for (int i = 0; i < n; ++i) {
      cin >> actoresConsulta[i];
   }

   // Verificar si Kevin Bacon está en la base de datos
   if (actorToIndex.find("KevinBacon") == actorToIndex.end()) {
      for (const string& actor : actoresConsulta) {
         cout << actor << " INF" << endl;
      }
      cout << "---" << endl;
      return true;
   }

   // Calcular los números de Bacon desde Kevin Bacon
   int kevinBaconIndex = actorToIndex["KevinBacon"];
   vector<bool> visit(actorIndex, false);
   vector<int> dist(actorIndex, -1);

   queue<int> q;
   q.push(kevinBaconIndex);
   visit[kevinBaconIndex] = true;
   dist[kevinBaconIndex] = 0;

   while (!q.empty()) {
      int v = q.front(); q.pop();

      for (int w : g.ady(v)) {
         if (!visit[w]) {
            visit[w] = true;
            dist[w] = dist[v] + 1;
            q.push(w);
         }
      }
   }

   // Responder a las consultas
   for (const string& actor : actoresConsulta) {
      int index = actorToIndex[actor];
      if (dist[index] != -1) {
         cout << actor << " " << dist[index] << endl;
      } else {
         cout << actor << " INF" << endl;
      }
   }

   cout << "---" << endl;
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
