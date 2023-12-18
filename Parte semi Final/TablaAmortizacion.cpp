/***********************************************************************
 UFA - ESPE
 * Module:  TablaAmortizacion.cpp
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: viernes, 8 de diciembre de 2023
 * Purpose: Declaracion de clase TablaAmortizacion
 ***********************************************************************/

#include <iostream>
#include "TablaAmortizacion.h"
#include "CalculosCredito.h"
#include "Fecha.h"
#include "ListaDoble.cpp"
#include "Nodo.cpp"

////////////////////////////////////////////////////////////////////////
// Name:       TablaAmortizacion(Credito credito_usar)
// Purpose:    tabla de amortizacion
// Parameters:
// - credito_usar
// Return:
///////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////
// Name:       llenar_tabla_amortizacion()
// Purpose:    llena la tabla de amortizacion
// Parameters:
// Return:     void
///////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////
// Name:       generar_fechas_pago()
// Purpose:    genera las fechas de pago
// Parameters:
// Return:     void
///////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////
// Name:       imprimir()
// Purpose:    imprime la tabla de amortizacion
// Parameters:
// Return:     void
///////////////////////////////////////////////////////////////////////

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
    std::cout<<"No. Cuota|Valor Cuota|Pago al capital|Intereses|Saldo capital|Fecha de pago";
    printf("\n");
    while(n_mostrados < n_mostrar){
        fecha_pagar = aux_fecha_pagar->get_valor();
        std::cout<<ord->get_valor()<<"\t|\t"<<valor_cuota->get_valor();
        std::cout<<"\t|\t"<<capital_pag->get_valor()<<"\t|\t"<<interes->get_valor();
        std::cout<<"\t|\t"<<saldo_cap->get_valor()<<"\t|\t";
        fecha_pagar.imprimir();
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

////////////////////////////////////////////////////////////////////////
// Name:       get_credito()
// Purpose:    getter del credito
// Parameters:
// Return:     Credito
///////////////////////////////////////////////////////////////////////

Credito TablaAmortizacion::get_credito(){
    return credito;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_cuotas_ord()
// Purpose:    getter de las cuotas
// Parameters:
// Return:     ListaDoble
///////////////////////////////////////////////////////////////////////

ListaDoble<int>* TablaAmortizacion::get_cuotas_ord(){
    return cuotas_ord;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_saldos_capital()
// Purpose:    getter de los saldos del capital
// Parameters:
// Return:     ListaDoble
///////////////////////////////////////////////////////////////////////

ListaDoble<double>* TablaAmortizacion::get_saldos_capital(){
    return saldos_capital;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_intereses()
// Purpose:    getter de los intereses
// Parameters:
// Return:     ListaDoble
///////////////////////////////////////////////////////////////////////

ListaDoble<double>* TablaAmortizacion::get_intereses(){
    return intereses;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_pagos_capital()
// Purpose:    getter de los pagos del capital
// Parameters:
// Return:     ListaDoble
///////////////////////////////////////////////////////////////////////

ListaDoble<double>* TablaAmortizacion::get_pagos_capital(){
    return pagos_capital;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_valor_coutas()
// Purpose:    getter del valor de cuotas
// Parameters:
// Return:     ListaDoble
///////////////////////////////////////////////////////////////////////

ListaDoble<double>* TablaAmortizacion::get_valor_cuotas(){
    return valor_cuotas;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_fechas_pago()
// Purpose:    getter de las fechas de pago
// Parameters:
// Return:     ListaDoble
///////////////////////////////////////////////////////////////////////

ListaDoble<Fecha>* TablaAmortizacion::get_fechas_pago(){
    return fechas_pago;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_credito(Credito nuevo_credito)
// Purpose:    setter del credito
// Parameters:
// - nuevo_credito
// Return:
///////////////////////////////////////////////////////////////////////

void TablaAmortizacion::set_credito(Credito nuevo_credito){
    credito = nuevo_credito;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_cuotas_ord(ListaDoble<int>* nuevo_cuotas_ord)
// Purpose:    setter de las cuotas ordenadas
// Parameters:
// - nuevo_cuotas_ord
// Return:
///////////////////////////////////////////////////////////////////////

void TablaAmortizacion::set_cuotas_ord(ListaDoble<int>* nuevo_cuotas_ord){
    cuotas_ord = nuevo_cuotas_ord;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_credito(Credito nuevo_credito)
// Purpose:    setter del credito
// Parameters:
// - nuevo_credito
// Return:
///////////////////////////////////////////////////////////////////////

void TablaAmortizacion::set_saldos_capital(ListaDoble<double>* nuevo_saldos_capital){
    saldos_capital = nuevo_saldos_capital;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_intereses(ListaDoble<double>* nuevo_intereses)
// Purpose:    setter de los interes
// Parameters:
// - nuevo_intereses
// Return:
///////////////////////////////////////////////////////////////////////

void TablaAmortizacion::set_intereses(ListaDoble<double>* nuevo_intereses){
    intereses = nuevo_intereses;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_pagos_capital(ListaDoble<double>* nuevo_pagos_capital)
// Purpose:    setter de los pagos de capital
// Parameters:
// - nuevo_pagos_capital
// Return:
///////////////////////////////////////////////////////////////////////

void TablaAmortizacion::set_pagos_capital(ListaDoble<double>* nuevo_pagos_capital){
    pagos_capital = nuevo_pagos_capital;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_valor_cuotas(ListaDoble<double>* nuevo_valor_cuotas)
// Purpose:    setter del valor de cuotas
// Parameters:
// - nuevo_valor_cuotas
// Return:
///////////////////////////////////////////////////////////////////////

void TablaAmortizacion::set_valor_cuotas(ListaDoble<double>* nuevo_valor_cuotas){
    valor_cuotas = nuevo_valor_cuotas;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_fechass_pagos(ListaDoble<Fecha>* nuevo_fechas_pago)
// Purpose:    setter de las fechas de pago
// Parameters:
// - nuevo_fechas_pago
// Return:
///////////////////////////////////////////////////////////////////////

void TablaAmortizacion::set_fechas_pago(ListaDoble<Fecha>* nuevo_fechas_pago){
    fechas_pago = nuevo_fechas_pago;
}
