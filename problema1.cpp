#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct Nodo {
    int clave;
    Nodo* izq;
    Nodo* der;
    explicit Nodo(int k) : clave(k), izq(nullptr), der(nullptr) {}
};
class BST {
private:
    Nodo* raiz;
public:
    BST() : raiz(nullptr) {}

    ~BST() {
        stack<Nodo*> pila;
        if (raiz) pila.push(raiz);
        while (!pila.empty()) {
            Nodo* n = pila.top();
            pila.pop();
            if (n->izq) pila.push(n->izq);
            if (n->der) pila.push(n->der);
            delete n;
        }
    }
    bool insertar(int k) {
        if (!raiz) {
            raiz = new Nodo(k);
            return true;
        }
        Nodo* act = raiz;
        Nodo* padre = nullptr;
        while (act) {
            padre = act;
            if (k < act->clave)      act = act->izq;
            else if (k > act->clave) act = act->der;
            else return false;
        }
        if (k < padre->clave) padre->izq = new Nodo(k);
        else                  padre->der = new Nodo(k);
        return true;
    }
    bool eliminar(int k) {
        Nodo* padre = nullptr;
        Nodo* act = raiz;
        while (act && act->clave != k) {
            padre = act;
            act = (k < act->clave) ? act->izq : act->der;
        }
        if (!act) return false;

        if (act->izq && act->der) {
            Nodo* padreSuc = act;
            Nodo* suc = act->der;
            while (suc->izq) {
                padreSuc = suc;
                suc = suc->izq;
            }
            act->clave = suc->clave; // copiar la clave del sucesor
            padre = padreSuc;        // ahora se elimina el sucesor
            act = suc;
        }
        Nodo* hijo = act->izq ? act->izq : act->der;
        if (!padre)                 raiz = hijo;
        else if (padre->izq == act) padre->izq = hijo;
        else                        padre->der = hijo;
        delete act;
        return true;
    }
    vector<int> inorden() const {
        vector<int> res;
        stack<Nodo*> pila;
        Nodo* act = raiz;
        while (act || !pila.empty()) {
            while (act) {
                pila.push(act);
                act = act->izq;
            }
            act = pila.top();
            pila.pop();
            res.push_back(act->clave);
            act = act->der;
        }
        return res;
    }
    int altura() const {
        if (!raiz) return 0;
        int maxProf = 0;
        stack<pair<Nodo*, int>> pila;
        pila.push({raiz, 1});
        while (!pila.empty()) {
            auto [n, prof] = pila.top();
            pila.pop();
            if (prof > maxProf) maxProf = prof;
            if (n->izq) pila.push({n->izq, prof + 1});
            if (n->der) pila.push({n->der, prof + 1});
        }
        return maxProf;
    }
};
static void imprimir(const string& titulo, const vector<int>& v) {
    cout << titulo;
    for (int x : v) cout << x << " ";
    cout << "\n";
}
int main() {
    BST a;
    int datos[20] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35,
                     45, 55, 65, 75, 85, 5, 15, 22, 68, 90};
    for (int x : datos) a.insertar(x);
    imprimir("In-order inicial:      ", a.inorden());
    a.eliminar(20);
    a.eliminar(5);
    imprimir("In-order tras eliminar:", a.inorden());
    cout << "Altura (mezclado): " << a.altura() << "\n\n";

    BST b;
    for (int i = 1; i <= 20; i++) b.insertar(i);
    b.eliminar(7);
    b.eliminar(13);
    imprimir("In-order (ordenado):   ", b.inorden());
    cout << "Altura (ordenado): " << b.altura() << "\n";
    return 0;
}