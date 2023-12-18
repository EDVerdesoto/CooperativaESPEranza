/***********************************************************************
 UFA - ESPE
 * Module:  TablaAmortizacion.cpp
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: viernes, 8 de diciembre de 2023
 * Purpose: Declaracion de clase TablaAmortizacion
 ***********************************************************************/

#include <iostream>
#include <iomanip>
#include "TablaAmortizacion.h"
#include "CalculosCredito.h"
#include "Fecha.h"
#include "ListaDoble.cpp"
#include "Nodo.cpp"

TablaAmortizacion::TablaAmortizacion(Credito credito_usar){
    credito = credito_usar;
    cuotas_ord = new ListaDoble<int>();
    saldos_capital= new ListaDoble<double>();
    intereses= new ListaDoble<double>();
    pagos_capital= new ListaDoble<double>();
    valor_cuotas= new ListaDoble<double>();
    fechas_pago= new ListaDoble<Fecha>();
    llenar_tabla_amortizacion();
}

void TablaAmortizacion::llenar_tabla_amortizacion(){
    CalculosCredito calculos(credito.get_tasa_interes());
    double v_cuotas = calculos.calcular_valor_cuotas(credito.get_n_cuotas_pagar(), credito.get_monto());
    int n_ord = 1;
    while(n_ord<=credito.get_n_cuotas_pagar()){
        cuotas_ord->insertar_cola(n_ord);
        valor_cuotas->insertar_cola(v_cuotas);
        n_ord++;
    }

    calculos.calcular_valor_intereses(credito.get_n_cuotas_pagar(), credito.get_monto(), v_cuotas, intereses);
    calculos.calcular_capitales_pagados(v_cuotas, pagos_capital, intereses->get_cabeza());
    calculos.calcular_saldos_restantes(credito.get_monto(), v_cuotas, saldos_capital, pagos_capital->get_cabeza());
    generar_fechas_pago();
}

void TablaAmortizacion::generar_fechas_pago(){
    Fecha fecha_sacado = credito.get_fecha_realizado();
    int ncuotas = credito.get_n_cuotas_pagar();
    int meses_gracia = credito.get_meses_gracia();
    int intervalo_pagos_mes = credito.get_intervalo_pagos_mes();
    Fecha fecha_gen = fecha_sacado;
    fecha_gen.set_mes(fecha_gen.get_mes() + meses_gracia);
    int n_gen = 0;

    while(fecha_gen.es_finde() || fecha_gen.es_feriado()){
        fecha_gen.set_dia(fecha_gen.get_dia()+1);
    }
    fechas_pago->insertar_cola(fecha_gen);
    n_gen++;

    while(n_gen<ncuotas){
        fecha_gen.set_mes(fecha_gen.get_mes() + intervalo_pagos_mes);
        while(fecha_gen.es_finde() || fecha_gen.es_feriado()){
            fecha_gen.set_dia(fecha_gen.get_dia()+1);
        }
        fechas_pago->insertar_cola(fecha_gen);
        n_gen++;
    }
}



void TablaAmortizacion::imprimir(){
    int n_mostrados = 0;
    int n_mostrar = credito.get_n_cuotas_pagar();
    Nodo<int>* ord = cuotas_ord->get_cabeza();
    Nodo<double>* saldo_cap = saldos_capital->get_cabeza();
    Nodo<double>* interes = intereses->get_cabeza();
    Nodo<double>* capital_pag = pagos_capital->get_cabeza();
    Nodo<double>* valor_cuota = valor_cuotas->get_cabeza();
    Nodo<Fecha>* aux_fecha_pagar = fechas_pago->get_cabeza();
    Fecha fecha_pagar;
    int ancho_ord = 10, ancho_vcuota = 12, ancho_capital = 12, ancho_interes = 10, ancho_saldo = 15, ancho_fecha = 14;

    std::cout<< '|'<<std::setw(ancho_ord)<<"No. Cuota"<< '|'<<std::setw(ancho_vcuota)<<"Valor Cuota";
    std::cout<<'|'<<std::setw(ancho_capital)<<"Pago capital"<<'|'<<std::setw(ancho_interes)<<"Intereses";
    std::cout<<'|'<<std::setw(ancho_saldo)<<"Saldo capital"<<'|'<<std::setw(ancho_fecha)<<"Fecha de pago"<<'|';
    printf("\n");
    while(n_mostrados < n_mostrar){
        fecha_pagar = aux_fecha_pagar->get_valor();
        std::cout<< '|'<<std::setw(ancho_ord)<<ord->get_valor()<<'|'<<std::setw(ancho_vcuota)<<valor_cuota->get_valor();
        std::cout<<'|'<<std::setw(ancho_capital)<<capital_pag->get_valor()<<'|'<<std::setw(ancho_interes)<<interes->get_valor();
        std::cout<<'|'<<std::setw(ancho_saldo)<<saldo_cap->get_valor()<<'|'<<std::setw(ancho_fecha)<<fecha_pagar.to_string()<<'|';
        printf("\n");

        ord = ord->get_siguiente();
        saldo_cap = saldo_cap->get_siguiente();
        interes = interes->get_siguiente();
        capital_pag = capital_pag->get_siguiente();
        valor_cuota = valor_cuota->get_siguiente();
        aux_fecha_pagar = aux_fecha_pagar->get_siguiente();
        n_mostrados++;
    }
}

Credito TablaAmortizacion::get_credito(){
    return credito;
}

ListaDoble<int>* TablaAmortizacion::get_cuotas_ord(){
    return cuotas_ord;
}

ListaDoble<double>* TablaAmortizacion::get_saldos_capital(){
    return saldos_capital;
}

ListaDoble<double>* TablaAmortizacion::get_intereses(){
    return intereses;
}

ListaDoble<double>* TablaAmortizacion::get_pagos_capital(){
    return pagos_capital;
}

ListaDoble<double>* TablaAmortizacion::get_valor_cuotas(){
    return valor_cuotas;
}

ListaDoble<Fecha>* TablaAmortizacion::get_fechas_pago(){
    return fechas_pago;
}

void TablaAmortizacion::set_credito(Credito nuevo_credito){
    credito = nuevo_credito;
}

void TablaAmortizacion::set_cuotas_ord(ListaDoble<int>* nuevo_cuotas_ord){
    cuotas_ord = nuevo_cuotas_ord;
}

void TablaAmortizacion::set_saldos_capital(ListaDoble<double>* nuevo_saldos_capital){
    saldos_capital = nuevo_saldos_capital;
}

void TablaAmortizacion::set_intereses(ListaDoble<double>* nuevo_intereses){
    intereses = nuevo_intereses;
}

void TablaAmortizacion::set_pagos_capital(ListaDoble<double>* nuevo_pagos_capital){
    pagos_capital = nuevo_pagos_capital;
}

void TablaAmortizacion::set_valor_cuotas(ListaDoble<double>* nuevo_valor_cuotas){
    valor_cuotas = nuevo_valor_cuotas;
}

void TablaAmortizacion::set_fechas_pago(ListaDoble<Fecha>* nuevo_fechas_pago){
    fechas_pago = nuevo_fechas_pago;
}
