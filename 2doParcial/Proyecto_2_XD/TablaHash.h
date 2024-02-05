#ifndef TABLAHASH_H
#define TABLAHASH_H

#include <string>
#include "ListaDoble.h"

template <typename T>

class TablaHash
{
public:
    TablaHash(int);
    void insertar(T, int);
    void insertar(T dato, std::string hashear_cadena);
    Nodo<T>* buscar(T, int);
    Nodo<T>* buscar_cedula_persona(std::string hashear_cadena);
    Nodo<T>* buscar_cedula_cuenta(std::string hashear_cadena);
    Nodo<T>* buscar_credito(int);
    Nodo<T>* buscar(int hashear, std::string tipo);
    Nodo<T>* buscar(int);
    void eliminar(T);
    void imprimir();
    ~TablaHash();

protected:

private:
    int tam;
    ListaDoble<T>** listas_indices;
};

#endif // TABLAHASH_H
