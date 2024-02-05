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
#include "arbolBinario.cpp"

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

TablaHash<Credito*>* cargar_creditos_al_hash(int tam, TablaHash<Cuenta*>* cuentas)
{
   TablaHash<Credito*>* creditos = new TablaHash<Credito*>(tam);

    std::string ruta;
    std::string ruta_inicial;
    std::string nombreCarpeta = "Informacion";
    char tmp[256];

    getcwd(tmp, 256);
    ruta_inicial = std::string(tmp);

    if (_chdir(nombreCarpeta.c_str()) != 0)
    {
        return creditos;
    }

    getcwd(tmp, 256);
    ruta = std::string(tmp);

    std::string nombre_original = ruta + "//" + "Creditos.csv";

    std::ifstream archivo_original(nombre_original);
    std::string linea;

    Cuenta* cuenta;
    Credito* credito;

    //obtener primera linea
    std::getline(archivo_original, linea);

    while (std::getline(archivo_original, linea))
    {
        std::istringstream ss(linea);

        std::string num_cuenta;
        std::string monto;
        std::string ncuotas;
        std::string interes;
        std::string sfecha;

        std::getline(ss, num_cuenta, ',');
        std::getline(ss, monto, ',');
        std::getline(ss, ncuotas, ',');
        std::getline(ss, interes, ',');
        std::getline(ss, sfecha, ',');

        cuenta = cuentas->buscar(std::stoi(num_cuenta))->get_valor();
        Fecha fecha;
        fecha.string_to_fecha(sfecha);
        credito = new Credito(std::stoi(ncuotas),std::stof(monto),fecha, std::stof(interes), cuenta);
        creditos->insertar(credito, cuenta->get_num_cuenta());
    }

    archivo_original.close();
    _chdir(ruta_inicial.c_str());

    return creditos;
}

bool guardar_credito(Credito credito)
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

    std::string nombre_original = ruta + "//" + "Creditos.csv";
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
            archivo_original<<"No. de Cuenta,Monto,No. Cuotas,Tasa Interes,Fecha obtenido\n";
        }

        archivo_original<<credito.get_cuenta()->get_num_cuenta()<<","<<credito.get_monto()<<","<<credito.get_n_cuotas_pagar()<<","<<credito.get_tasa_interes()<<","<<credito.get_fecha_realizado().to_string()<<"\n";
    }

    archivo_original.close();
    _chdir(ruta_inicial.c_str());

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

void cargar_cuentas_al_arbol(TablaHash<Persona*>* personas, ArbolBinario<Cuenta*>* arbol_ID)
{
    std::string ruta;
    std::string ruta_inicial;
    std::string nombreCarpeta = "Informacion";
    char tmp[256];

    getcwd(tmp, 256);
    ruta_inicial = std::string(tmp);

    if (_chdir(nombreCarpeta.c_str()) != 0)
    {
        return;
    }

    getcwd(tmp, 256);
    ruta = std::string(tmp);

    std::string nombre_original = ruta + "//" + "Cuentas.csv";

    std::ifstream archivo_original(nombre_original);
    std::string linea;

    Persona* persona;
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
        Cliente* cliente = new Cliente(persona, id);
        num_cuenta = std::stoi(snocuenta);
        cuenta = new Cuenta(cliente, num_cuenta, std::stof(ssaldo));

        arbol_ID->insertar(cuenta, 1);
    }

    archivo_original.close();
    _chdir(ruta_inicial.c_str());

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
    std::string nombre_temporal = ruta + "//" + "Cuentas_temp.csv";

    std::fstream archivo_original(nombre_original, std::ios::in);
    std::ofstream archivo_temporal(nombre_temporal);

    if (!archivo_original || !archivo_temporal) {
        _chdir(ruta_inicial.c_str());
        return false;
    } else {
        if (!esta_vacio(nombre_original)) {
            int num_cuenta = cuenta.get_num_cuenta();
            std::string linea;
            std::string snocuenta;

            std::getline(archivo_original, linea);  // Leer la cabecera
            archivo_temporal << linea << "\n";  // Escribir la cabecera en el nuevo archivo

            while (std::getline(archivo_original, linea)) {
                std::istringstream ss(linea);
                std::getline(ss, snocuenta, ',');

                if (num_cuenta == std::stoi(snocuenta)) {
                    // Escribir la nueva línea en el nuevo archivo
                    archivo_temporal << cuenta.get_num_cuenta() << "," << cuenta.get_saldo() << ","
                        << cuenta.get_cliente()->get_id() << "," << cuenta.get_cliente()->get_persona()->get_cedula() << ","
                        << cuenta.get_cliente()->get_persona()->get_nombre() << "," << cuenta.get_cliente()->get_persona()->get_apellido() << "\n";
                } else {
                    // Conservar la línea original
                    archivo_temporal << linea << "\n";
                }
            }
        }

        archivo_original.close();
        archivo_temporal.close();

        std::remove(nombre_original.c_str());

        if (std::rename(nombre_temporal.c_str(), nombre_original.c_str()) == 0) {
            _chdir(ruta_inicial.c_str());
            return true;
        } else {
            _chdir(ruta_inicial.c_str());
            return false;
        }
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

bool crear_backup(Fecha fecha, const std::string& nombre_original)
{
    bool creado;
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
