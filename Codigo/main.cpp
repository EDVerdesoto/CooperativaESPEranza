#include <iostream>
#include <ctime>
#include "menus.h"
#include "ListaDoble.cpp"
#include "Credito.h"
#include "CalculosCredito.h"
#include "TablaAmortizacion.h"

int main()
{
    Fecha sacado(2023,12,16);
    Credito credito(60, 15000, sacado);
    TablaAmortizacion tabla(credito);
    tabla.imprimir();

    system("pause");
    return 0;
}
