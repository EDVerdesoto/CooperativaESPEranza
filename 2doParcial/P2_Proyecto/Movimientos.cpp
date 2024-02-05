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

/**
 * @brief Verifica si el archivo de movimientos está vacío.
 * @param nombre_archivo Nombre del archivo de movimientos.
 * @return true si el archivo está vacío, false si no lo está.
 */
bool esta_vacio_movimientos(const std::string& nombre_archivo) {
    std::ifstream archivo(nombre_archivo);

    if (archivo.is_open() && archivo.peek() == std::ifstream::traits_type::eof()){
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Guarda los movimientos en un archivo CSV asociado a la cuenta.
 * @return true si los movimientos se guardan correctamente, false en caso contrario.
 */
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

/**
 * @brief Constructor de la clase Movimientos.
 * @param cuenta_asignada Puntero a la cuenta asociada a los movimientos.
 */
Movimientos::Movimientos(Cuenta* cuenta_asignada)
{
    cuenta = cuenta_asignada;
    saldo = cuenta_asignada->get_saldo();
}

/**
 * @brief Realiza un depósito en la cuenta y guarda el movimiento.
 * @param depositado Monto a depositar.
 * @return true si el depósito se realiza correctamente, false en caso contrario.
 */
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

/**
 * @brief Realiza un retiro en la cuenta y guarda el movimiento.
 * @param retirado Monto a retirar.
 * @return true si el retiro se realiza correctamente, false en caso contrario.
 */
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

/**
 * @brief Obtiene el saldo actual de la cuenta.
 * @return Saldo actual de la cuenta.
 */
double Movimientos::get_saldo(){
    return saldo;
}

/**
 * @brief Obtiene el monto del último movimiento realizado.
 * @return Monto del último movimiento.
 */
double Movimientos::get_monto(){
    return monto;
}

/**
 * @brief Obtiene el puntero a la cuenta asociada a los movimientos.
 * @return Puntero a la cuenta asociada.
 */
Cuenta* Movimientos::get_cuenta(){
    return cuenta;
}

/**
 * @brief Obtiene el tipo de movimiento ('D' para depósito, 'R' para retiro).
 * @return Tipo de movimiento.
 */
char Movimientos::get_tipo(){
    return tipo;
}
