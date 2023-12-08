/***********************************************************************
 UFA - ESPE
 * Module:  Fecha.h
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: jueves, 7 de diciembre de 2023 01:11:27 p. m.
 * Purpose: Declaracion de clase Fecha
 ***********************************************************************/

#include "Nodo.h"

#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

class Fecha{
    public:
        Fecha();
        Fecha(int _anuario, int _mes, int _dia);
        Fecha(int _anuario, int _mes, int _dia, int _hora, int _minutos, int _segundos);
        int get_anuario();
        void set_anuario(int);
        int get_mes();
        void set_mes(int);
        int get_dia();
        void set_dia(int);
        int get_hora();
        void set_hora(int);
        int get_minutos();
        void set_minutos(int);
        int get_segundos();
        void set_segundos(int);

    protected:

    private:
        int dia;
        int mes;
        int anuario;
        int hora;
        int minutos;
        int segundos;
        char* fecha_t;
};

#endif // FECHA_H_INCLUDED
