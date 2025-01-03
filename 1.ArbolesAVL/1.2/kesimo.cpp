
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "TreeSet_AVL.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

template<class T, class Comparator = std::less<T>>
class TreeSet_AVL_Extended : public Set<T, Comparator> {
protected:
    struct TreeNode;
    using Link = TreeNode *;

    struct TreeNode : public Set<T, Comparator>::TreeNode {
        int tam_i; // Número de nodos en el hijo izquierdo + 1

        TreeNode(T const &e, Link i = nullptr, Link d = nullptr, int alt = 1)
            : Set<T, Comparator>::TreeNode(e, i, d, alt), tam_i(1) {}
    };

    // Inserción extendida para mantener tam_i
    bool inserta(T const &e, Link &a) {
        bool crece;
        if (a == nullptr) {
            a = new TreeNode(e);
            ++this->nelems;
            crece = true;
        } else if (this->menor(e, a->elem)) {
            crece = inserta(e, reinterpret_cast<Link &>(a->iz));
            if (crece) reequilibraDer(a);
        } else if (this->menor(a->elem, e)) {
            crece = inserta(e, reinterpret_cast<Link &>(a->dr));
            if (crece) reequilibraIzq(a);
        } else {
            crece = false; // El elemento ya está en el árbol, no se inserta
        }

        if (a != nullptr) {
            int izTam = a->iz ? static_cast<TreeNode *>(a->iz)->tam_i : 0;
            int drTam = a->dr ? static_cast<TreeNode *>(a->dr)->tam_i : 0;
            static_cast<TreeNode *>(a)->tam_i = izTam + drTam + 1;
        }

        return crece;
    }

    // Reequilibrado extendido para actualizar tam_i
    void reequilibraIzq(Link &a) {
        if (this->altura(a->dr) - this->altura(a->iz) > 1) {
            if (this->altura(a->dr->iz) > this->altura(a->dr->dr))
                rotaDerIzq(a);
            else rotaIzq(a);
        } else {
            a->altura = std::max(this->altura(a->iz), this->altura(a->dr)) + 1;
        }

        if (a != nullptr) {
            int izTam = a->iz ? static_cast<TreeNode *>(a->iz)->tam_i : 0;
            int drTam = a->dr ? static_cast<TreeNode *>(a->dr)->tam_i : 0;
            static_cast<TreeNode *>(a)->tam_i = izTam + drTam + 1;
        }
    }

    void reequilibraDer(Link &a) {
        if (this->altura(a->iz) - this->altura(a->dr) > 1) {
            if (this->altura(a->iz->dr) > this->altura(a->iz->iz))
                rotaIzqDer(a);
            else rotaDer(a);
        } else {
            a->altura = std::max(this->altura(a->iz), this->altura(a->dr)) + 1;
        }

        if (a != nullptr) {
            int izTam = a->iz ? static_cast<TreeNode *>(a->iz)->tam_i : 0;
            int drTam = a->dr ? static_cast<TreeNode *>(a->dr)->tam_i : 0;
            static_cast<TreeNode *>(a)->tam_i = izTam + drTam + 1;
        }
    }

public:
    T const &kesimo(int k) const {
        if (k < 1 || k > this->size()) {
            throw std::out_of_range("k fuera de rango");
        }

        return kesimoRec(k, reinterpret_cast<Link>(this->raiz));
    }

private:
    T const &kesimoRec(int k, Link a) const {
        if (a == nullptr) {
            throw std::out_of_range("Nodo nulo encontrado");
        }

        int tamIz = a->iz ? static_cast<TreeNode *>(a->iz)->tam_i : 0;

        if (k == tamIz + 1) {
            return a->elem;
        } else if (k <= tamIz) {
            return kesimoRec(k, reinterpret_cast<Link>(a->iz));
        } else {
            return kesimoRec(k - tamIz - 1, reinterpret_cast<Link>(a->dr));
        }
    }
};

bool resuelveCaso() {
    int N;
    cin >> N;

    if (N == 0) // Caso especial: terminar
        return false;

    TreeSet_AVL_Extended<int> conjunto;
    for (int i = 0; i < N; ++i) {
        int valor;
        cin >> valor;
        conjunto.insert(valor);
    }

    int M;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        int k;
        cin >> k;
        try {
            cout << conjunto.kesimo(k) << endl;
        } catch (std::out_of_range &) {
            cout << "??" << endl;
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
