
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "bintree.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// Estructura para almacenar el resultado de la comprobación
template <typename T>
struct AVLResult {
    bool esAVL;
    int altura;
    T minVal;
    T maxVal;
};

// Función auxiliar para comprobar si el árbol cumple AVL
template <typename T>
AVLResult<T> esAVLRec(const BinTree<T>& tree) {
    if (tree.empty()) {
        // Un árbol vacío es AVL y tiene altura 0, y no restringe valores
        return {true, 0, T(), T()};
    }

    // Comprobar recursivamente los subárboles izquierdo y derecho
    AVLResult<T> izq = esAVLRec(tree.left());
    AVLResult<T> der = esAVLRec(tree.right());

    // El árbol actual es AVL si:
    // 1. Los subárboles izquierdo y derecho son AVL
    // 2. La diferencia de alturas es como mucho 1
    // 3. El mayor valor del subárbol izquierdo es menor que el nodo actual
    // 4. El menor valor del subárbol derecho es mayor que el nodo actual
    bool esAVL = izq.esAVL && der.esAVL && abs(izq.altura - der.altura) <= 1;

    if (!tree.left().empty() && izq.maxVal >= tree.root()) {
        esAVL = false;
    }
    if (!tree.right().empty() && der.minVal <= tree.root()) {
        esAVL = false;
    }

    // La altura del árbol es 1 + la altura máxima de los subárboles
    int altura = 1 + max(izq.altura, der.altura);

    // Determinar el rango de valores (mínimo y máximo)
    T minVal = tree.left().empty() ? tree.root() : izq.minVal;
    T maxVal = tree.right().empty() ? tree.root() : der.maxVal;

    return {esAVL, altura, minVal, maxVal};
}

// Función para leer un árbol desde la entrada estándar
template <typename T>
BinTree<T> leerArbol(istream& in) {
    char c;
    in >> c;

    if (c == '.') {
        return {}; // Subárbol vacío
    }

    if (c == '(') {
        BinTree<T> izq = leerArbol<T>(in); // Leer subárbol izquierdo
        T elemento;
        in >> elemento; // Leer el nodo actual
        BinTree<T> der = leerArbol<T>(in); // Leer subárbol derecho
        in >> c; // Leer el paréntesis de cierre
        return BinTree<T>(izq, elemento, der);
    }

    return {}; // Caso por defecto
}

bool resuelveCaso() {
    // Leer el carácter de tipo de caso
    char tipo;
    cin >> tipo;
    if (!cin) return false;

    if (tipo == 'N') {
        // Leer y comprobar un árbol de enteros
        BinTree<int> arbol = leerArbol<int>(cin);
        AVLResult<int> resultado = esAVLRec(arbol);

        if (resultado.esAVL) {
            cout << "SI" << endl;
        } else {
            cout << "NO" << endl;
        }

    } else if (tipo == 'P') {
        // Leer y comprobar un árbol de cadenas
        BinTree<string> arbol = leerArbol<string>(cin);
        AVLResult<string> resultado = esAVLRec(arbol);

        if (resultado.esAVL) {
            cout << "SI" << endl;
        } else {
            cout << "NO" << endl;
        }
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
