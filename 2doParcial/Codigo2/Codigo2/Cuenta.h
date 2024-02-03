/***********************************************************************
  UFA - ESPE
 * Module:  Cuenta.h
 * Author:  Edison Verdesoto, Joan Cobe�a
 * Modified: viernes, 2 de febrero de 2024 19:24:07
 * Purpose: Declaration of the class Cuenta
 ***********************************************************************/

#if !defined(__Class_Diagram_1_Cuenta_h)
#define __Class_Diagram_1_Cuenta_h

class Movimientos;

#include <iostream>
#include "Cliente.h"

class Cuenta
{
public:
    Cuenta(Persona*);
    void generar_ID_cuenta();
    Movimientos** movimientos;

protected:
private:
   int num_cuenta;
   Persona* persona;


};

#endif
