#include <iostream>
#include <queue>
#include <utility>

using namespace std;

struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(int valor) {
        this->valor = valor;
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

bool esCompleto(Nodo* raiz) {
    if (raiz == nullptr) {
        return true;
    }

    queue<Nodo*> cola;
    cola.push(raiz);

    bool espacioVacio = false;

    while (!cola.empty()) {
        Nodo* actual = cola.front();
        cola.pop();

        if (actual == nullptr) {
            espacioVacio = true;
        } else {
            // No puede aparecer un nodo despues de un espacio vacio
            if (espacioVacio) {
                return false;
            }

            cola.push(actual->izquierdo);
            cola.push(actual->derecho);
        }
    }

    return true;
}

int anchoMaximo(Nodo* raiz) {
    if (raiz == nullptr) {
        return 0;
    }

    queue<Nodo*> cola;
    cola.push(raiz);

    int maximo = 0;

    while (!cola.empty()) {
        int nodosNivel = static_cast<int>(cola.size());

        if (nodosNivel > maximo) {
            maximo = nodosNivel;
        }

        for (int i = 0; i < nodosNivel; i++) {
            Nodo* actual = cola.front();
            cola.pop();

            if (actual->izquierdo != nullptr) {
                cola.push(actual->izquierdo);
            }

            if (actual->derecho != nullptr) {
                cola.push(actual->derecho);
            }
        }
    }

    return maximo;
}

int profundidadMinima(Nodo* raiz) {
    if (raiz == nullptr) {
        return 0;
    }

    queue<pair<Nodo*, int>> cola;
    cola.push({raiz, 1});


    while (!cola.empty()) {
        Nodo* actual = cola.front().first;
        int profundidad = cola.front().second;

        cola.pop();


        // La primera hoja encontrada tiene menor profundidad
        if (actual->izquierdo == nullptr &&
            actual->derecho == nullptr) {
            return profundidad;
        }

        if (actual->izquierdo != nullptr) {
            cola.push({actual->izquierdo, profundidad + 1});
        }

        if (actual->derecho != nullptr) {
            cola.push({actual->derecho, profundidad + 1});
        }
    }

    return 0;

}

void eliminarArbol(Nodo* raiz) {
    if (raiz == nullptr) {
        return;
    }
    queue<Nodo*> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        Nodo* actual = cola.front();
        cola.pop();

        if (actual->izquierdo != nullptr) {
            cola.push(actual->izquierdo);
        }

        if (actual->derecho != nullptr) {
            cola.push(actual->derecho);
        }

        delete actual;
    }
}

int main() {
    Nodo* arbol = new Nodo(1);

    arbol->izquierdo = new Nodo(2);
    arbol->derecho = new Nodo(3);

    arbol->izquierdo->izquierdo = new Nodo(4);
    arbol->izquierdo->derecho = new Nodo(5);
    arbol->derecho->izquierdo = new Nodo(6);

    cout << "Arbol completo: " << (esCompleto(arbol) ? "Si" : "No") << '\n';
    cout  << "Ancho maximo: "<< anchoMaximo(arbol) << '\n';
    cout << "Profundidad minima: " << profundidadMinima(arbol) << '\n';

    eliminarArbol(arbol);
    return 0;
}