/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#include "PriorityQueue.h"

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Pelicula {
    int ini;
    int fin; 
    int dur;
};

bool resuelveCaso() {
    
    // leer los datos de la entrada
    int n;
    cin >> n;
    
    if (n  <= 0) 
        return false;

    vector<Pelicula> pelis(n);

    char puntos;
    int auxh, auxm, duracion;

    for (int i = 0; i < n; ++i) {
        cin >> auxh >> puntos >> auxm >> duracion; 

        pelis[i] = { auxh*60+auxm, auxh*60+auxm+duracion , duracion };
    }

    // resolver el caso posiblemente llamando a otras funciones

    sort(pelis.begin(), pelis.end(), [](const Pelicula &a, const Pelicula &b){
        return a.fin < b.fin;
    });

    vector<long long int> duraciones(n, 0);
    long long int sol = 0;

    for (int i = 0; i < n; ++i) {
        duraciones[i] = pelis[i].dur;
        for (int j = 0; j < i; ++j) {
            if (pelis[j].fin + 10 <= pelis[i].ini) {
                duraciones[i] = max(duraciones[i], duraciones[j]+ pelis[i].dur);
            }
        }
        sol = max(sol, duraciones[i]);
    }

    // escribir la solución

    cout << sol << "\n";
    return true;
}

/*@ </answer> */

//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    while (resuelveCaso());
    
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
