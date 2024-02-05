/***********************************************************************
 UFA - ESPE
 * Module:  Nodo.cpp
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: jueves, 7 de diciembre de 2023 01:11:27 p. m.
 * Purpose: Implementation of the class Nodo
 ***********************************************************************/

#include "Nodo.h"

/**
 * @brief Constructor de la clase Nodo con anterior y siguiente especificados.
 * @param _valor Valor almacenado en el nodo.
 * @param _siguiente Puntero al siguiente nodo.
 * @param _anterior Puntero al nodo anterior.
 */
template <typename T>
Nodo<T>::Nodo(T _valor, Nodo<T>* _siguiente, Nodo<T>* _anterior)
{
    valor = _valor;
    siguiente = _siguiente;
    anterior = _anterior;
}

/**
 * @brief Constructor de la clase Nodo con solo siguiente especificado.
 * @param _valor Valor almacenado en el nodo.
 * @param _siguiente Puntero al siguiente nodo.
 */
template <typename T>
Nodo<T>::Nodo(T _valor, Nodo<T>* _siguiente)
{
    valor = _valor;
    siguiente = _siguiente;
}

/**
 * @brief Constructor por defecto de la clase Nodo.
 */
template <typename T>
Nodo<T>::Nodo()
{
}

/**
 * @brief Destructor de la clase Nodo.
 */
template <typename T>
Nodo<T>::~Nodo()
{
   // TODO : implement
}

/**
 * @brief Obtiene el valor almacenado en el nodo.
 * @return Valor almacenado en el nodo.
 */
template <typename T>
T Nodo<T>::get_valor()
{
   return valor;
}

/**
 * @brief Establece un nuevo valor para el nodo.
 * @param new_valor Nuevo valor a ser asignado al nodo.
 */
template <typename T>
void Nodo<T>::set_valor(T new_valor)
{
   valor = new_valor;
}

/**
 * @brief Obtiene el puntero al siguiente nodo.
 * @return Puntero al siguiente nodo.
 */
template <typename T>
Nodo<T>* Nodo<T>::get_siguiente()
{
   return siguiente;
}

/**
 * @brief Establece un nuevo puntero al siguiente nodo.
 * @param new_siguiente Nuevo puntero al siguiente nodo.
 */
template <typename T>
void Nodo<T>::set_siguiente(Nodo<T>* new_siguiente)
{
   siguiente = new_siguiente;
}

/**
 * @brief Obtiene el puntero al nodo anterior.
 * @return Puntero al nodo anterior.
 */
template <typename T>
Nodo<T>* Nodo<T>::get_anterior()
{
   return anterior;
}

/**
 * @brief Establece un nuevo puntero al nodo anterior.
 * @param new_anterior Nuevo puntero al nodo anterior.
 */
template <typename T>
void Nodo<T>::set_anterior(Nodo<T>* new_anterior)
{
   anterior = new_anterior;
}
