/***********************************************************************
 UFA - ESPE
 * Module:  Cliente.cpp
 * Author:  Edison Verdesoto, Joan Cobeña
 * Modified: viernes, 2 de febrero de 2024 19:31:11
 * Purpose: Implementation of the class Cliente
 ***********************************************************************/
#include <iostream>
#include <fstream>
#include "Cuenta.h"
#include "Cliente.h"


Cliente::Cliente(Persona* _persona){
    persona = _persona;
    ID_cliente = "000001";
}

Cliente::Cliente(Persona* _persona, std::string _ID_cliente){
    persona = _persona;
    ID_cliente = _ID_cliente;
}

Persona* Cliente::get_persona(){
    return persona;
}

std::string Cliente::get_id(){
    return ID_cliente;
}


////////////////////////////////////////////////////////////////////////
// Name:       Cliente::generar_ID_cliente()
// Purpose:    Implementation of Cliente::generar_ID_cliente()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

void Cliente::generar_ID_cliente(char id[7], int i, bool &guardado) {
    if (guardado) {
        std::sprintf(id, "%06d", i);
        std::cout << id << std::endl;
        guardado = false;
    }
}

std::string Cliente::generar_ID(std::string nombre, int i) {
    char ID[7];
    bool guardado = true;

    generar_ID_cliente(ID, i, guardado);

    return ID;
}

bool Cliente::ID_existe_en_archivo(const std::string &archivo, const std::string &ID) {
    std::ifstream archivo_entrada(archivo);

    if (!archivo_entrada) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return false;
    }

    std::string linea;
    while (std::getline(archivo_entrada, linea)) {
        if (linea == ID) {
            archivo_entrada.close();
            return true; // ID encontrado en el archivo
        }
    }

    archivo_entrada.close();
    return false; // ID no encontrado en el archivo
}

void Cliente::guardar_ID_en_archivo(const std::string &archivo, const std::string &ID) {
    std::ofstream archivo_salida(archivo, std::ios::app);

    if (!archivo_salida) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    archivo_salida << ID << std::endl;
    archivo_salida.close();
}

////////////////////////////////////////////////////////////////////////
// Name:       Cliente::es_moroso()
// Purpose:    Implementation of Cliente::es_moroso()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Cliente::es_moroso(void)
{
   // TODO : implement
}
