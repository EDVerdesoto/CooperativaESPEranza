#include "NodoB.h"
#include "ListaDoble.h"

NodoB::NodoB(){
    claves = new ListaDoble<Cuenta*>;
    hijos = new ListaDoble<Arbol_Bplus*>;
}

bool NodoB::es_hoja(){
    return hijos->esta_vacia();
}

ListaDoble<Cuenta*>* NodoB::get_claves(){
    return claves;
}

ListaDoble<Arbol_Bplus*>* NodoB::get_hijos(){
    return hijos;
}

NodoB::~NodoB(){

}
