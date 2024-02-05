/***********************************************************************
 UFA - ESPE
 * Module:  TablaAmortizacion.cpp
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: miercoles, 6 de diciembre de 2023
 * Purpose: Declaracion de clase TablaAmortizacion
 ***********************************************************************/
#include "TablaHash.h"
#include <iostream>
#include "ListaDoble.h"
#include "Persona.h"
#include "Cuenta.h"
#include "Nodo.h"

/**
 * @brief Constructor de la clase TablaHash.
 * @param t Tamaño de la tabla hash.
 */
template <typename T>
TablaHash<T>::TablaHash(int t)
{
    tam = t;
    listas_indices = new ListaDoble<T>*[tam];
    for(int i = 0; i<tam;i++){
        listas_indices[i] = new ListaDoble<T>;
    }
}

/**
 * @brief Inserta datos en la tabla hash usando un valor de hash precalculado.
 * @param dato Datos a insertar.
 * @param hashear_cadena Valor de hash precalculado como cadena.
 */
template <typename T>
void TablaHash<T>::insertar(T dato, std::string hashear_cadena){
    int hashear = 0;
    for (char ch : hashear_cadena) {
        hashear += int(ch);
    }
    int pos_hash = hashear % tam;
    listas_indices[pos_hash]->insertar_cola(dato);
}

/**
 * @brief Inserta datos en la tabla hash usando un valor de hash precalculado.
 * @param dato Datos a insertar.
 * @param hashear Valor de hash precalculado como entero.
 */
template <typename T>
void TablaHash<T>::insertar(T dato, int hashear){
    int pos_hash = hashear % tam;
    listas_indices[pos_hash]->insertar_cola(dato);
}

/**
 * @brief Busca un dato en la tabla hash utilizando un valor de hash precalculado.
 * @param dato Datos a buscar.
 * @param hashear Valor de hash precalculado como entero.
 */
template <typename T>
void TablaHash<T>::buscar(T dato, int hashear){
    int pos_hash = hashear % tam;
    printf("Lista %d de la tabla hash ", pos_hash);
    listas_indices[pos_hash]->buscar(dato);
}

/**
 * @brief Busca un valor de hash en la tabla hash.
 * @param hashear Valor de hash precalculado como entero.
 * @return True si se encuentra, False si no se encuentra.
 */
template <typename T>
bool TablaHash<T>::buscar(int hashear){
    int pos_hash = hashear % tam;

    Nodo<Cuenta*>* cuenta_nodo = listas_indices[pos_hash]->get_cabeza();

    while(cuenta_nodo!=nullptr){
        if (cuenta_nodo->get_valor()->get_num_cuenta() == hashear){
            return true;
        }
        cuenta_nodo = cuenta_nodo->get_siguiente();
    }

    return false;
}

/**
 * @brief Busca una persona en la tabla hash utilizando su cédula como valor de hash.
 * @param hashear_cadena Cédula de la persona como cadena.
 * @return Nodo que contiene la persona si se encuentra, nullptr si no se encuentra.
 */
template <typename T>
Nodo<T>* TablaHash<T>::buscar_cedula_persona(std::string hashear_cadena){
    int hashear = 0;
    for (char ch : hashear_cadena) {
        hashear += int(ch);
    }
    int pos_hash = hashear % tam;

    Nodo<T>* persona_nodo = listas_indices[pos_hash]->get_cabeza();

    std::string cedula_nodo;

    while(persona_nodo!=nullptr){

        cedula_nodo = persona_nodo->get_valor()->get_cedula();

        if (cedula_nodo == hashear_cadena){
            return persona_nodo;
        }
        persona_nodo = persona_nodo->get_siguiente();
    }

    return persona_nodo;
}

/**
 * @brief Busca una cuenta en la tabla hash utilizando la cédula del cliente como valor de hash.
 * @param hashear_cadena Cédula del cliente como cadena.
 * @return Nodo que contiene la cuenta si se encuentra, nullptr si no se encuentra.
 */
template <typename T>
Nodo<T>* TablaHash<T>::buscar_cedula_cuenta(std::string hashear_cadena){
    int hashear = 0;
    for (char ch : hashear_cadena) {
        hashear += int(ch);
    }
    int pos_hash = hashear % tam;

    Nodo<T>* cuenta_nodo = listas_indices[pos_hash]->get_cabeza();

    std::string cedula_nodo;

    while(cuenta_nodo!=nullptr){

        cedula_nodo = cuenta_nodo->get_valor()->get_cliente()->get_persona()->get_cedula();

        if (cedula_nodo == hashear_cadena){
            return cuenta_nodo;
        }
        cuenta_nodo = cuenta_nodo->get_siguiente();
    }

    return cuenta_nodo;
}

/**
 * @brief Busca un dato en la tabla hash utilizando un valor de hash precalculado y un tipo específico.
 * @param hashear_cadena Valor de hash precalculado como cadena.
 * @param tipo Tipo de dato a buscar ("cuenta" en este caso).
 * @return Nodo que contiene el dato si se encuentra, nullptr si no se encuentra o el tipo no coincide.
 */
template <typename T>
Nodo<T>* TablaHash<T>::buscar(int hashear_cadena ,std::string tipo){
    int hashear = 0;
    for (char ch : hashear_cadena) {
        hashear += int(ch);
    }
    int pos_hash = hashear % tam;

    if(tipo == "cuenta"){
        Nodo<Cuenta*>* cuenta_nodo = listas_indices[pos_hash]->get_cabeza();

        int num_cuenta_del_nodo;

        while(cuenta_nodo!=nullptr){

            num_cuenta_del_nodo = cuenta_nodo->get_valor()->get_num_cuenta();

            if (num_cuenta_del_nodo == hashear){
                return cuenta_nodo;
            }
            cuenta_nodo = cuenta_nodo->get_siguiente();
        }

        return cuenta_nodo;
    }
}

/**
 * @brief Elimina un dato de la tabla hash.
 * @param dato Dato a eliminar.
 */
template <typename T>
void TablaHash<T>::eliminar(T dato){
    int pos_hash = dato % tam;
    listas_indices[pos_hash]->eliminar(dato);
}

/**
 * @brief Imprime la tabla hash.
 */
template <typename T>
void TablaHash<T>::imprimir(){
    for(int i = 0; i<tam; i++){
        printf("%d\t", i);
        listas_indices[i]->imprimir();
        printf("\n");
    }
}

/**
 * @brief Destructor de la clase TablaHash.
 */
template <typename T>
TablaHash<T>::~TablaHash()
{

}
