#ifndef ARBOL_BPLUS_H_INCLUDED
#define ARBOL_BPLUS_H_INCLUDED

#include "NodoB.h"
#include "ListaDoble.h"

class Arbol_Bplus {
    public:
        Arbol_Bplus(int);
        void insertar(int dato);
        void insertar_rec(int, NodoB*);
        void eliminar(int);
        void imprimir_rec(int);
        void imprimir_rec(int x, int y, int nclaves, int nhijos,
                               int ancho, int alto, int xprev, int yprev,
                               NodoB* raiz_princ, Nodo<int>* clave, Nodo<Arbol_Bplus*>* hijo, int* tam);
        void imprimir_rec(int, int, int, int, int, int);
        void imprimir();
        NodoB* get_raiz();
        ~Arbol_Bplus();
        void partir(NodoB* raiz, NodoB* raiz_anterior);

    protected:

    private:
        int grado;
        NodoB* raiz;
        ListaDoble<int>* datos_hojas;
};

#endif // ARBOL_B+_H
