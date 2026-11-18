#include <iostream>
#include <stack>
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

bool buscarCamino(Nodo* raiz, int k, stack<int>& resultado) {
    if (raiz == nullptr) {
        return false;
    }

    stack<pair<Nodo*, bool>> nodos;
    stack<int> camino;

    int suma = 0;
    nodos.push({raiz, false});

    while (!nodos.empty()) {
        Nodo* actual = nodos.top().first;
        bool visitado = nodos.top().second;
        nodos.pop();

        if (!visitado) {
            camino.push(actual->valor);
            suma += actual->valor;

            bool esHoja = actual->izquierdo == nullptr && actual->derecho == nullptr;

            if (esHoja && suma == k) {
                resultado = camino;
                return true;
            }

            // Guardamos el nodo para regresar despues
            nodos.push({actual, true});

            if (actual->derecho != nullptr) {
                nodos.push({actual->derecho, false});
            }


            if (actual->izquierdo != nullptr) {
                nodos.push({actual->izquierdo, false});
            }
        } else {
            suma -= actual->valor;
            camino.pop();
        }
    }

    return false;
}


void imprimirCamino(stack<int> camino) {
    stack<int> auxiliar;

    while (!camino.empty()) {
        auxiliar.push(camino.top());
        camino.pop();
    }

    while (!auxiliar.empty()) {
        cout << auxiliar.top();
        auxiliar.pop();

        if (!auxiliar.empty()) {
            cout << " -> ";
        }
    }

    cout << '\n';
}

void eliminarArbol(Nodo* raiz) {
    if (raiz == nullptr) {
        return;
    }

    stack<Nodo*> nodos;
    nodos.push(raiz);

    while (!nodos.empty()) {
        Nodo* actual = nodos.top();
        nodos.pop();

        if (actual->izquierdo != nullptr) {
            nodos.push(actual->izquierdo);
        }

        if (actual->derecho != nullptr) {
            nodos.push(actual->derecho);
        }

        delete actual;
    }
}

int main() {
    Nodo* arbol = new Nodo(5);

    arbol->izquierdo = new Nodo(4);
    arbol->derecho = new Nodo(8);

    arbol->izquierdo->izquierdo = new Nodo(11);
    arbol->izquierdo->izquierdo->izquierdo = new Nodo(7);
    arbol->izquierdo->izquierdo->derecho = new Nodo(2);

    arbol->derecho->izquierdo = new Nodo(13);
    arbol->derecho->derecho = new Nodo(4);
    arbol->derecho->derecho->derecho = new Nodo(1);

    int k = 22;
    stack<int> camino;

    cout << "Buscando camino con suma " << k << '\n';

    if (buscarCamino(arbol, k, camino)) {
        cout << "Camino encontrado: ";
        imprimirCamino(camino);
    } else {
        cout << "No existe un camino con esa suma\n";
    }

    eliminarArbol(arbol);


    return 0;
}