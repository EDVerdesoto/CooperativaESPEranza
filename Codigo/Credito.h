/***********************************************************************
 UFA - ESPE
 * Module:  Credito.h
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: jueves, 7 de diciembre de 2023 01:11:27 p. m.
 * Purpose: Declaracion de clase Credito
 ***********************************************************************/

#ifndef CREDITO_H_INCLUDED
#define CREDITO_H_INCLUDED

#include "Fecha.h"

class Credito{
    public:
        Credito(int num_cuotas, double _monto);
        int get_n_cuotas_pagar();
        int get_cuotas_pagadas();
        double get_monto();
        double get_saldo();
        double get_valor_cuota();
        void set_n_cuotas_pagar(int);
        void set_cuotas_pagadas(int);
        void set_monto(double);
        void set_saldo(double);
        void set_valor_cuota(double);
        char* to_string();
    protected:

    private:
        int n_cuotas_pagar;
        int cuotas_pagadas;
        double monto;
        double saldo;
        double valor_cuota;
        Fecha primer_cuota;
};



#endif // CREDITO_H_INCLUDED
