#include <iostream>
#include <string>
#include "Arbol_Bplus.h"
#include "Nodo.cpp"
#include "ListaDoble.cpp"
#include "NodoB.h"
#include "Cuenta.h"
#include "Cliente.h"

Arbol_Bplus::Arbol_Bplus(int grado_max)
{
    grado = grado_max;
    raiz = new NodoB();
}

Nodo<Cuenta*>* obtener_nodo_central(ListaDoble<Cuenta*>* claves, int grado)
{
    Nodo<Cuenta*>* aux = claves->get_cabeza();
    int i;
    for(i = 0; i<grado/2; i++)
    {
        aux = aux->get_siguiente();
    }
    if(i%2==0)
    {
        aux = aux->get_anterior();
    }
    return aux;
}

void insertar_en_claves(ListaDoble<Cuenta*>* claves, Cuenta* dato, char tipo)
{
    Nodo<Cuenta*>* aux = claves->get_cabeza();
    std::string comparar, comparar_nodo;
    Cuenta* cuenta;

    //id
    if(tipo == 'i')
    {
        comparar = dato->get_cliente()->get_persona()->get_cedula();
    }
    //cedula
    else if(tipo == 'c')
    {
        comparar = dato->get_cliente()->get_id();
    }


    while(aux!=nullptr)
    {
        cuenta = aux->get_valor();

        //id
        if(tipo == 'i')
        {
            comparar_nodo = cuenta->get_cliente()->get_persona()->get_cedula();
        }
        //cedula
        else if(tipo == 'c')
        {
            comparar_nodo = cuenta->get_cliente()->get_id();
        }

        if(!(comparar > comparar_nodo))
        {
            break;
        }

        aux = aux->get_siguiente();
    }

    if(aux == nullptr)
    {
        claves->insertar_cola(dato);
    }
    else if (aux == claves->get_cabeza())
    {
        claves->insertar_cabeza(dato);
    }
    else
    {
        claves->insertar_entre(aux->get_anterior()->get_valor(), dato);
    }
}

Arbol_Bplus* obtener_hijo_a_insertar(NodoB* raiz, Cuenta* dato, char tipo)
{
    ListaDoble<Cuenta*>* claves = raiz->get_claves();
    ListaDoble<Arbol_Bplus*>* hijos = raiz->get_hijos();

    Nodo<Cuenta*>* clave = claves->get_cabeza();
    Nodo<Arbol_Bplus*>* hijo = hijos->get_cabeza();

    std::string comparar, comparar_nodo;
    Cuenta* cuenta;

    //id
    if(tipo == 'i')
    {
        comparar = dato->get_cliente()->get_persona()->get_cedula();
    }
    //cedula
    else if(tipo == 'c')
    {
        comparar = dato->get_cliente()->get_id();
    }

    while(clave!= nullptr)
    {
        cuenta = clave->get_valor();
        //id
        if(tipo == 'i')
        {
            comparar_nodo = cuenta->get_cliente()->get_persona()->get_cedula();
        }
        //cedula
        else if(tipo == 'c')
        {
            comparar_nodo = cuenta->get_cliente()->get_id();
        }

        if (!(comparar > comparar_nodo))
        {
            break;
        }

        clave = clave->get_siguiente();
        hijo = hijo->get_siguiente();
    }

    return hijo->get_valor();
}


void configurar_hijos(Nodo<Cuenta*>* nodo_central, Arbol_Bplus* hijo_izq, Arbol_Bplus* hijo_der)
{
    Nodo<Cuenta*>* cabeza_izq = nodo_central->get_anterior();
    Nodo<Cuenta*>* cola_der = nodo_central->get_siguiente();

    while (cabeza_izq->get_anterior() != nullptr)
    {
        cabeza_izq = cabeza_izq ->get_anterior();
    }
    while (cola_der->get_siguiente() != nullptr)
    {
        cola_der = cola_der->get_siguiente();
    }

    hijo_izq->get_raiz()->get_claves()->set_cabeza(cabeza_izq);
    hijo_izq->get_raiz()->get_claves()->set_cola(nodo_central->get_anterior());
    hijo_der->get_raiz()->get_claves()->set_cabeza(nodo_central->get_siguiente());
    hijo_der->get_raiz()->get_claves()->set_cola(cola_der);

    nodo_central->get_anterior()->set_siguiente(nullptr);
    nodo_central->get_siguiente()->set_anterior(nullptr);
}

void conservar_hijos(ListaDoble<Arbol_Bplus*>* hijos_previos, Arbol_Bplus* hijo_izq, Arbol_Bplus* hijo_der, int grado)
{
    Nodo<Arbol_Bplus*>* hijo_prev1 = hijos_previos->get_cabeza();
    Nodo<Arbol_Bplus*>* hijo_prev2 = hijos_previos->get_cola();
    int i = (grado%2==0)?1:0;
    for(int i; i<=grado/2; i++)
    {
        hijo_izq->get_raiz()->get_hijos()->insertar_cola(hijo_prev1->get_valor());
        hijo_der->get_raiz()->get_hijos()->insertar_cabeza(hijo_prev2->get_valor());
        hijo_prev1 = hijo_prev1->get_siguiente();
        hijo_prev2 = hijo_prev2->get_anterior();
    }

}

void Arbol_Bplus::partir(NodoB* _raiz, NodoB* raiz_anterior, char tipo)
{

    Nodo<Cuenta*>* aux = obtener_nodo_central(_raiz->get_claves(), grado);

    Arbol_Bplus* hijo_izq = new Arbol_Bplus(grado);
    Arbol_Bplus* hijo_der = new Arbol_Bplus(grado);

    configurar_hijos(aux, hijo_izq, hijo_der);

    if(raiz_anterior == nullptr)
    {
        NodoB* nueva_raiz = new NodoB();
        nueva_raiz->get_claves()->insertar_cabeza(aux->get_valor());

        if(!_raiz->get_hijos()->esta_vacia())
        {
            conservar_hijos(_raiz->get_hijos(), hijo_izq, hijo_der, grado);
        }

        nueva_raiz->get_hijos()->insertar_cola(hijo_izq);
        nueva_raiz->get_hijos()->insertar_cola(hijo_der);

        aux->set_anterior(nullptr);
        aux->set_siguiente(nullptr);

        this->raiz = nueva_raiz;
    }
    else
    {

        Arbol_Bplus* hijo_previo = obtener_hijo_a_insertar(raiz_anterior, aux->get_valor(), tipo);

        if(!_raiz->get_hijos()->esta_vacia())
        {
            conservar_hijos(_raiz->get_hijos(), hijo_izq, hijo_der, grado);
        }

        raiz_anterior->get_hijos()->insertar_entre(hijo_previo, hijo_der);
        raiz_anterior->get_hijos()->insertar_entre(hijo_previo, hijo_izq);

        raiz_anterior->get_hijos()->eliminar(hijo_previo);

        insertar_en_claves(raiz_anterior->get_claves(), aux->get_valor(), tipo);

    }

}

void Arbol_Bplus::insertar(Cuenta* dato, char tipo)
{
    insertar_rec(dato, nullptr, tipo);

}

void Arbol_Bplus::insertar_rec(Cuenta* dato, NodoB* raiz_anterior, char tipo)
{

    if(raiz->get_claves()->esta_vacia())
    {
        raiz->get_claves()->insertar_cabeza(dato);
    }
    else
    {
        if(raiz->es_hoja())
        {
            insertar_en_claves(raiz->get_claves(), dato, tipo);
        }
        else
        {
            obtener_hijo_a_insertar(raiz, dato, tipo)->insertar_rec(dato, raiz, tipo);
        }
    }

    if(raiz->get_claves()->tam() == grado)
    {
        partir(raiz, raiz_anterior, tipo);
    }
}




void Arbol_Bplus::eliminar(Cuenta* dato)
{

}


NodoB* Arbol_Bplus::get_raiz()
{
    return raiz;
}

Arbol_Bplus::~Arbol_Bplus()
{

}
