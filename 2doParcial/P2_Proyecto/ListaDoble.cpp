/***********************************************************************
 UFA - ESPE
 * Module:  ListaDoble.cpp
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: jueves, 7 de diciembre de 2023 01:11:27 p. m.
 * Purpose: Implementacion de clase ListaDoble
 ***********************************************************************/
#include <iostream>
#include "ListaDoble.h"

template <typename T>
ListaDoble<T>::ListaDoble(Nodo<T>* _cabeza){
    cabeza = _cabeza;
}

template <typename T>
ListaDoble<T>::ListaDoble(){
    cabeza = nullptr;
}

/**
 * @brief Obtiene la cabeza de la lista doblemente enlazada.
 * @return Puntero al nodo cabeza de la lista.
 */
template <typename T>
Nodo<T>* ListaDoble<T>::get_cabeza(){
    return cabeza;
}

/**
 * @brief Establece un nuevo nodo cabeza para la lista doblemente enlazada.
 * @param nueva_cabeza Puntero al nuevo nodo cabeza.
 * @return void
 */
template <typename T>
void ListaDoble<T>::set_cabeza(Nodo<T>* nueva_cabeza){
    cabeza = nueva_cabeza;
}

/**
 * @brief Obtiene la cola de la lista doblemente enlazada.
 * @return Puntero al nodo cola de la lista.
 */
template <typename T>
Nodo<T>* ListaDoble<T>::get_cola(){
    return cola;
}

/**
 * @brief Establece un nuevo nodo cola para la lista doblemente enlazada.
 * @param nueva_cola Puntero al nuevo nodo cola.
 * @return void
 */
template <typename T>
void ListaDoble<T>::set_cola(Nodo<T>* nueva_cola){
    cola = nueva_cola;
}

/**
 * @brief Inserta un nuevo nodo al inicio de la lista con el valor proporcionado.
 * @param valor Valor a ser almacenado en el nuevo nodo.
 * @return void
 */
template <typename T>
void ListaDoble<T>::insertar_cabeza(T valor){
    Nodo<T>* nuevo_nodo;
    if(esta_vacia()){
        nuevo_nodo = new Nodo<T>(valor, nullptr, nullptr);
        cola = nuevo_nodo;
    }
    else{
        nuevo_nodo = new Nodo<T>(valor, cabeza, nullptr);
        cabeza->set_anterior(nuevo_nodo);
    }
    cabeza = nuevo_nodo;
}

/**
 * @brief Inserta un nuevo nodo al final de la lista con el valor proporcionado.
 * @param valor Valor a ser almacenado en el nuevo nodo.
 * @return void
 */
template <typename T>
void ListaDoble<T>::insertar_cola(T valor){
    Nodo<T>* nuevo_nodo;
    if(esta_vacia()){
        nuevo_nodo = new Nodo<T>(valor, nullptr, nullptr);
        cabeza = nuevo_nodo;
    }
    else{
        nuevo_nodo = new Nodo<T>(valor, nullptr, cola);
        cola->set_siguiente(nuevo_nodo);
    }
    cola = nuevo_nodo;
}

/**
 * @brief Imprime en la consola los valores almacenados en los nodos de la lista.
 * @return void
 */
template <typename T>
void ListaDoble<T>::imprimir(){
    Nodo<T>* aux = cabeza;
    while(aux!=nullptr){
        std::cout<<aux->get_valor()<<"\t";
        aux = aux->get_siguiente();
    }
}

/**
 * @brief Elimina el nodo que contiene el valor proporcionado de la lista.
 * @param valor Valor a ser eliminado de la lista.
 * @return void
 */
template <typename T>
void ListaDoble<T>::eliminar(T valor){
    Nodo<T>* aux = cabeza;
    while(aux!=nullptr){
        if(valor == aux->get_valor()){
            if(aux->get_anterior() != nullptr && aux->get_siguiente() != nullptr){
                aux->get_anterior()->set_siguiente(aux->get_siguiente());
            }
            else{
                cabeza = aux->get_siguiente();
            }
            if(aux->get_siguiente() != nullptr && aux->get_anterior()!= nullptr){
                aux->get_siguiente()->set_anterior(aux->get_anterior());
            }
            delete aux;
            break;
        }
        aux = aux->get_siguiente();
    }
    if(aux == nullptr){
        std::cout<<"No se encontro el elemento a eliminar";
    }
}

/**
 * @brief Inserta un nuevo nodo con el valor proporcionado después del nodo que contiene el valor de búsqueda.
 * @param valor_busq Valor del nodo después del cual se insertará el nuevo nodo.
 * @param valor Valor a ser almacenado en el nuevo nodo.
 * @return void
 */
template <typename T>
void ListaDoble<T>::insertar_entre(T valor_busq, T valor){
    Nodo<T>* aux = cabeza;
    bool encontrado = false;
    while(aux!=nullptr){
        if(valor_busq == aux->get_valor()){
            encontrado = true;
            Nodo<T>* nuevo = new Nodo<T>(valor,aux->get_siguiente(), aux);
            if(aux != cola && aux->get_siguiente()!= nullptr){
                aux->get_siguiente()->set_anterior(nuevo);
            }else{
                cola = nuevo;
            }
            aux->set_siguiente(nuevo);
            break;
        }
        aux = aux->get_siguiente();
    }
    if(encontrado==false)printf("\n No se encontro el dato en la lista");
}

/**
 * @brief Busca el nodo que contiene el valor proporcionado en la lista e imprime su posición.
 * @param valor_busq Valor a ser buscado en la lista.
 * @return void
 */
template <typename T>
void ListaDoble<T>::buscar(T valor_busq){
    Nodo<T>* aux = cabeza;
    int pos = 0;
    while(aux!=nullptr){
        if(valor_busq == aux->get_valor()){
            std::cout<<"Dato encontrado: "<<valor_busq<<" Posicion en la lista: "<<pos<<std::endl;;
            break;
        }
        aux = aux->get_siguiente();
        pos++;
    }
    if(aux==nullptr)printf("\n No se encontro el dato en la lista");
}

/**
 * @brief Obtiene el tamaño (cantidad de nodos) de la lista.
 * @return Tamaño de la lista.
 */
template <typename T>
int ListaDoble<T>::tam(){
    int i = 0;
    Nodo<T>* aux = cabeza;
    while(aux!=nullptr){
        aux = aux->get_siguiente();
        i++;
    }
    return i;
}

/**
 * @brief Verifica si la lista está vacía.
 * @return true si la lista está vacía, false si no lo está.
 */
template <typename T>
bool ListaDoble<T>::esta_vacia(){
    return (cabeza == nullptr);
}
