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
    Persona(std::string,std::string,std::string);
    std::string get_nombre(void);
    void set_nombre(std::string newNombre);
    std::string get_apellido(void);
    void set_apellido(std::string newApellido);
    std::string get_cedula(void);
    void set_cedula(std::string newCedula);


protected:
private:
    std::string nombre;
    std::string apellido;
    std::string cedula;


};

#endif
