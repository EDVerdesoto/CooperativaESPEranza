/***********************************************************************
 UFA - ESPE
 * Module:  Fecha.cpp
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: jueves, 7 de diciembre de 2023 01:11:27 p. m.
 * Purpose: Implementacion de clase Fecha
 ***********************************************************************/

#include <iostream>
#include "Fecha.h"
#include <ctime>
#include <iomanip>

////////////////////////////////////////////////////////////////////////
// Name:       Fecha()
// Purpose:    formato de fecha
// Parameters:
// Return:
////////////////////////////////////////////////////////////////////////

Fecha::Fecha(){
    std::time_t tiempo_actual = std::time(nullptr);
    std::tm tm_actual = *std::localtime(&tiempo_actual);
    std::mktime(&tm_actual);

    dia = tm_actual.tm_mday;
    mes = tm_actual.tm_mon + 1;
    anuario = tm_actual.tm_year + 1900;
    hora = tm_actual.tm_hour;
    minutos = tm_actual.tm_min;
    segundos = tm_actual.tm_sec;
}

////////////////////////////////////////////////////////////////////////
// Name:       Fecha(int _anuario, int _mes, int _dia)
// Purpose:    setea la fecha
// Parameters:
// - _anuario
// - _mes
// - _dia
// Return:
////////////////////////////////////////////////////////////////////////

Fecha::Fecha(int _anuario, int _mes, int _dia){
    anuario = _anuario;
    set_mes(_mes);
    set_dia(_dia);
    hora = 0;
    minutos = 0;
    segundos = 1;
}

////////////////////////////////////////////////////////////////////////
// Name:       Fecha(int _anuario, int _mes, int _dia, int _hora, int _minutos, int _segundos)
// Purpose:    setea la fecha
// Parameters:
// - _anuario
// - _mes
// - _dia
// - _hora
// -_minutos
// -_segundos
// Return:
////////////////////////////////////////////////////////////////////////
Fecha::Fecha(int _anuario, int _mes, int _dia, int _hora, int _minutos, int _segundos){
    anuario = _anuario;
    mes = _mes;
    dia = _dia;
    hora = _hora;
    minutos = _minutos;
    segundos = _segundos;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_anuario()
// Purpose:    getter anuario
// Parameters:
// Return:     int
////////////////////////////////////////////////////////////////////////

int Fecha::get_anuario(){
    return anuario;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_anuario(int nuevo_anuario)
// Purpose:    setter anuario
// Parameters:
// - nuevo_anuario
// Return:
////////////////////////////////////////////////////////////////////////

void Fecha::set_anuario(int nuevo_anuario){
    anuario = nuevo_anuario;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_mes()
// Purpose:    getter mes
// Parameters:
// Return:     int
////////////////////////////////////////////////////////////////////////

int Fecha::get_mes(){
    return mes;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_mes(int nuevo_mes)
// Purpose:    setter mes
// Parameters:
// - nuevo_mes
// Return:
////////////////////////////////////////////////////////////////////////

void Fecha::set_mes(int nuevo_mes){
    int meses_pasados = (nuevo_mes >12) ? 12 : 0;

    mes = nuevo_mes - meses_pasados;

    if(meses_pasados>0)set_anuario(anuario+1);
}

////////////////////////////////////////////////////////////////////////
// Name:       get_dia()
// Purpose:    getter dia
// Parameters:
// Return:      int
////////////////////////////////////////////////////////////////////////

int Fecha::get_dia(){
    return dia;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_dia(int nuevo_dia)
// Purpose:    setter dia
// Parameters:
// - nuevo_dia
// Return:
////////////////////////////////////////////////////////////////////////

void Fecha::set_dia(int nuevo_dia){
    int ndias_mes_pasado = 0;

    if(nuevo_dia>28){
        if (mes==2){
            if(anuario%4!=0){
                ndias_mes_pasado = 28;
            }
            else {
                ndias_mes_pasado = (nuevo_dia > 29) ? 29 : 0;
            }
        }
        else if (((mes < 8) && mes%2!=0)||(mes >= 8) && mes%2==0){
            ndias_mes_pasado = (nuevo_dia > 31) ? 31 : 0;
        }
        else {
            ndias_mes_pasado = (nuevo_dia > 30) ? 30 : 0;
        }
    }

    dia = nuevo_dia - ndias_mes_pasado;

    if(ndias_mes_pasado>0)set_mes(mes+1);
}

////////////////////////////////////////////////////////////////////////
// Name:       get_hora()
// Purpose:    getter hora
// Parameters:
// Return:      int
////////////////////////////////////////////////////////////////////////

int Fecha::get_hora(){
    return hora;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_hora(int nueva_hora)
// Purpose:    setter hora
// Parameters:
// - nueva_hora
// Return:
////////////////////////////////////////////////////////////////////////

void Fecha::set_hora(int nueva_hora){
    hora = nueva_hora;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_minutos()
// Purpose:    getter minutos
// Parameters:
// Return:      int
////////////////////////////////////////////////////////////////////////

int Fecha::get_minutos(){
    return minutos;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_minutos(int nuevo_minuto)
// Purpose:    setter minuto
// Parameters:
// - nuevo_minuto
// Return:
////////////////////////////////////////////////////////////////////////

void Fecha::set_minutos(int nuevo_minutos){
    minutos = nuevo_minutos;
}

////////////////////////////////////////////////////////////////////////
// Name:       get_segundos()
// Purpose:    getter segundos
// Parameters:
// Return:      int
////////////////////////////////////////////////////////////////////////

int Fecha::get_segundos(){
    return segundos;
}

////////////////////////////////////////////////////////////////////////
// Name:       set_segundos(int nuevo_segundos)
// Purpose:    setter segundos
// Parameters:
// - nuevo_segundos
// Return:
////////////////////////////////////////////////////////////////////////

void Fecha::set_segundos(int nuevo_segundos){
    segundos = nuevo_segundos;
}

////////////////////////////////////////////////////////////////////////
// Name:       to_string()
// Purpose:    pasar de formato fecha a string
// Parameters:
// Return:     string
////////////////////////////////////////////////////////////////////////


std::string Fecha::to_string(){
    auto t = std::time(nullptr);
    std::tm tm_fecha = {};
    tm_fecha.tm_mday = dia;
    tm_fecha.tm_mon = mes;
    tm_fecha.tm_year = anuario;

    std::mktime(&tm_fecha);

    std::ostringstream oss;
    oss << std::put_time(&tm_fecha, "%Y-%m-%d");
    auto str = oss.str();

    return oss.str();
}

////////////////////////////////////////////////////////////////////////
// Name:       to_string_documento()
// Purpose:    pasar de formato fecha a string del documento
// Parameters:
// Return:     string
////////////////////////////////////////////////////////////////////////

std::string Fecha::to_string_documento(){
    auto t = std::time(nullptr);
    std::tm tm_fecha = {};
    tm_fecha.tm_mday = dia;
    tm_fecha.tm_mon = mes;
    tm_fecha.tm_year = anuario;

    std::mktime(&tm_fecha);

    std::ostringstream oss;
    oss << std::put_time(&tm_fecha, "%Y-%m-%dT_%H-%M-%SZ");
    auto str = oss.str();

    return oss.str();
}

////////////////////////////////////////////////////////////////////////
// Name:       imprimir()
// Purpose:    imprime la fecha
// Parameters:
// Return:
////////////////////////////////////////////////////////////////////////

void Fecha::imprimir(){
    printf("%d", dia);
    printf("/%d", mes);
    printf("/%d", anuario);
}

////////////////////////////////////////////////////////////////////////
// Name:       es_dia_habil()
// Purpose:    valida si hay dia habil
// Parameters:
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Fecha::es_dia_habil(){
    bool habil = true;
    if(es_finde()){
        habil = false;
    }
    else if(es_feriado()){
        habil = false;
    }
    return habil;
}

////////////////////////////////////////////////////////////////////////
// Name:       es_feriado()
// Purpose:    valida si hay feriados
// Parameters:
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Fecha::es_feriado(){
    bool es_feriado = false;

    if(mes==1){
        if(dia ==1) es_feriado = true;
    }
    else if(mes==2){
        if(dia == 12 || dia == 13) es_feriado = true;
    }

    else if(mes==3){
        if(dia == 29) es_feriado = true;
    }
    else if(mes==4){

    }
    else if(mes==5){
        if(dia == 1 || dia == 24) es_feriado = true;
    }
    else if(mes==6){

    }
    else if(mes==7){

    }
    else if(mes==8){
        if(dia == 10)es_feriado = true;
    }
    else if(mes==9){
         if(dia == 26)es_feriado = true;
    }
    else if(mes==10){
         if(dia == 9)es_feriado = true;
    }
    else if(mes==11){
        if(dia == 2 || dia == 3)es_feriado = true;
    }

    else if(mes==12){
        if(dia == 24 || dia == 25 || dia == 31) es_feriado = true;
    }

    return es_feriado;
}

////////////////////////////////////////////////////////////////////////
// Name:       es_finde()
// Purpose:    valida si es fin de semana
// Parameters:
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Fecha::es_finde(){
    std::tm tm_fecha = {};
    tm_fecha.tm_mday = dia;
    tm_fecha.tm_mon = mes - 1;
    tm_fecha.tm_year = anuario - 1900;

    std::mktime(&tm_fecha);

    int dia_semana = tm_fecha.tm_wday;

    return (dia_semana == 0 || dia_semana == 6);
}

/*
bool operator<(Fecha fecha1, Fecha fecha2){
    bool menor;
    if(fecha1.get_anuario()<fecha2.get_anuario()){
        menor = true;
    }
    else if(fecha1.get_anuario() == fecha2.get_anuario()){
        if(fecha1.get_mes()<fecha2.get_mes()){
            menor = true;
        }
        else if(fecha1.get_mes() == fecha2.get_mes()){
            if(fecha1.get_dia()<fecha2.get_dia()){
                menor = true;
            }
            else if(fecha1.get_dia() == fecha2.get_dia()){
                if(fecha1.get_dia()<fecha2.get_dia()){
                    menor = true;
                }
                else if(fecha1.get_dia() == fecha2.get_dia()){
                    if(fecha1.get_hora()<fecha2.get_hora()){
                        menor = true;
                    }
                    else if(fecha1.get_hora() == fecha2.get_hora()){
                        if(fecha1.get_minutos()<fecha2.get_minutos()){
                            menor = true;
                        }
                        else if(fecha1.get_minutos() == fecha2.get_minutos()){
                            if(fecha1.get_segundos()<fecha2.get_segundos()){
                                menor = true;
                            }
                            else if(fecha1.get_segundos() == fecha2.get_segundos()){
                                menor = false;
                            }
                            else{
                                menor = false;
                            }
                        }
                        else{
                            menor = false;
                        }
                    }
                    else{
                        menor = false;
                    }
                }
                else{
                    menor = false;
                }
            }
            else{
                menor = false;
            }
        }
        else{
            menor = false;
        }
    }
    else{
        menor = false;
    }

    return menor;
}

bool operator>(Fecha fecha1, Fecha fecha2){
    bool mayor;
    if(fecha1.get_anuario()>fecha2.get_anuario()){
        mayor = true;
    }
    else if(fecha1.get_anuario() == fecha2.get_anuario()){
        if(fecha1.get_mes()>fecha2.get_mes()){
            mayor = true;
        }
        else if(fecha1.get_mes() == fecha2.get_mes()){
            if(fecha1.get_dia()>fecha2.get_dia()){
                mayor = true;
            }
            else if(fecha1.get_dia() == fecha2.get_dia()){
                if(fecha1.get_dia()>fecha2.get_dia()){
                    mayor = true;
                }
                else if(fecha1.get_dia() == fecha2.get_dia()){
                    if(fecha1.get_hora()>fecha2.get_hora()){
                        mayor = true;
                    }
                    else if(fecha1.get_hora() == fecha2.get_hora()){
                        if(fecha1.get_minutos()>fecha2.get_minutos()){
                            mayor = true;
                        }
                        else if(fecha1.get_minutos() == fecha2.get_minutos()){
                            if(fecha1.get_segundos()>fecha2.get_segundos()){
                                mayor = true;
                            }
                            else if(fecha1.get_segundos() == fecha2.get_segundos()){
                                mayor = false;
                            }
                            else{
                                mayor = false;
                            }
                        }
                        else{
                            mayor = false;
                        }
                    }
                    else{
                        mayor = false;
                    }
                }
                else{
                    mayor = false;
                }
            }
            else{
                mayor = false;
            }
        }
        else{
            mayor = false;
        }
    }
    else{
        mayor = false;
    }

    return mayor;
}
*/
