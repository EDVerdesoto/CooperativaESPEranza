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

/**
 * @brief Constructor de CalculosCredito que inicializa la tasa de interés
 * @param _tasa_interes Tasa de interés para los cálculos
 */
CalculosCredito::CalculosCredito(double _tasa_interes){
    tasa_interes = _tasa_interes;
}

/**
 * @brief Calcula el valor de las cuotas mensuales para un préstamo
 * @param num_cuotas Número total de cuotas a pagar
 * @param monto Monto del préstamo
 * @return Valor de las cuotas mensuales
 */
double CalculosCredito::calcular_valor_cuotas(int num_cuotas, double monto){
    return  (monto * (tasa_interes/(100.0*12)) * pow(1+(tasa_interes/(100.0*12)),num_cuotas))/(pow(1+(tasa_interes/(100.0*12)),num_cuotas)-1);
}

/**
 * @brief Calcula el valor de los intereses para cada cuota del préstamo
 * @param num_cuotas Número total de cuotas a pagar
 * @param monto Monto del préstamo
 * @param valor_cuotas Valor de las cuotas mensuales
 * @param intereses Lista donde se almacenan los valores de los intereses
 */
void CalculosCredito::calcular_valor_intereses(int num_cuotas, double monto, double valor_cuotas, ListaDoble<double>* intereses){
    if(num_cuotas>0){
        intereses->insertar_cola(monto * (tasa_interes/(100.0*12)));
        monto = monto - (valor_cuotas -(monto*(tasa_interes/(100.0*12))));
        calcular_valor_intereses(num_cuotas-1, monto, valor_cuotas, intereses);
    }
}

/**
 * @brief Calcula los capitales pagados en cada cuota del préstamo
 * @param valor_cuotas Valor de las cuotas mensuales
 * @param capitales Lista donde se almacenan los valores de los capitales pagados
 * @param cabeza_intereses Cabeza de la lista de intereses
 */
void CalculosCredito::calcular_capitales_pagados(double valor_cuotas, ListaDoble<double>* capitales, Nodo<double>* cabeza_intereses){
    if(cabeza_intereses!=nullptr){
        capitales->insertar_cola(valor_cuotas - cabeza_intereses->get_valor());
        calcular_capitales_pagados(valor_cuotas, capitales, cabeza_intereses->get_siguiente());
    }
}

/**
 * @brief Calcula los saldos restantes después de cada cuota del préstamo
 * @param monto Monto del préstamo
 * @param valor_cuotas Valor de las cuotas mensuales
 * @param saldos Lista donde se almacenan los valores de los saldos restantes
 * @param cabeza_capitales Cabeza de la lista de capitales pagados
 */
void CalculosCredito::calcular_saldos_restantes(double monto, double valor_cuotas, ListaDoble<double>* saldos, Nodo<double>* cabeza_capitales){
    if(cabeza_capitales!=nullptr){
        saldos->insertar_cola(monto);
        monto = monto - cabeza_capitales->get_valor();
        calcular_saldos_restantes(monto, valor_cuotas, saldos, cabeza_capitales->get_siguiente());
    }
}
