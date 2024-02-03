/***********************************************************************
 UFA - ESPE
 * Module:  Persona.h
 * Author:  Edison Verdesoto, Joan Cobeña
 * Modified: viernes, 2 de febrero de 2024 19:26:16
 * Purpose: Declaration of the class Persona
 ***********************************************************************/

#if !defined(__Class_Diagram_1_Persona_h)
#define __Class_Diagram_1_Persona_h

#include "Fecha.h"

class Persona
{
public:
   std::string get_id(void);
   void set_id(std::string newId);
   std::string get_nombre(void);
   void set_nombre(std::string newNombre);
   std::string get_apellido(void);
   void set_apellido(std::string newApellido);
   std::string get_cedula(void);
   void set_cedula(std::string newCedula);
   Fecha get_fecha(void);
   void set_fecha(Fecha newFecha);

protected:
private:
   std::string id;
   std::string nombre;
   std::string apellido;
   std::string cedula;
   Fecha Fecha;


};

#endif
