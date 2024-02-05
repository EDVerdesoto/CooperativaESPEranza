#pragma once

template <typename T>
class Nodo_Arbol {
public:
    T dato;
    int altura;                     // Altura del subárbol enraizado en este nodo
    Nodo_Arbol<T>* izquierda;
    Nodo_Arbol<T>* derecha;
    Nodo_Arbol(T valor);
};

