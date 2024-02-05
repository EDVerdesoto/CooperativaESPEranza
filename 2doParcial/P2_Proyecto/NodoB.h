#ifndef NODOB_H_INCLUDED
#define NODOB_H_INCLUDED

class Arbol_Bplus;

#include "ListaDoble.h"
#include "Cuenta.h"

class NodoB
{
public:
    NodoB();
    bool es_hoja();
    ListaDoble<Cuenta*>* get_claves();
    ListaDoble<Arbol_Bplus*>* get_hijos();
    ~NodoB();

protected:

private:
    ListaDoble<Cuenta*>* claves;
    ListaDoble<Arbol_Bplus*>* hijos;

};

#endif // NODOB_H
