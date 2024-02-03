/***********************************************************************
  UFA - ESPE
 * Module:  Cliente.h
 * Author:  Edison Verdesoto, Joan Cobeña
 * Modified: viernes, 2 de febrero de 2024 19:31:11
 * Purpose: Declaration of the class Cliente
 ***********************************************************************/

#if !defined(__Class_Diagram_1_Cliente_h)
#define __Class_Diagram_1_Cliente_h

class Cuenta;

#include "Persona.h"

class Cliente
{
public:
   void apertura_cuenta(void);
   std::string generar_ID_cliente(void);
   std::string es_moroso(void);

   Cuenta** cuenta;

protected:
private:
   Persona* persona;
   std::string ID_cliente;


};

#endif
