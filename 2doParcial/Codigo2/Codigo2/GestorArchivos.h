#ifndef GESTORARCHIVOS_H_INCLUDED
#define GESTORARCHIVOS_H_INCLUDED

#include <iostream>
#include <fstream>

#include <string>
#include "Credito.h"
#include "Fecha.h"

int contar_lineas(const std::string& nombre_archivo);
bool esta_vacio(const std::string& nombre_archivo);
bool crear_backup(Fecha fecha);

bool existe_credito(int num_credito){
    std::string nombre_original = "Creditos.csv";
    if(num_credito>=contar_lineas(nombre_original)){
        return false;
    }
    else{
        return true;
    }
}


Credito obtener_credito(int num_credito){
    std::string nombre_original = "Creditos.csv";
    std::ifstream archivo_original(nombre_original);
    std::string linea;
    int contador = 0;
    while (std::getline(archivo_original, linea)&&(contador<num_credito)) {
        contador++;
    }
    std::istringstream ss(linea);

    std::string snum;
    std::string smonto;
    std::string sncuotas;
    std::string stasa;
    std::string sfecha;

    std::getline(ss, snum, ',');
    std::getline(ss, smonto, ',');
    std::getline(ss, sncuotas, ',');
    std::getline(ss, stasa, ',');
    std::getline(ss, sfecha, ',');

    Fecha fecha_obt;
    fecha_obt.string_to_fecha(sfecha);

    return Credito(std::stoi(sncuotas), std::stof(smonto), fecha_obt, std::stof(stasa));
}

bool guardar_credito(Credito credito){
    int num_credito;

    std::string nombre_original = "Creditos.csv";
    std::ofstream archivo_original(nombre_original, std::ios::app);

    if(!archivo_original){
        return false;
    }
    else{
        if(esta_vacio(nombre_original)){
            archivo_original<<"ID,Monto,No. Cuotas,Tasa Interes,Fecha obtenido\n";
            num_credito = contar_lineas(nombre_original)+1;
        }
        else{
            num_credito = contar_lineas(nombre_original);
        }
        archivo_original<<num_credito<<","<<credito.get_monto()<<","<<credito.get_n_cuotas_pagar()<<","<<credito.get_tasa_interes()<<","<<credito.get_fecha_realizado().to_string()<<"\n";
    }

    archivo_original.close();
    Fecha fecha;
    crear_backup(fecha);
    return true;
}

bool crear_backup(Fecha fecha){
    bool creado;
    std::string nombre_original = "Creditos.csv";
    std::string nombre_backup = fecha.to_string_documento()+".csv";

    std::ifstream archivo_original(nombre_original);

    if (!archivo_original) {
        creado = false;
    }
    else{
        std::ofstream archivo_backup(nombre_backup);

        if (!archivo_backup) {
            creado = false;
        }
        else{
            archivo_backup<<archivo_original.rdbuf();
            creado = true;
        }

        archivo_backup.close();
    }
    archivo_original.close();
    return creado;
}

bool restaurar_backup(const std::string& nombre_backup){
    bool restaurado;
    std::string nombre_original = "Creditos.csv";
    std::ifstream archivo_backup(nombre_backup);

    if (!archivo_backup) {
        restaurado = false;
    }
    else{
        std::ofstream archivo_original(nombre_original);

        if (!archivo_original) {
            restaurado = false;
        }
        else{
            archivo_original<<archivo_backup.rdbuf();
            restaurado = true;
        }

        archivo_original.close();
    }
    archivo_backup.close();
    return restaurado;
}

bool esta_vacio(const std::string& nombre_archivo) {
    std::ifstream archivo(nombre_archivo);

    if (archivo.is_open() && archivo.peek() == std::ifstream::traits_type::eof()){
        return true;
    } else {
        return false;
    }
}

int contar_lineas(const std::string& nombre_archivo) {
    int contador = 0;
    std::ifstream archivo(nombre_archivo);

    if (!archivo.is_open()) {
        contador = -1;
    }
    else{
        std::string linea;
        while (std::getline(archivo, linea)) {
            contador++;
        }
    }

    archivo.close();
    return contador;
}

#endif // GESTORARCHIVOS_H_INCLUDED
