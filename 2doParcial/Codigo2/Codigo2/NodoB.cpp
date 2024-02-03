#include "NodoB.h"
#include "ListaDoble.cpp"

NodoB::NodoB(){
    claves = new ListaDoble<int>;
    hijos = new ListaDoble<Arbol_Bplus*>;
}

bool NodoB::es_hoja(){
    return hijos->esta_vacia();
}

ListaDoble<int>* NodoB::get_claves(){
    return claves;
}

ListaDoble<Arbol_Bplus*>* NodoB::get_hijos(){
    return hijos;
}

NodoB::~NodoB(){

}
