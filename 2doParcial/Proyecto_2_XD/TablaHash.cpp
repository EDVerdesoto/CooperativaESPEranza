#include "TablaHash.h"
#include <iostream>
#include "ListaDoble.h"
#include "Persona.h"
#include "Cuenta.h"
#include "Nodo.h"
#include "Credito.h"

template <typename T>
TablaHash<T>::TablaHash(int t)
{
    tam = t;
    listas_indices = new ListaDoble<T>*[tam];
    for(int i = 0; i<tam; i++)
    {
        listas_indices[i] = new ListaDoble<T>;
    }
}

template <typename T>
void TablaHash<T>::insertar(T dato, std::string hashear_cadena)
{
    int hashear = 0;
    for (char ch : hashear_cadena)
    {
        hashear += int(ch);
    }
    int pos_hash = hashear % tam;
    listas_indices[pos_hash]->insertar_cola(dato);
}

template <typename T>
void TablaHash<T>::insertar(T dato, int hashear)
{
    int pos_hash = hashear % tam;
    listas_indices[pos_hash]->insertar_cola(dato);
}

template <typename T>
Nodo<T>* TablaHash<T>::buscar(T dato, int hashear)
{
    int pos_hash = hashear % tam;
    return listas_indices[pos_hash]->buscar(dato);
}

template <typename T>
Nodo<T>* TablaHash<T>::buscar(int hashear)
{
    int pos_hash = hashear % tam;

    Nodo<Cuenta*>* cuenta_nodo = listas_indices[pos_hash]->get_cabeza();

    while(cuenta_nodo!=nullptr)
    {
        if (cuenta_nodo->get_valor()->get_num_cuenta() == hashear)
        {
            return cuenta_nodo;
        }
        cuenta_nodo = cuenta_nodo->get_siguiente();
    }

    return cuenta_nodo;
}

template <typename T>
Nodo<T>* TablaHash<T>::buscar_cedula_persona(std::string hashear_cadena)
{
    int hashear = 0;
    for (char ch : hashear_cadena)
    {
        hashear += int(ch);
    }
    int pos_hash = hashear % tam;

    Nodo<T>* persona_nodo = listas_indices[pos_hash]->get_cabeza();

    std::string cedula_nodo;

    while(persona_nodo!=nullptr)
    {

        cedula_nodo = persona_nodo->get_valor()->get_cedula();

        if (cedula_nodo == hashear_cadena)
        {
            return persona_nodo;
        }
        persona_nodo = persona_nodo->get_siguiente();
    }

    return persona_nodo;
}

template <typename T>
Nodo<T>* TablaHash<T>::buscar_cedula_cuenta(std::string hashear_cadena)
{
    int hashear = 0;
    for (char ch : hashear_cadena)
    {
        hashear += int(ch);
    }
    int pos_hash = hashear % tam;

    Nodo<T>* cuenta_nodo = listas_indices[pos_hash]->get_cabeza();

    std::string cedula_nodo;

    while(cuenta_nodo!=nullptr)
    {

        cedula_nodo = cuenta_nodo->get_valor()->get_cliente()->get_persona()->get_cedula();

        if (cedula_nodo == hashear_cadena)
        {
            return cuenta_nodo;
        }
        cuenta_nodo = cuenta_nodo->get_siguiente();
    }

    return cuenta_nodo;
}

template <typename T>
Nodo<T>* TablaHash<T>::buscar(int hashear_cadena,std::string tipo)
{
    int hashear = 0;
    for (char ch : hashear_cadena)
    {
        hashear += int(ch);
    }
    int pos_hash = hashear % tam;

    if(tipo == "cuenta")
    {
        Nodo<Cuenta*>* cuenta_nodo = listas_indices[pos_hash]->get_cabeza();

        int num_cuenta_del_nodo;

        while(cuenta_nodo!=nullptr)
        {

            num_cuenta_del_nodo = cuenta_nodo->get_valor()->get_num_cuenta();

            if (num_cuenta_del_nodo == hashear)
            {
                return cuenta_nodo;
            }
            cuenta_nodo = cuenta_nodo->get_siguiente();
        }

        return cuenta_nodo;
    }
}
template <typename T>
Nodo<T>* TablaHash<T>::buscar_credito(int num_cuenta){
    int pos_hash = num_cuenta % tam;

    Nodo<Credito*>* cuenta_nodo = listas_indices[pos_hash]->get_cabeza();

    while(cuenta_nodo!=nullptr)
    {
        if (cuenta_nodo->get_valor()->get_cuenta()->get_num_cuenta() == num_cuenta)
        {
            return cuenta_nodo;
        }
        cuenta_nodo = cuenta_nodo->get_siguiente();
    }

    return cuenta_nodo;
}

template <typename T>
void TablaHash<T>::eliminar(T dato)
{
    int pos_hash = dato % tam;
    listas_indices[pos_hash]->eliminar(dato);
}

template <typename T>
void TablaHash<T>::imprimir()
{
    for(int i = 0; i<tam; i++)
    {
        printf("%d\t", i);
        listas_indices[i]->imprimir();
        printf("\n");
    }
}

template <typename T>
TablaHash<T>::~TablaHash()
{

}
