/***********************************************************************
 UFA - ESPE
 * Module:  Credito.cpp
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: jueves, 7 de diciembre de 2023
 * Purpose: Implementacion de clase Credito
 ***********************************************************************/

#include "Credito.h"

/**
 * @brief Constructor de Credito que inicializa los atributos del crédito
 * @param num_cuotas Número total de cuotas a pagar
 * @param _monto Monto del crédito
 * @param _fecha_realizado Fecha en la que se realizó el crédito
 * @param _tasa_interes Tasa de interés del crédito
 */
Credito::Credito(int num_cuotas, double _monto, Fecha _fecha_realizado, double _tasa_interes){
    n_cuotas_pagar = num_cuotas;
    monto = _monto;
    meses_gracia = 1;
    intervalo_pagos_mes = 1;
    fecha_realizado = _fecha_realizado;
    tasa_interes = _tasa_interes;
}

/**
 * @brief Obtiene el número total de cuotas a pagar
 * @return Número total de cuotas a pagar
 */
int Credito::get_n_cuotas_pagar(){
    return n_cuotas_pagar;
}

/**
 * @brief Obtiene el número de cuotas pagadas
 * @return Número de cuotas pagadas
 */
int Credito::get_cuotas_pagadas(){
    return cuotas_pagadas;
}

/**
 * @brief Obtiene el monto del crédito
 * @return Monto del crédito
 */
double Credito::get_monto(){
    return monto;
}

/**
 * @brief Obtiene el saldo pendiente del crédito
 * @return Saldo pendiente del crédito
 */
double Credito::get_saldo(){
    return saldo;
}

/**
 * @brief Obtiene el valor de cada cuota del crédito
 * @return Valor de cada cuota del crédito
 */
double Credito::get_valor_cuota(){
    return valor_cuota;
}

/**
 * @brief Establece el número total de cuotas a pagar
 * @param nuevo_n_cuotas_pagar Nuevo número total de cuotas a pagar
 */
void Credito::set_n_cuotas_pagar(int nuevo_n_cuotas_pagar){
    n_cuotas_pagar = nuevo_n_cuotas_pagar;
}

/**
 * @brief Establece el número de cuotas pagadas
 * @param nuevo_cuotas_pagadas Nuevo número de cuotas pagadas
 */
void Credito::set_cuotas_pagadas(int nuevo_cuotas_pagadas){
    cuotas_pagadas = nuevo_cuotas_pagadas;
}

/**
 * @brief Establece el monto del crédito
 * @param nuevo_monto Nuevo monto del crédito
 */
void Credito::set_monto(double nuevo_monto){
    monto = nuevo_monto;
}

/**
 * @brief Establece el saldo pendiente del crédito
 * @param nuevo_saldo Nuevo saldo pendiente del crédito
 */
void Credito::set_saldo(double nuevo_saldo){
    saldo = nuevo_saldo;
}

/**
 * @brief Establece el valor de cada cuota del crédito
 * @param nuevo_valor_cuota Nuevo valor de cada cuota del crédito
 */
void Credito::set_valor_cuota(double nuevo_valor_cuota){
    valor_cuota = nuevo_valor_cuota;
}

/**
 * @brief Obtiene el número de meses de gracia del crédito
 * @return Número de meses de gracia del crédito
 */
int Credito::get_meses_gracia(){
    return meses_gracia;
}

/**
 * @brief Obtiene el intervalo de pagos en meses del crédito
 * @return Intervalo de pagos en meses del crédito
 */
int Credito::get_intervalo_pagos_mes(){
    return intervalo_pagos_mes;
}

/**
 * @brief Obtiene la fecha en la que se realizó el crédito
 * @return Fecha en la que se realizó el crédito
 */

Fecha Credito::get_fecha_realizado(){
    return fecha_realizado;
}

/**
 * @brief Obtiene la tasa de interés del crédito
 * @return Tasa de interés del crédito
 */
double Credito::get_tasa_interes(){
    return tasa_interes;
}

/**
 * @brief Establece la tasa de interés del crédito
 * @param nueva_tasa Nueva tasa de interés del crédito
 */
void Credito::set_tasa_interes(double nueva_tasa){
    tasa_interes = nueva_tasa;
}

/**
 * @brief Convierte la información del crédito a una cadena de caracteres (sin implementar)
 * @return Cadena de caracteres que representa la información del crédito
 */
char* Credito::to_string(){

}
