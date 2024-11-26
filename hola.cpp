#include <iostream>
#include <random>  // Para generar números aleatorios
#include <ncurses.h>  // Para graficar el árbol

// Definición de una ternia
template <typename T1, typename T2, typename T3>
struct ternia {
    T1 primero;
    T2 segundo;
    T3 tercero;

    ternia() : primero(T1()), segundo(T2()), tercero(T3()) {}
    ternia(const T1 &v1, const T2 &v2, const T3 &v3) : primero(v1), segundo(v2), tercero(v3) {}
    bool operator<(const ternia &other) const {
        if (primero != other.primero) {
            return primero < other.primero;
        } else if (segundo != other.segundo) {
            return segundo < other.segundo;
        } else {
            return tercero < other.tercero;
        }
    }
};

// Definición de un nodo
template <typename X>
struct nodoA {
    X llave;
    nodoA *izq;
    nodoA *der;

    nodoA(X val) : llave(val), izq(nullptr), der(nullptr) {}
};

// Clase árbol binario
template <typename X>
class arbol {
public:
    nodoA<X> *raiz;

    arbol() : raiz(nullptr) {}

    void inserta(X val) {
        raiz = _inserta(raiz, val);
    }

private:
    nodoA<X> *_inserta(nodoA<X> *nodo, X val) {
        if (!nodo) return new nodoA<X>(val);
        if (val < nodo->llave) {
            nodo->izq = _inserta(nodo->izq, val);
        } else {
            nodo->der = _inserta(nodo->der, val);
        }
        return nodo;
    }
};

// Función para asignar coordenadas a los nodos
template <typename X>
void asignarCoordenadas(nodoA<X> *nodo, int x, int y, int &offset) {
    if (!nodo) return;

    asignarCoordenadas(nodo->izq, x - offset, y + 2, offset);

    nodo->llave.segundo = x;
    nodo->llave.tercero = y;

    asignarCoordenadas(nodo->der, x + offset, y + 2, offset);
}

// Función para graficar el árbol con trazas
template <typename X>
void graficarConTrazas(nodoA<X> *nodo) {
    if (!nodo) return;

    initscr();
    noecho();
    curs_set(0);

    _graficarConTrazas(nodo);

    getch();
    endwin();
}

template <typename X>
void _graficarConTrazas(nodoA<X> *nodo) {
    if (!nodo) return;

    int x = nodo->llave.segundo;
    int y = nodo->llave.tercero;

    mvprintw(y, x, "%d", nodo->llave.primero);

    if (nodo->izq && nodo->der) {
        int xIzq = nodo->izq->llave.segundo;
        int yIzq = nodo->izq->llave.tercero;
        int xDer = nodo->der->llave.segundo;
        int yDer = nodo->der->llave.tercero;

        for (int i = xIzq; i <= xDer; ++i) {
            mvaddch(yIzq - 1, i, '-');
        }

        int xMedio = (xIzq + xDer) / 2;
        mvaddch(y + 1, xMedio, '|');
    }

    if (nodo->izq) {
        int xIzq = nodo->izq->llave.segundo;
        mvaddch(y + 1, xIzq, '|');
        _graficarConTrazas(nodo->izq);
    }

    if (nodo->der) {
        int xDer = nodo->der->llave.segundo;
        mvaddch(y + 1, xDer, '|');
        _graficarConTrazas(nodo->der);
    }
}

// Función principal
int main() {
    int semilla, n;

    initscr();
    cbreak();
    curs_set(1);

    mvprintw(0, 0, "Ingrese la semilla para el generador de numeros aleatorios: ");
    scanw("%d", &semilla);

    mvprintw(1, 0, "Ingrese el numero de valores a insertar en el arbol: ");
    scanw("%d", &n);
    clear();
    endwin();

    std::mt19937 generador(semilla);
    std::uniform_int_distribution<int> distribucion(1, 100);

    arbol<ternia<int, int, int>> miArbol;

    for (int i = 0; i < n; ++i) {
        int valor = distribucion(generador);
        miArbol.inserta(ternia<int, int, int>(valor, 0, 0));
    }

    int offset = 8;
    asignarCoordenadas(miArbol.raiz, 40, 0, offset);

    graficarConTrazas(miArbol.raiz);

    return 0;
}