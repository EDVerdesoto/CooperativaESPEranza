/***********************************************************************
 UFA - ESPE
 * Module:  Credito.cpp
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: jueves, 7 de diciembre de 2023 01:11:27 p. m.
 * Purpose: Implementacion de clase Credito
 ***********************************************************************/

#include "Credito.h"

Credito::Credito(int num_cuotas, double _monto){
    ncuotas = num_cuotas;
    monto = _monto;
}
