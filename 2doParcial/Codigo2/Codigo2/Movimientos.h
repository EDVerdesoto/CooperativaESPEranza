/***********************************************************************
 UFA - ESPE
 * Module:  Movimientos.h
 * Author:  Edison Verdesoto, Joan Cobeña
 * Modified: lunes, 29 de enero de 2024 12:07:16
 * Purpose: Declaration of the class Movimientos
 ***********************************************************************/

#if !defined(__Class_Diagram_1_Movimientos_h)
#define __Class_Diagram_1_Movimientos_h

#include "Cuenta.h"
#include "Cliente.h"

class Movimientos
{
public:
   double deposito(void);
   double retiro(void);
   double saldo(void);

protected:
private:
   int monto;
   Cuenta Cuenta;
   Persona Persona;
   Fecha Fecha;


};

#endif
