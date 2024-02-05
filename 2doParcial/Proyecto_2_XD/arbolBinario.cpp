#include "arbolBinario.h"
#include "Nodo_Arbol.cpp"
#include <algorithm>
#include <iostream>
#include "Cuenta.h"

template <typename T>
ArbolBinario<T>::ArbolBinario() : raiz(nullptr) {

}

template <typename T>
Nodo_Arbol<T>* ArbolBinario<T>::insertar_arb(Nodo_Arbol<T>* nodo, Cuenta* valor, int opcion) {
    if (nodo == nullptr) {
        return new Nodo_Arbol<T>(valor);
    }

    if (valor->getter_general(opcion) < nodo->dato->getter_general(opcion)) {
        nodo->izquierda = insertar_arb(nodo->izquierda, valor, opcion);
    } else if (valor->getter_general(opcion) > nodo->dato->getter_general(opcion)) {
        nodo->derecha = insertar_arb(nodo->derecha, valor, opcion);
    }else if (valor->getter_general(opcion) == nodo->dato->getter_general(opcion)) {
        nodo->derecha = insertar_arb(nodo->derecha, valor, opcion);
    }

    return nodo;
}

template <typename T>
void ArbolBinario<T>::inorden(Nodo_Arbol<T>* nodo) {
    if (nodo != nullptr) {
        inorden(nodo->izquierda);
        nodo->dato.to_String();
        inorden(nodo->derecha);
    }
}

template <typename T>
void ArbolBinario<T>::preorden(Nodo_Arbol<T>* nodo, int opcion) {
    if (nodo != nullptr) {
        std::cout << nodo->dato.getter_general(opcion) << " ";
        preorden(nodo->izquierda);
        preorden(nodo->derecha);
    }
}

template <typename T>
void ArbolBinario<T>::postorden(Nodo_Arbol<T>* nodo, int opcion) {
    if (nodo != nullptr) {
        postorden(nodo->izquierda);
        postorden(nodo->derecha);
        std::cout << nodo->dato.getter_general(opcion) << " ";
    }
}

template <typename T>
Nodo_Arbol<T>* ArbolBinario<T>::encontrarMinimo(Nodo_Arbol<T>* nodo) {
    while (nodo->izquierda != nullptr) {
        nodo = nodo->izquierda;
    }
    return nodo;
}

template <typename T>
Nodo_Arbol<T>* ArbolBinario<T>::encontrarMaximo(Nodo_Arbol<T>* nodo) {
    while (nodo->derecha != nullptr) {
        nodo = nodo->derecha;
    }
    return nodo;
}

template <typename T>
Nodo_Arbol<T>* ArbolBinario<T>::eliminar(Nodo_Arbol<T>* nodo, T valor, int opcion) {
    if (nodo == nullptr) {
        return nodo;
    }

    if (valor.getter_general(opcion) < nodo->dato.getter_general(opcion)) {
        nodo->izquierda = eliminar(nodo->izquierda, valor);
    } else if (valor.getter_general(opcion) > nodo->dato.getter_general(opcion)) {
        nodo->derecha = eliminar(nodo->derecha, valor);
    } else {
        if (nodo->izquierda == nullptr) {
            Nodo_Arbol<T>* temp = nodo->derecha;
            delete nodo;
            return temp;
        } else if (nodo->derecha == nullptr) {
            Nodo_Arbol<T>* temp = nodo->izquierda;
            delete nodo;
            return temp;
        }

        Nodo_Arbol<T>* temp = encontrarMinimo(nodo->derecha);
        nodo->dato = temp->dato;
        nodo->derecha = eliminar(nodo->derecha, temp->dato);
    }

    return nodo;
}

template <typename T>
void ArbolBinario<T>::insertar(Cuenta* valor, int opcion) {
    raiz = insertar_arb(raiz, valor, opcion);
}

template <typename T>
void ArbolBinario<T>::recorridoInorden() {
    inorden(raiz);
    std::cout << std::endl;
}

template <typename T>
void ArbolBinario<T>::eliminar(T valor) {
    raiz = eliminar(raiz, valor);
}

template <typename T>
int ArbolBinario<T>::altura(Nodo_Arbol<T>* nodo) {
    if (nodo == nullptr)
        return 0;
    return nodo->altura;
}

template <typename T>
int ArbolBinario<T>::balance(Nodo_Arbol<T>* nodo) {
    if (nodo == nullptr)
        return 0;
    return altura(nodo->izquierda) - altura(nodo->derecha);
}

template <typename T>
Nodo_Arbol<T>* ArbolBinario<T>::rotacionDerecha(Nodo_Arbol<T>* y) {
    Nodo_Arbol<T>* x = y->izquierda;
    Nodo_Arbol<T>* T2 = x->derecha;

    // Realizar rotación
    x->derecha = y;
    y->izquierda = T2;

    // Actualizar alturas
    y->altura = std::max(altura(y->izquierda), altura(y->derecha)) + 1;
    x->altura = std::max(altura(x->izquierda), altura(x->derecha)) + 1;

    return x;
}

template <typename T>
Nodo_Arbol<T>* ArbolBinario<T>::rotacionIzquierda(Nodo_Arbol<T>* x) {
    Nodo_Arbol<T>* y = x->derecha;
    Nodo_Arbol<T>* T2 = y->izquierda;

    // Realizar rotación
    y->izquierda = x;
    x->derecha = T2;

    // Actualizar alturas
    x->altura = std::max(altura(x->izquierda), altura(x->derecha)) + 1;
    y->altura = std::max(altura(y->izquierda), altura(y->derecha)) + 1;

    return y;
}

template <typename T>
Nodo_Arbol<T>* ArbolBinario<T>::balancear(Nodo_Arbol<T>* nodo) {
    // Actualizar la altura de este nodo
    nodo->altura = std::max(altura(nodo->izquierda), altura(nodo->derecha)) + 1;

    // Obtener el factor de equilibrio de este nodo
    int factorEquilibrio = balance(nodo);

    // Caso izquierda-izquierda
    if (factorEquilibrio > 1 && balance(nodo->izquierda) >= 0) {
        return rotacionDerecha(nodo);
    }

    // Caso derecha-derecha
    if (factorEquilibrio < -1 && balance(nodo->derecha) <= 0) {
        return rotacionIzquierda(nodo);
    }

    // Caso izquierda-derecha
    if (factorEquilibrio > 1 && balance(nodo->izquierda) < 0) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }

    // Caso derecha-izquierda
    if (factorEquilibrio < -1 && balance(nodo->derecha) > 0) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    // No se requiere equilibrado
    return nodo;
}

template <typename T>
void ArbolBinario<T>::balancearArbol() {
    raiz = balancear(raiz);
}

template <typename T>
void ArbolBinario<T>::imprimirNodo(Nodo_Arbol<T>* nodo, int espacio, int opcion) {
    if (nodo == nullptr) {
        return;
    }

    espacio += 5;

    imprimirNodo(nodo->derecha, espacio, opcion);

    std::cout << std::endl;
    for (int i = 5; i < espacio; i++) {
        std::cout << " ";
    }

    std::cout << nodo->dato.getter_general(opcion) << "\n";

    imprimirNodo(nodo->izquierda, espacio, opcion);
}

template <typename T>
void ArbolBinario<T>::imprimirArbol(Nodo_Arbol<T>* raiz, int espacio) {
    if (raiz == nullptr) {
        return;
    }

    imprimirArbol(raiz->derecha, espacio + 5);

    for (int i = 5; i < espacio; i++) {
        std::cout << " ";
    }

    std::cout << raiz->dato << "\n";

    imprimirArbol(raiz->izquierda, espacio + 5);
}

template <typename T>
void ArbolBinario<T>::imprimirArbol(int opcion) {
    imprimirNodo(raiz, 0, opcion);
}


template <typename T>
T* ArbolBinario<T>::buscar(std::string valor) {
    Nodo_Arbol<T>* current = raiz;
    while (current != nullptr) {
        if (valor == current->dato.getter_general(4)) {
            return &current->dato;
        } else if (valor < current->dato.getter_general(4)) {
            current = current->izquierda;
        } else {
            current = current->derecha;
        }
    }
    return nullptr;
}
