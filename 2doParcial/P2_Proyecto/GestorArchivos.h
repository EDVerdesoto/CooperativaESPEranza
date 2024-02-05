#ifndef GESTORARCHIVOS_H_INCLUDED
#define GESTORARCHIVOS_H_INCLUDED

#include <iostream>
#include <fstream>

#include <string>
#include "Credito.h"
#include "Fecha.h"
#include "Persona.h"
#include "TablaHash.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

int contar_lineas(const std::string& nombre_archivo);
bool esta_vacio(const std::string& nombre_archivo);
bool crear_backup(Fecha fecha);

bool existe_credito(int num_credito)
{
    std::string nombre_original = "Creditos.csv";
    if(num_credito>=contar_lineas(nombre_original))
    {
        return false;
    }
    else
    {
        return true;
    }
}

Credito obtener_credito(int num_credito)
{
    std::string nombre_original = "Creditos.csv";
    std::ifstream archivo_original(nombre_original);
    std::string linea;
    int contador = 0;
    while (std::getline(archivo_original, linea)&&(contador<num_credito))
    {
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

bool guardar_credito(Credito credito)
{
    int num_credito;

    std::string nombre_original = "Creditos.csv";
    std::ofstream archivo_original(nombre_original, std::ios::app);

    if(!archivo_original)
    {
        return false;
    }
    else
    {
        if(esta_vacio(nombre_original))
        {
            archivo_original<<"ID,Monto,No. Cuotas,Tasa Interes,Fecha obtenido\n";
            num_credito = contar_lineas(nombre_original)+1;
        }
        else
        {
            num_credito = contar_lineas(nombre_original);
        }
        archivo_original<<num_credito<<","<<credito.get_monto()<<","<<credito.get_n_cuotas_pagar()<<","<<credito.get_tasa_interes()<<","<<credito.get_fecha_realizado().to_string()<<"\n";
    }

    archivo_original.close();
    Fecha fecha;
    crear_backup(fecha);
    return true;
}

TablaHash<Persona*>* cargar_personas_al_hash(int tam)
{
    TablaHash<Persona*>* personas = new TablaHash<Persona*>(tam);

    std::string ruta;
    std::string ruta_inicial;
    std::string nombreCarpeta = "Informacion";
    char tmp[256];

    getcwd(tmp, 256);
    ruta_inicial = std::string(tmp);

    if (_chdir(nombreCarpeta.c_str()) != 0)
    {
        return personas;
    }

    getcwd(tmp, 256);
    ruta = std::string(tmp);

    std::string nombre_original = ruta + "//" + "Personas.csv";

    std::ifstream archivo_original(nombre_original);
    std::string linea;


    Persona* persona;

    //obtener primera linea
    std::getline(archivo_original, linea);

    while (std::getline(archivo_original, linea))
    {
        std::istringstream ss(linea);

        std::string cedula;
        std::string nombre;
        std::string apellido;

        std::getline(ss, cedula, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, apellido, ',');

        persona = new Persona(nombre,apellido,cedula);

        personas->insertar(persona, cedula);

    }

    archivo_original.close();
    _chdir(ruta_inicial.c_str());

    return personas;

}

TablaHash<Cuenta*>* cargar_cuentas_al_hash(int tam, TablaHash<Persona*>* personas, TablaHash<Cuenta*>* cuentas_cedulas)
{

    TablaHash<Cuenta*>* cuentas = new TablaHash<Cuenta*>(tam);

    std::string ruta;
    std::string ruta_inicial;
    std::string nombreCarpeta = "Informacion";
    char tmp[256];

    getcwd(tmp, 256);
    ruta_inicial = std::string(tmp);

    if (_chdir(nombreCarpeta.c_str()) != 0)
    {
        return cuentas;
    }

    getcwd(tmp, 256);
    ruta = std::string(tmp);

    std::string nombre_original = ruta + "//" + "Cuentas.csv";

    std::ifstream archivo_original(nombre_original);
    std::string linea;

    Persona* persona;
    Cliente* cliente;
    Cuenta* cuenta;
    int num_cuenta;

    //obtener primera linea
    std::getline(archivo_original, linea);

    while (std::getline(archivo_original, linea))
    {
        std::istringstream ss(linea);

        std::string snocuenta;
        std::string ssaldo;
        std::string id;
        std::string cedula;
        std::string nombre;
        std::string apellido;

        std::getline(ss, snocuenta, ',');
        std::getline(ss, ssaldo, ',');
        std::getline(ss, id, ',');
        std::getline(ss, cedula, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, apellido, ',');

        persona = personas->buscar_cedula_persona(cedula)->get_valor();
        cliente = new Cliente(persona, id);
        num_cuenta = std::stoi(snocuenta);
        cuenta = new Cuenta(cliente, num_cuenta, std::stof(ssaldo));

        cuentas->insertar(cuenta, num_cuenta);
        cuentas_cedulas->insertar(cuenta, cedula);

    }

    archivo_original.close();
    _chdir(ruta_inicial.c_str());

    return cuentas;
}

bool guardar_persona(Persona persona)
{

    std::string ruta;
    std::string ruta_inicial;
    std::string nombreCarpeta = "Informacion";
    char tmp[256];

    getcwd(tmp, 256);
    ruta_inicial = std::string(tmp);

    if(_mkdir(nombreCarpeta.c_str()) != 0)
    {
        if (_chdir(nombreCarpeta.c_str()) != 0)
        {
            return false;
        }
    }
    else
    {
        _chdir(nombreCarpeta.c_str());
    }

    getcwd(tmp, 256);
    ruta = std::string(tmp);

    std::string nombre_original = ruta + "//" + "Personas.csv";
    std::ofstream archivo_original(nombre_original, std::ios::app);

    if(!archivo_original)
    {
        return false;
    }
    else
    {
        if(esta_vacio(nombre_original))
        {
            archivo_original<<"Cedula,Nombre,Apellido\n";
        }

        archivo_original<<persona.get_cedula()<<","<<persona.get_nombre()<<","<<persona.get_apellido()<<"\n";
    }

    archivo_original.close();
    _chdir(ruta_inicial.c_str());


    return true;

}

bool actualizar_cuenta(Cuenta cuenta)
{
    std::string ruta;
    std::string ruta_inicial;
    std::string nombreCarpeta = "Informacion";
    char tmp[256];

    getcwd(tmp, 256);
    ruta_inicial = std::string(tmp);

    if(_mkdir(nombreCarpeta.c_str()) != 0)
    {
        if (_chdir(nombreCarpeta.c_str()) != 0)
        {
            return false;
        }
    }
    else
    {
        _chdir(nombreCarpeta.c_str());
    }

    getcwd(tmp, 256);
    ruta = std::string(tmp);

    std::string nombre_original = ruta + "//" + "Cuentas.csv";
    std::fstream archivo_original(nombre_original, std::ios::in | std::ios::out);

    if(!archivo_original)
    {
        _chdir(ruta_inicial.c_str());
        return false;
    }
    else
    {
        if(!esta_vacio(nombre_original))
        {
            int num_cuenta = cuenta.get_num_cuenta();
            std::string linea;
            std::string snocuenta;

            std::getline(archivo_original, linea);

            while (std::getline(archivo_original, linea))
            {
                std::istringstream ss(linea);
                std::getline(ss, snocuenta, ',');

                if (num_cuenta == std::stoi(snocuenta)) {
                    // Mover el puntero al inicio de la línea actual
                    archivo_original.seekp(archivo_original.tellg() - linea.length() - 2);

                    // Escribir la nueva línea
                    archivo_original<<cuenta.get_num_cuenta()<<","<<cuenta.get_saldo()<<","
                        <<cuenta.get_cliente()->get_id()<<","<<cuenta.get_cliente()->get_persona()->get_cedula()<<","
                        <<cuenta.get_cliente()->get_persona()->get_nombre()<<","<<cuenta.get_cliente()->get_persona()->get_apellido()<<"\n";
                    break;
                }
            }

        }

    archivo_original.close();
    _chdir(ruta_inicial.c_str());
    return true;

    }

}

bool guardar_cuenta(Cuenta cuenta)
{
    std::string ruta;
    std::string ruta_inicial;
    std::string nombreCarpeta = "Informacion";
    char tmp[256];

    getcwd(tmp, 256);
    ruta_inicial = std::string(tmp);

    if(_mkdir(nombreCarpeta.c_str()) != 0)
    {
        if (_chdir(nombreCarpeta.c_str()) != 0)
        {
            return false;
        }
    }
    else
    {
        _chdir(nombreCarpeta.c_str());
    }

    getcwd(tmp, 256);
    ruta = std::string(tmp);

    std::string nombre_original = ruta + "//" + "Cuentas.csv";
    std::ofstream archivo_original(nombre_original, std::ios::app);

    if(!archivo_original)
    {
        _chdir(ruta_inicial.c_str());
        return false;
    }
    else
    {
        if(esta_vacio(nombre_original))
        {
            archivo_original<<"No. de Cuenta,Saldo,ID,Cedula,Nombre,Apellido\n";
        }

        archivo_original<<cuenta.get_num_cuenta()<<","<<cuenta.get_saldo()<<","
                        <<cuenta.get_cliente()->get_id()<<","<<cuenta.get_cliente()->get_persona()->get_cedula()<<","
                        <<cuenta.get_cliente()->get_persona()->get_nombre()<<","<<cuenta.get_cliente()->get_persona()->get_apellido()<<"\n";
    }

    archivo_original.close();
    _chdir(ruta_inicial.c_str());


    return true;
}

bool crear_backup(Fecha fecha)
{
    bool creado;
    std::string nombre_original = "Creditos.csv";
    std::string nombre_backup = fecha.to_string_documento()+".csv";

    std::ifstream archivo_original(nombre_original);

    if (!archivo_original)
    {
        creado = false;
    }
    else
    {
        std::ofstream archivo_backup(nombre_backup);

        if (!archivo_backup)
        {
            creado = false;
        }
        else
        {
            archivo_backup<<archivo_original.rdbuf();
            creado = true;
        }

        archivo_backup.close();
    }
    archivo_original.close();
    return creado;
}

bool restaurar_backup(const std::string& nombre_backup)
{
    bool restaurado;
    std::string nombre_original = "Creditos.csv";
    std::ifstream archivo_backup(nombre_backup);

    if (!archivo_backup)
    {
        restaurado = false;
    }
    else
    {
        std::ofstream archivo_original(nombre_original);

        if (!archivo_original)
        {
            restaurado = false;
        }
        else
        {
            archivo_original<<archivo_backup.rdbuf();
            restaurado = true;
        }

        archivo_original.close();
    }
    archivo_backup.close();
    return restaurado;
}

bool esta_vacio(const std::string& nombre_archivo)
{
    std::ifstream archivo(nombre_archivo);

    if (archivo.is_open() && archivo.peek() == std::ifstream::traits_type::eof())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int contar_lineas(const std::string& nombre_archivo)
{
    int contador = 0;
    std::ifstream archivo(nombre_archivo);

    if (!archivo.is_open())
    {
        contador = -1;
    }
    else
    {
        std::string linea;
        while (std::getline(archivo, linea))
        {
            contador++;
        }
    }

    archivo.close();
    return contador;
}

#endif // GESTORARCHIVOS_H_INCLUDED
