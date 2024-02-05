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

class Movimientos
{
public:
    Movimientos(Cuenta*);
    bool deposito(double);
    bool retiro(double);
    bool guardar_movimientos();
    int contar_movimientos();
    bool borrar_ultimo();
    void generar_comprobante();
    Cuenta* get_cuenta();
    char get_tipo();
    double get_monto();
    double get_saldo();

protected:
private:
    std::string comprobante;
    char tipo;
    double monto;
    double saldo;
    Cuenta* cuenta;

};

#endif
