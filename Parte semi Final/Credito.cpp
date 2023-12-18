/***********************************************************************
 UFA - ESPE
 * Module:  Credito.cpp
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: jueves, 7 de diciembre de 2023
 * Purpose: Implementacion de clase Credito
 ***********************************************************************/

#include "Credito.h"

////////////////////////////////////////////////////////////////////////
// Name:       Credito(int num_cuotas, double _monto, Fecha _fecha_realizado, double _tasa_interes)
// Purpose:    setea valores
// Parameters:
// - num_cuotas
// - monto
// - _fecha_realizado
// - _tasa_interes
// Return:
////////////////////////////////////////////////////////////////////////

Credito::Credito(int num_cuotas, double _monto, Fecha _fecha_realizado, double _tasa_interes){
    n_cuotas_pagar = num_cuotas;
    monto = _monto;
    meses_gracia = 1;
    intervalo_pagos_mes = 1;
    fecha_realizado = _fecha_realizado;
    tasa_interes = _tasa_interes;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_n_cuotas_pagar()
// Purpose:    getter numero de cuotas a pagar
// Parameters:
// Return:     int
////////////////////////////////////////////////////////////////////////

int Credito::get_n_cuotas_pagar(){
    return n_cuotas_pagar;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_cuotas_pagadas()
// Purpose:    getter cuotas pagadas
// Parameters:
// Return:     int
////////////////////////////////////////////////////////////////////////

int Credito::get_cuotas_pagadas(){
    return cuotas_pagadas;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_monto()
// Purpose:    getter monto
// Parameters:
// Return:     double
////////////////////////////////////////////////////////////////////////

double Credito::get_monto(){
    return monto;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_saldo()
// Purpose:    getter saldo
// Parameters:
// Return:     double
////////////////////////////////////////////////////////////////////////

double Credito::get_saldo(){
    return saldo;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_valor_cuota()
// Purpose:    getter valor cuota
// Parameters:
// Return:     double
////////////////////////////////////////////////////////////////////////

double Credito::get_valor_cuota(){
    return valor_cuota;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_n_cuotas_pagar(int nuevo_n_cuotas_pagar)
// Purpose:    setter numero de cuotas a pagar
// Parameters:
// - nuevo_n_cuotas_pagar
// Return:
///////////////////////////////////////////////////////////////////////

void Credito::set_n_cuotas_pagar(int nuevo_n_cuotas_pagar){
    n_cuotas_pagar = nuevo_n_cuotas_pagar;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_cuotas_pagadas(int nuevo_cuotas_pagadas)
// Purpose:    setter cuotas pagadas
// Parameters:
// - nuevo_cuotas_pagadas
// Return:
///////////////////////////////////////////////////////////////////////

void Credito::set_cuotas_pagadas(int nuevo_cuotas_pagadas){
    cuotas_pagadas = nuevo_cuotas_pagadas;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_monto(double nuevo_monto)
// Purpose:    setter monto
// Parameters:
// - nuevo_monto
// Return:
///////////////////////////////////////////////////////////////////////

void Credito::set_monto(double nuevo_monto){
    monto = nuevo_monto;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_saldo(double nuevo_saldo)
// Purpose:    setter saldo
// Parameters:
// - nuevo_saldo
// Return:
///////////////////////////////////////////////////////////////////////

void Credito::set_saldo(double nuevo_saldo){
    saldo = nuevo_saldo;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_valor_cuota(double nuevo_valor_cuota)
// Purpose:    setter valor cuota
// Parameters:
// - nuevo_valor_cuota
// Return:
///////////////////////////////////////////////////////////////////////

void Credito::set_valor_cuota(double nuevo_valor_cuota){
    valor_cuota = nuevo_valor_cuota;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_meses_gracia()
// Purpose:    getter meses de gracia
// Parameters:
// Return:     int
///////////////////////////////////////////////////////////////////////

int Credito::get_meses_gracia(){
    return meses_gracia;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_intervalo_pagos_mes()
// Purpose:    getter intervalo de pagos de mes
// Parameters:
// Return:     int
///////////////////////////////////////////////////////////////////////

int Credito::get_intervalo_pagos_mes(){
    return intervalo_pagos_mes;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_fecha_realizado()
// Purpose:    getter fecha del monto realizado
// Parameters:
// Return:     Fecha
///////////////////////////////////////////////////////////////////////

Fecha Credito::get_fecha_realizado(){
    return fecha_realizado;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_tasa_interes()
// Purpose:    getter tasa de interes
// Parameters:
// Return:     double
///////////////////////////////////////////////////////////////////////

double Credito::get_tasa_interes(){
    return tasa_interes;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_tasa_interes(double nueva_tasa)
// Purpose:    setter tasa de interes
// Parameters:
// - nueva_tasa
// Return:
///////////////////////////////////////////////////////////////////////

void Credito::set_tasa_interes(double nueva_tasa){
    tasa_interes = nueva_tasa;
}

////////////////////////////////////////////////////////////////////////
// Name:       to_String()
// Purpose:    declaracion de clase to_string
// Parameters:
// Return:     char*
///////////////////////////////////////////////////////////////////////

char* Credito::to_string(){

}
