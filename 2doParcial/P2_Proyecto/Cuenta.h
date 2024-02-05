/***********************************************************************
  UFA - ESPE
 * Module:  Cuenta.h
 * Author:  Edison Verdesoto, Joan Cobeña
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
    Cuenta();
    Cuenta(Cliente*, int, double);
    Cuenta(Cliente*);
    int generar_ID_cuenta();
    Movimientos** movimientos;

    int get_num_cuenta();
    double get_saldo();
    Cliente* get_cliente();

    void set_saldo(double);

    void imprimir();

protected:
private:
    int num_cuenta;
    double saldo;
    Cliente* cliente;


};

#endif
