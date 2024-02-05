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

/**
 * @brief Constructor de Cliente que inicializa el objeto con una Persona y un ID cliente predeterminado
 * @param _persona Persona asociada al cliente
 */
Cliente::Cliente(Persona* _persona){
    persona = _persona;
    ID_cliente = "000001";
}

/**
 * @brief Constructor de Cliente que inicializa el objeto con una Persona y un ID cliente proporcionado
 * @param _persona Persona asociada al cliente
 * @param _ID_cliente ID cliente proporcionado
 */
Cliente::Cliente(Persona* _persona, std::string _ID_cliente){
    persona = _persona;
    ID_cliente = _ID_cliente;
}

/**
 * @brief Obtiene la persona asociada al cliente
 * @return Puntero a la Persona asociada
 */
Persona* Cliente::get_persona(){
    return persona;
}

/**
 * @brief Obtiene el ID cliente del cliente
 * @return ID cliente del cliente
 */
std::string Cliente::get_id(){
    return ID_cliente;
}

/**
 * @brief Genera el ID cliente para un nuevo cliente
 * @param id Arreglo de caracteres para almacenar el ID generado
 * @param i Número de clientes existentes
 * @param guardado Variable para indicar si el ID ha sido generado y guardado
 */
void Cliente::generar_ID_cliente(char id[7], int i, bool &guardado) {
    if (guardado) {
        std::sprintf(id, "%06d", i);
        std::cout << id << std::endl;
        guardado = false;
    }
}

/**
 * @brief Genera un nuevo ID cliente para un cliente
 * @param nombre Nombre del cliente
 * @param i Número de clientes existentes
 * @return Nuevo ID cliente generado
 */
std::string Cliente::generar_ID(std::string nombre, int i) {
    char ID[7];
    bool guardado = true;

    generar_ID_cliente(ID, i, guardado);

    return ID;
}

/**
 * @brief Verifica si un ID existe en un archivo proporcionado
 * @param archivo Nombre del archivo donde se busca el ID
 * @param ID ID a buscar
 * @return True si el ID existe en el archivo, False en caso contrario
 */
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

/**
 * @brief Guarda un ID en un archivo proporcionado
 * @param archivo Nombre del archivo donde se guarda el ID
 * @param ID ID a guardar
 */
void Cliente::guardar_ID_en_archivo(const std::string &archivo, const std::string &ID) {
    std::ofstream archivo_salida(archivo, std::ios::app);

    if (!archivo_salida) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    archivo_salida << ID << std::endl;
    archivo_salida.close();
}

/**
 * @brief Verifica si el cliente es moroso (sin implementar)
 * @return Mensaje indicando si el cliente es moroso
 */
std::string Cliente::es_moroso(void)
{
   // TODO : implement
}
