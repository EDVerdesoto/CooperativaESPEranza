/***********************************************************************
  UFA - ESPE
 * Module:  Movimientos.cpp
 * Author:  Edison Verdesoto, Joan Cobeña
 * Modified: lunes, 29 de enero de 2024 12:07:16
 * Purpose: Implementation of the class Movimientos
 ***********************************************************************/

#include "Movimientos.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

bool esta_vacio_movimientos(const std::string& nombre_archivo) {
    std::ifstream archivo(nombre_archivo);

    if (archivo.is_open() && archivo.peek() == std::ifstream::traits_type::eof()){
        return true;
    } else {
        return false;
    }
}

bool Movimientos::guardar_movimientos(){

    std::string ruta;
    std::string ruta_inicial;
    std::string nombreCarpeta = "Movimientos";
    char tmp[256];

    getcwd(tmp, 256);
    ruta_inicial = std::string(tmp);

    if(_mkdir(nombreCarpeta.c_str()) != 0) {
        if (_chdir(nombreCarpeta.c_str()) != 0){
            return false;
        }
    }
    else{
        _chdir(nombreCarpeta.c_str());
    }

    getcwd(tmp, 256);
    ruta = std::string(tmp);

    std::string nombre_original = ruta + "//" +std::to_string(cuenta->get_num_cuenta())+".csv";
    std::ofstream archivo_original(nombre_original, std::ios::app);

    if(!archivo_original){
        return false;
    }
    else{
        if(esta_vacio_movimientos(nombre_original)){
            archivo_original<<"Cedula,Nombre,Apellido,No. de Cuenta,ID\n";
            archivo_original<<cuenta->get_cliente()->get_persona()->get_cedula()<<","<<
            cuenta->get_cliente()->get_persona()->get_nombre()<<","<<
            cuenta->get_cliente()->get_persona()->get_apellido()<<","<<
            cuenta->get_num_cuenta()<<","<<cuenta->get_cliente()->get_id()<<"\n";
            archivo_original<<"Debito,Credito,Saldo\n";
        }
        if(tipo == 'D'){
            archivo_original<<monto<<","<<0.0<<","<<saldo<<"\n";
        }
        else if(tipo == 'R'){
            archivo_original<<0.0<<","<<monto<<","<<saldo<<"\n";
        }
    }

    archivo_original.close();
    _chdir(ruta_inicial.c_str());

    system("pause");

}

Movimientos::Movimientos(Cuenta* cuenta_asignada)
{
    cuenta = cuenta_asignada;
    saldo = cuenta_asignada->get_saldo();
}

////////////////////////////////////////////////////////////////////////
// Name:       Movimientos::deposito()
// Purpose:    Implementation of Movimientos::deposito()
// Return:     double
////////////////////////////////////////////////////////////////////////

bool Movimientos::deposito(double depositado)
{
    tipo = 'D';
    double MONTO_MINIMO = 5.0;
    if(depositado < MONTO_MINIMO){
        return false;
    }
    else{
        monto = depositado;
        saldo += monto;
        if(guardar_movimientos()){
            cuenta->set_saldo(saldo);
            return true;
        }
        else{
            return false;
        }
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       Movimientos::retiro()
// Purpose:    Implementation of Movimientos::retiro()
// Return:     double
////////////////////////////////////////////////////////////////////////

bool Movimientos::retiro(double retirado)
{
    tipo = 'R';
    if(retirado>monto){
        return false;
    }
    else{
        monto = retirado;
        saldo -= monto;
        if(guardar_movimientos()){
            cuenta->set_saldo(saldo);
            return true;
        }
        else{
            return false;
        }
    }

}

double Movimientos::get_saldo(){
    return saldo;
}

double Movimientos::get_monto(){
    return monto;
}

Cuenta* Movimientos::get_cuenta(){
    return cuenta;
}

char Movimientos::get_tipo(){
    return tipo;
}
