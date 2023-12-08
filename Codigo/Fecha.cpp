/***********************************************************************
 UFA - ESPE
 * Module:  Fecha.cpp
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: jueves, 7 de diciembre de 2023 01:11:27 p. m.
 * Purpose: Implementacion de clase Fecha
 ***********************************************************************/

#include "Fecha.h"

Fecha::Fecha(){

}

Fecha::Fecha(int _anuario, int _mes, int _dia){
    anuario = _anuario;
    mes = _mes;
    dia = _dia;
    hora = 0;
    minutos = 0;
    segundos = 1;
}

Fecha::Fecha(int _anuario, int _mes, int _dia, int _hora, int _minutos, int _segundos){
    anuario = _anuario;
    mes = _mes;
    dia = _dia;
    hora = _hora;
    minutos = _minutos;
    segundos = _segundos;
}

int Fecha::get_anuario(){
    return anuario;
}

void Fecha::set_anuario(int nuevo_anuario){
    anuario = nuevo_anuario;
}

int Fecha::get_mes(){
    return mes;
}

void Fecha::set_mes(int nuevo_mes){
    mes = nuevo_mes;
}

int Fecha::get_dia(){
    return dia;
}

void Fecha::set_dia(int nuevo_dia){
    dia = nuevo_dia;
}

int Fecha::get_hora(){
    return hora;
}

void Fecha::set_hora(int nueva_hora){
    hora = nueva_hora;
}

int Fecha::get_minutos(){
    return minutos;
}

void Fecha::set_minutos(int nuevo_minutos){
    minutos = nuevo_minutos;
}

int Fecha::get_segundos(){
    return segundos;
}

void Fecha::set_segundos(int nuevo_segundos){
    segundos = nuevo_segundos;
}


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

