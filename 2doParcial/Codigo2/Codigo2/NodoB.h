#ifndef NODOB_H_INCLUDED
#define NODOB_H_INCLUDED

class Arbol_Bplus;

#include "ListaDoble.h"

class NodoB
{
    public:
        NodoB();
        bool es_hoja();
        ListaDoble<int>* get_claves();
        ListaDoble<Arbol_Bplus*>* get_hijos();
        ~NodoB();

    protected:

    private:
        ListaDoble<int>* claves;
        ListaDoble<Arbol_Bplus*>* hijos;

};

#endif // NODOB_H
