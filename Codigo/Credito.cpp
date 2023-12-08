/***********************************************************************
 UFA - ESPE
 * Module:  Credito.cpp
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: jueves, 7 de diciembre de 2023 01:11:27 p. m.
 * Purpose: Implementacion de clase Credito
 ***********************************************************************/

#include "Credito.h"

Credito::Credito(int num_cuotas, double _monto){
    n_cuotas_pagar = num_cuotas;
    monto = _monto;
}

int Credito::get_n_cuotas_pagar(){
    return n_cuotas_pagar;
}

int Credito::get_cuotas_pagadas(){
    return cuotas_pagadas;
}

double Credito::get_monto(){
    return monto;
}

double Credito::get_saldo(){
    return saldo;
}

double Credito::get_valor_cuota(){
    return valor_cuota;
}

void Credito::set_n_cuotas_pagar(int nuevo_n_cuotas_pagar){
    n_cuotas_pagar = nuevo_n_cuotas_pagar;
}

void Credito::set_cuotas_pagadas(int nuevo_cuotas_pagadas){
    cuotas_pagadas = nuevo_cuotas_pagadas;
}

void Credito::set_monto(double nuevo_monto){
    monto = nuevo_monto;
}

void Credito::set_saldo(double nuevo_saldo){
    saldo = nuevo_saldo;
}

void Credito::set_valor_cuota(double nuevo_valor_cuota){
    valor_cuota = nuevo_valor_cuota;
}

char* Credito::to_string(){

}
