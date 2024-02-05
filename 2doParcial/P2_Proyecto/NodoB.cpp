#include "NodoB.h"
#include "ListaDoble.cpp"

/**
 * @brief Constructor por defecto de la clase NodoB.
 */
NodoB::NodoB(){
    claves = new ListaDoble<Cuenta*>;
    hijos = new ListaDoble<Arbol_Bplus*>;
}

/**
 * @brief Verifica si el nodo es una hoja.
 * @return true si el nodo es una hoja, false en caso contrario.
 */
bool NodoB::es_hoja(){
    return hijos->esta_vacia();
}

/**
 * @brief Obtiene la lista de claves del nodo.
 * @return Puntero a la lista de claves.
 */
ListaDoble<Cuenta*>* NodoB::get_claves(){
    return claves;
}

/**
 * @brief Obtiene la lista de hijos del nodo.
 * @return Puntero a la lista de hijos.
 */
ListaDoble<Arbol_Bplus*>* NodoB::get_hijos(){
    return hijos;
}

/**
 * @brief Destructor de la clase NodoB.
 */
NodoB::~NodoB(){

}
