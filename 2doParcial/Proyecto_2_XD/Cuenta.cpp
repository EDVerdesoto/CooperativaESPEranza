/***********************************************************************
 UFA - ESPE
 * Module:  Cuenta.cpp
 * Author:  Edison Verdesoto, Joan Cobeña
 * Modified: viernes, 2 de febrero de 2024 19:24:07
 * Purpose: Implementation of the class Cuenta
 ***********************************************************************/

#include <iostream>
#include "Movimientos.h"
#include "Cuenta.h"
#include "Cliente.h"
#include <math.h>
#include <string>

/**
 * @brief Constructor predeterminado de Cuenta
 */
Cuenta::Cuenta(){

}

/**
 * @brief Constructor de Cuenta que inicializa la cuenta con un cliente y genera un número de cuenta
 * @param _cliente Cliente asociado a la cuenta
 */
Cuenta::Cuenta(Cliente* _cliente){
    cliente = _cliente;
    num_cuenta = generar_ID_cuenta();
    saldo = 0.0;
}

/**
 * @brief Constructor de Cuenta que inicializa la cuenta con un cliente, un número de cuenta y un saldo
 * @param _cliente Cliente asociado a la cuenta
 * @param _num_cuenta Número de cuenta
 * @param _saldo Saldo inicial de la cuenta
 */
Cuenta::Cuenta(Cliente* _cliente, int _num_cuenta, double _saldo){
    cliente = _cliente;
    num_cuenta = _num_cuenta;
    saldo = _saldo;
}

/**
 * @brief Obtiene el cliente asociado a la cuenta
 * @return Cliente asociado a la cuenta
 */
Cliente* Cuenta::get_cliente(){
    return cliente;
}

/**
 * @brief Obtiene el número de cuenta
 * @return Número de cuenta
 */
int Cuenta::get_num_cuenta(){
    return num_cuenta;
}

/**
 * @brief Obtiene el saldo de la cuenta
 * @return Saldo de la cuenta
 */
double Cuenta::get_saldo(){
    return saldo;
}

/**
 * @brief Establece el saldo de la cuenta
 * @param nuevo_saldo Nuevo saldo de la cuenta
 */
void Cuenta::set_saldo(double nuevo_saldo){
    saldo = nuevo_saldo;
}

/**
 * @brief Función auxiliar para cifrar un número sumando sus dígitos
 * @param numero Número a cifrar
 * @param cifra Variable acumuladora para el cifrado
 * @return Número cifrado
 */
int cifrar_numero(int numero, int cifra){
    if(numero>=10){
        cifra = cifra + (numero % 10);
        cifrar_numero(numero/10 , cifra);
    }
    else{
        cifra = cifra + numero;
        if(cifra>=10){
            cifra = cifrar_numero(cifra, 0);

        }
        return cifra;
    }
}

/**
 * @brief Función auxiliar para calcular el dígito de verificación de un número
 * @param digitos_anteriores Número al que se le calculará el dígito de verificación
 * @return Dígito de verificación calculado
 */
int verificador(int digitos_anteriores){
    int longitud = (int) log(digitos_anteriores);
    int digito, verificador = 0;
    for(int i = 0; i<longitud; i++){
        digito = digitos_anteriores / (int) pow(10,longitud-i);
        verificador += (i%2==0)? digito*2: digito;
    }

    int decena_prox = verificador/10;

    if(verificador % 10 != 0)decena_prox += 1;
    decena_prox *= 10;
    verificador = decena_prox - verificador;

    return verificador;
}

/**
 * @brief Genera un número de cuenta único basado en la información del cliente
 * @return Número de cuenta generado
 */
int Cuenta::generar_ID_cuenta(){
    int primeros_digitos;
    Persona* persona = cliente->get_persona();
    primeros_digitos = persona->get_nombre().at(0) - persona->get_apellido().at(0);
    if(primeros_digitos<0)primeros_digitos*=-1;
    primeros_digitos += 1;

    if (primeros_digitos >= 10){
        primeros_digitos = cifrar_numero(primeros_digitos, 0);
    }

    int numero_cuentas = std::stoi(cliente->get_id());

    num_cuenta = primeros_digitos*pow(10,6) + numero_cuentas;
    num_cuenta = num_cuenta*10 + verificador(num_cuenta);
    return num_cuenta;
}

/**
 * @brief Imprime la información de la cuenta en la consola
 */
void Cuenta::imprimir(){
    std::cout<<"No. de cuenta: "<<num_cuenta<<std::endl;
    std::cout<<"Propietario de la cuenta: "<<std::endl;
    std::cout<<"ID_cliente: "<<cliente->get_id()<<std::endl;
    std::cout<<"Nombre: "<<cliente->get_persona()->get_nombre()<<std::endl;
    std::cout<<"Apellido: "<<cliente->get_persona()->get_apellido()<<std::endl;
    std::cout<<"Cedula: "<<cliente->get_persona()->get_cedula()<<std::endl;
}
/**
 * @brief getter general de la claes
 * @param dato controlador
 * @return dependiendo del valor del dato, retorna un valor diferente
 */
std::string Cuenta::getter_general(int dato) {
    if (dato == 1) {
        return cliente->get_id();
    }
    else if (dato == 2) {
        std::string str_num_cuenta = std::to_string(num_cuenta);
        return str_num_cuenta;
    }
    else if (dato == 3) {
        return cliente->get_persona()->get_nombre();
    }
    else if (dato == 4) {
        imprimir();
    }
    else if (dato == 5) {
        return cliente->get_persona()->get_apellido();
    }
    else if (dato == 6) {
        return cliente->get_persona()->get_cedula();
    }
}


