/***********************************************************************
 UFA - ESPE
 * Module:  CalculosCredito.cpp
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: jueves, 7 de diciembre de 2023
 * Purpose: Implementacion de clase CalculosCredito
 ***********************************************************************/

#include "CalculosCredito.h"
#include "ListaDoble.cpp"
#include "Nodo.cpp"
#include <cmath>

////////////////////////////////////////////////////////////////////////
// Name:       CalculosCredito(double _tasa_interes)
// Purpose:
// Parameters:
// - _tasa_interes
// Return:
////////////////////////////////////////////////////////////////////////

CalculosCredito::CalculosCredito(double _tasa_interes){
    tasa_interes = _tasa_interes;
}

////////////////////////////////////////////////////////////////////////
// Name:       calcular_valor_cuotas(int num_cuotas, double monto)
// Purpose:    calcula el valor de las cuotas
// Parameters:
// - num_cuotas
// - monto
// Return:     double
////////////////////////////////////////////////////////////////////////

double CalculosCredito::calcular_valor_cuotas(int num_cuotas, double monto){
    return  (monto * (tasa_interes/(100.0*12)) * pow(1+(tasa_interes/(100.0*12)),num_cuotas))/(pow(1+(tasa_interes/(100.0*12)),num_cuotas)-1);
}

////////////////////////////////////////////////////////////////////////
// Name:       calcular_valor_intereses(int num_cuotas, double monto, double valor_cuotas, ListaDoble<double>* intereses)
// Purpose:    calcula el valor de los intereses
// Parameters:
// - num_cuotas
// - monto
// - valor_cuotas
// - intereses
// Return:
////////////////////////////////////////////////////////////////////////

void CalculosCredito::calcular_valor_intereses(int num_cuotas, double monto, double valor_cuotas, ListaDoble<double>* intereses){
    if(num_cuotas>0){
        intereses->insertar_cola(monto * (tasa_interes/(100.0*12)));
        monto = monto - (valor_cuotas -(monto*(tasa_interes/(100.0*12))));
        calcular_valor_intereses(num_cuotas-1, monto, valor_cuotas, intereses);
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       calcular_capitales_pagados(double valor_cuotas, ListaDoble<double>* capitales, Nodo<double>* cabeza_intereses)
// Purpose:    calcula el valor de los intereses
// Parameters:
// - valor_cuotas
// - capitales
// - cabeza_intereses
// Return:
////////////////////////////////////////////////////////////////////////

void CalculosCredito::calcular_capitales_pagados(double valor_cuotas, ListaDoble<double>* capitales, Nodo<double>* cabeza_intereses){
    if(cabeza_intereses!=nullptr){
        capitales->insertar_cola(valor_cuotas - cabeza_intereses->get_valor());
        calcular_capitales_pagados(valor_cuotas, capitales, cabeza_intereses->get_siguiente());
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       calcular_saldos_restantes(double monto, double valor_cuotas, ListaDoble<double>* saldos, Nodo<double>* cabeza_capitales)
// Purpose:    calcula el valor de los saldos restantes
// Parameters:
// - monto
// - valor_cuotas
// - saldos
// - cabeza_capitales
// Return:
////////////////////////////////////////////////////////////////////////

void CalculosCredito::calcular_saldos_restantes(double monto, double valor_cuotas, ListaDoble<double>* saldos, Nodo<double>* cabeza_capitales){
    if(cabeza_capitales!=nullptr){
        saldos->insertar_cola(monto);
        monto = monto - cabeza_capitales->get_valor();
        calcular_saldos_restantes(monto, valor_cuotas, saldos, cabeza_capitales->get_siguiente());
    }
}
