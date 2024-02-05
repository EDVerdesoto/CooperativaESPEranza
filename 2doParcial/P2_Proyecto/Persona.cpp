/***********************************************************************
  UFA - ESPE
  * Module:  Persona.cpp
 * Author:  Edison Verdesoto, Joan Cobeña
 * Modified: viernes, 2 de febrero de 2024 19:26:16
 * Purpose: Implementation of the class Persona
 ***********************************************************************/

#include "Persona.h"

/**
 * @brief Constructor de la clase Persona.
 * @param _nombre Nombre de la persona.
 * @param _apellido Apellido de la persona.
 * @param _cedula Cédula de la persona.
 */
Persona::Persona(std::string _nombre, std::string _apellido, std::string _cedula){
    nombre = _nombre;
    apellido = _apellido;
    cedula = _cedula;

}

/**
 * @brief Obtiene el nombre de la persona.
 * @return Nombre de la persona.
 */
std::string Persona::get_nombre(void)
{
   return nombre;
}

/**
 * @brief Establece un nuevo nombre para la persona.
 * @param newNombre Nuevo nombre a ser asignado.
 */
void Persona::set_nombre(std::string newNombre)
{
   nombre = newNombre;
}

/**
 * @brief Obtiene el apellido de la persona.
 * @return Apellido de la persona.
 */
std::string Persona::get_apellido(void)
{
   return apellido;
}

/**
 * @brief Establece un nuevo apellido para la persona.
 * @param newApellido Nuevo apellido a ser asignado.
 */
void Persona::set_apellido(std::string newApellido)
{
   apellido = newApellido;
}

/**
 * @brief Obtiene la cédula de la persona.
 * @return Cédula de la persona.
 */
std::string Persona::get_cedula(void)
{
   return cedula;
}

/**
 * @brief Establece una nueva cédula para la persona.
 * @param newCedula Nueva cédula a ser asignada.
 */
void Persona::set_cedula(std::string newCedula)
{
   cedula = newCedula;
}

/**
 * @brief Imprime la información de la persona.
 */
void Persona::imprimir()
{
   std::cout<<"Nombre: "<<nombre<<std::endl;
   std::cout<<"ApellidO: "<<apellido<<std::endl;
   std::cout<<"Cedula: "<<cedula<<std::endl;
}

