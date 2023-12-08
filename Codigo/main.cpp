#include <iostream>
#include "menus.h"
#include "ListaDoble.cpp"
#include "CalculosCredito.h"

int main()
{
    ListaDoble<double> intereses;
    ListaDoble<double> saldos;
    ListaDoble<double> capitales;
    double monto = 15109;
    int cuotas = 60;

    CalculosCredito calculos(13.32, 0);
    double valor_cuota = calculos.calcular_valor_cuotas(cuotas, monto);
    calculos.calcular_valor_intereses(cuotas, monto, valor_cuota, &intereses);
    calculos.calcular_capitales_pagados(valor_cuota, &capitales, intereses.get_cabeza());
    calculos.calcular_saldos_restantes(monto, valor_cuota, &saldos, capitales.get_cabeza());
    printf("\nValor cuota %f", valor_cuota);
    printf("\nIntereses");
    intereses.imprimir();
    printf("\nCapitales");
    capitales.imprimir();
    printf("\nSaldos");
    saldos.imprimir();

    system("pause");
    return 0;
}
