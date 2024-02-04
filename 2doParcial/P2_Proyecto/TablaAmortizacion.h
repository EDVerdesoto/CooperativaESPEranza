/***********************************************************************
 UFA - ESPE
 * Module:  TablaAmortizacion.h
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: viernes, 8 de diciembre de 2023
 * Purpose: Declaracion de clase TablaAmortizacion
 ***********************************************************************/

#ifndef TABLAAMORTIZACION_H_INCLUDED
#define TABLAAMORTIZACION_H_INCLUDED

#include "ListaDoble.h"
#include "Credito.h"
#include "Fecha.h"

class TablaAmortizacion{
    public:
        void llenar_tabla_amortizacion();
        void generar_fechas_pago();
        void imprimir();
        TablaAmortizacion(Credito);
        Credito get_credito();
        ListaDoble<int>* get_cuotas_ord();
        ListaDoble<double>* get_saldos_capital();
        ListaDoble<double>* get_intereses();
        ListaDoble<double>* get_pagos_capital();
        ListaDoble<double>* get_valor_cuotas();
        ListaDoble<Fecha>* get_fechas_pago();
        void set_credito(Credito nuevo_credito);
        void set_cuotas_ord(ListaDoble<int>* nuevo_cuotas_ord);
        void set_saldos_capital(ListaDoble<double>* nuevo_saldos_capital);
        void set_intereses(ListaDoble<double>* nuevo_intereses);
        void set_pagos_capital(ListaDoble<double>* nuevo_pagos_capital);
        void set_valor_cuotas(ListaDoble<double>* nuevo_valor_cuotas);
        void set_fechas_pago(ListaDoble<Fecha>* nuevo_fechas_pago);
    private:
        Credito credito;
        ListaDoble<int>* cuotas_ord;
        ListaDoble<double>* saldos_capital;
        ListaDoble<double>* intereses;
        ListaDoble<double>* pagos_capital;
        ListaDoble<double>* valor_cuotas;
        ListaDoble<Fecha>* fechas_pago;
    protected:

};

#endif // TABLAAMORTIZACION_H_INCLUDED
