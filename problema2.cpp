#include <iostream>
#include <stack>
using namespace std;
 
enum Color { ROJO, NEGRO };
struct NodoRB {
    int clave;
    Color color;
    NodoRB* izq;
    NodoRB* der;
    NodoRB* padre;
};
 
class RedBlackTree {
private:
    NodoRB* NIL;
    NodoRB* raiz;
    void rotarIzq(NodoRB* x) {
        NodoRB* y = x->der;
        x->der = y->izq;
        if (y->izq != NIL) y->izq->padre = x;
        y->padre = x->padre;
        if (x->padre == NIL)            raiz = y;
        else if (x == x->padre->izq)    x->padre->izq = y;
        else                            x->padre->der = y;
        y->izq = x;
        x->padre = y;
    }
    void rotarDer(NodoRB* x) {
        NodoRB* y = x->izq;
        x->izq = y->der;
        if (y->der != NIL) y->der->padre = x;
        y->padre = x->padre;
        if (x->padre == NIL)            raiz = y;
        else if (x == x->padre->der)    x->padre->der = y;
        else                            x->padre->izq = y;
        y->der = x;
        x->padre = y;
    }
    void corregirInsercion(NodoRB* z) {
        while (z->padre->color == ROJO) {
            NodoRB* abuelo = z->padre->padre;
            if (z->padre == abuelo->izq) {
                NodoRB* tio = abuelo->der;
                if (tio->color == ROJO) {
                    z->padre->color = NEGRO;
                    tio->color = NEGRO;
                    abuelo->color = ROJO;
                    z = abuelo;
                } else {
                    if (z == z->padre->der) {
                        z = z->padre;
                        rotarIzq(z);
                    }
                    z->padre->color = NEGRO;
                    z->padre->padre->color = ROJO;
                    rotarDer(z->padre->padre);
                }
            } else {
                NodoRB* tio = abuelo->izq;
                if (tio->color == ROJO) {
                    z->padre->color = NEGRO;
                    tio->color = NEGRO;
                    abuelo->color = ROJO;
                    z = abuelo;
                } else {
                    if (z == z->padre->izq) {
                        z = z->padre;
                        rotarDer(z);
                    }
                    z->padre->color = NEGRO;
                    z->padre->padre->color = ROJO;
                    rotarIzq(z->padre->padre);
                }
            }
        }
        raiz->color = NEGRO;
    }
    int verificarRec(NodoRB* n) const {
        if (n == NIL) return 1;
        if (n->color == ROJO &&
            (n->izq->color == ROJO || n->der->color == ROJO))
            return -1;
        if (n->izq != NIL && n->izq->clave >= n->clave) return -1;
        if (n->der != NIL && n->der->clave <= n->clave) return -1;
        int hi = verificarRec(n->izq);
        int hd = verificarRec(n->der);
        if (hi == -1 || hd == -1 || hi != hd) return -1;
        return hi + (n->color == NEGRO ? 1 : 0);
    }
    int alturaRec(NodoRB* n) const {
        if (n == NIL) return 0;
        return 1 + max(alturaRec(n->izq), alturaRec(n->der));
    }
    void liberar(NodoRB* n) {
        if (n == NIL) return;
        liberar(n->izq);
        liberar(n->der);
        delete n;
    }
public:
    RedBlackTree() {
        NIL = new NodoRB{0, NEGRO, nullptr, nullptr, nullptr};
        NIL->izq = NIL->der = NIL->padre = NIL;
        raiz = NIL;
    }
    ~RedBlackTree() {
        liberar(raiz);
        delete NIL;
    }
    bool insertar(int k) {
        NodoRB* padre = NIL;
        NodoRB* act = raiz;
        while (act != NIL) {
            padre = act;
            if (k < act->clave)      act = act->izq;
            else if (k > act->clave) act = act->der;
            else return false;
        }
        NodoRB* z = new NodoRB{k, ROJO, NIL, NIL, padre};
        if (padre == NIL)            raiz = z;
        else if (k < padre->clave)   padre->izq = z;
        else                         padre->der = z;
        corregirInsercion(z);
        return true;
    }
    bool verificarPropiedades() const {
        if (NIL->color != NEGRO) return false;
        if (raiz != NIL && raiz->color != NEGRO) return false;
        return verificarRec(raiz) != -1;
    }
    int altura() const { return alturaRec(raiz); }
    void preorden() const {
        stack<NodoRB*> pila;
        if (raiz != NIL) pila.push(raiz);
        while (!pila.empty()) {
            NodoRB* n = pila.top();
            pila.pop();
            cout << n->clave << (n->color == ROJO ? "(R) " : "(N) ");
            if (n->der != NIL) pila.push(n->der);
            if (n->izq != NIL) pila.push(n->izq);
        }
        cout << "\n";
    }
};
//     BST simple del Problema 1 solo para comparar alturas
struct NodoBST {
    int clave;
    NodoBST* izq;
    NodoBST* der;
    explicit NodoBST(int k) : clave(k), izq(nullptr), der(nullptr) {}
};
class BST {
private:
    NodoBST* raiz;
public:
    BST() : raiz(nullptr) {}
    ~BST() {
        stack<NodoBST*> pila;
        if (raiz) pila.push(raiz);
        while (!pila.empty()) {
            NodoBST* n = pila.top();
            pila.pop();
            if (n->izq) pila.push(n->izq);
            if (n->der) pila.push(n->der);
            delete n;
        }
    }
    void insertar(int k) {
        if (!raiz) { raiz = new NodoBST(k); return; }
        NodoBST* act = raiz;
        NodoBST* padre = nullptr;
        while (act) {
            padre = act;
            if (k < act->clave)      act = act->izq;
            else if (k > act->clave) act = act->der;
            else return;
        }
        if (k < padre->clave) padre->izq = new NodoBST(k);
        else                  padre->der = new NodoBST(k);
    }
    int altura() const {
        if (!raiz) return 0;
        int maxProf = 0;
        stack<pair<NodoBST*, int>> pila;
        pila.push({raiz, 1});
        while (!pila.empty()) {
            auto [n, prof] = pila.top();
            pila.pop();
            maxProf = max(maxProf, prof);
            if (n->izq) pila.push({n->izq, prof + 1});
            if (n->der) pila.push({n->der, prof + 1});
        }
        return maxProf;
    }
    void preorden() const {
        stack<NodoBST*> pila;
        if (raiz) pila.push(raiz);
        while (!pila.empty()) {
            NodoBST* n = pila.top();
            pila.pop();
            cout << n->clave << " ";
            if (n->der) pila.push(n->der);
            if (n->izq) pila.push(n->izq);
        }
        cout << "\n";
    }
};

int main() {
    const int N = 20;
    BST bst;
    RedBlackTree rbt;
    for (int i = 1; i <= N; i++) {
        bst.insertar(i);
        rbt.insertar(i);
    }
    cout << "Pre-orden BST:        ";
    bst.preorden();
    cout << "Pre-orden Red-Black:  ";
    rbt.preorden();
    cout << "\nAltura BST:        " << bst.altura() << "\n";
    cout << "Altura Red-Black:  " << rbt.altura() << "\n";
    cout << "Propiedades RB validas: "
         << (rbt.verificarPropiedades() ? "si" : "no") << "\n";
    return 0;
}
 