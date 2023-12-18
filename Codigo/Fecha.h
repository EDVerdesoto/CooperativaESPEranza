/***********************************************************************
 UFA - ESPE
 * Module:  Fecha.h
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: jueves, 7 de diciembre de 2023 01:11:27 p. m.
 * Purpose: Declaracion de clase Fecha
 ***********************************************************************/

#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include <iostream>
#include "Nodo.h"
#include <ctime>
#include <iomanip>

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
        bool es_dia_habil();
        bool es_feriado();
        bool es_finde();
        std::string to_string();
        std::string to_string_documento();
<<<<<<< HEAD
        void string_to_fecha(const std::string);
=======
        void string_to_fecha(std::string to_string_documento());
>>>>>>> 587086ee3da88a0073a36ccb62f325b8ba28bf78
        void imprimir();

    protected:

    private:
        int dia;
        int mes;
        int anuario;
        int hora;
        int minutos;
        int segundos;
};

#endif // FECHA_H_INCLUDED
