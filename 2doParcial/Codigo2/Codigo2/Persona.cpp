/***********************************************************************
  UFA - ESPE
  * Module:  Persona.cpp
 * Author:  Edison Verdesoto, Joan Cobeña
 * Modified: viernes, 2 de febrero de 2024 19:26:16
 * Purpose: Implementation of the class Persona
 ***********************************************************************/

#include "Persona.h"

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getId()
// Purpose:    Implementation of Persona::getId()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::get_id(void)
{
   return id;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setId(std::string newId)
// Purpose:    Implementation of Persona::setId()
// Parameters:
// - newId
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::set_id(std::string newId)
{
   id = newId;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getNombre()
// Purpose:    Implementation of Persona::getNombre()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::get_nombre(void)
{
   return nombre;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setNombre(std::string newNombre)
// Purpose:    Implementation of Persona::setNombre()
// Parameters:
// - newNombre
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::set_nombre(std::string newNombre)
{
   nombre = newNombre;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getApellido()
// Purpose:    Implementation of Persona::getApellido()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::get_apellido(void)
{
   return apellido;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setApellido(std::string newApellido)
// Purpose:    Implementation of Persona::setApellido()
// Parameters:
// - newApellido
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::set_apellido(std::string newApellido)
{
   apellido = newApellido;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getCedula()
// Purpose:    Implementation of Persona::getCedula()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::get_cedula(void)
{
   return cedula;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setCedula(std::string newCedula)
// Purpose:    Implementation of Persona::setCedula()
// Parameters:
// - newCedula
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::set_cedula(std::string newCedula)
{
   cedula = newCedula;
}
