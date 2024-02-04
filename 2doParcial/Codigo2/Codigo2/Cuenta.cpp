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

Cuenta::Cuenta(){

}

Cuenta::Cuenta(Cliente* _cliente){
    cliente = _cliente;
}

Cliente* Cuenta::get_cliente(){
    return cliente;
}

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

void Cuenta::generar_ID_cuenta(){
    int primeros_digitos;
    Persona* persona = cliente->get_persona();
    primeros_digitos = persona->get_nombre().at(0) - persona->get_apellido().at(0);
    if(primeros_digitos<0)primeros_digitos*=-1;
    primeros_digitos += 1;

    if (primeros_digitos >= 10){
        primeros_digitos = cifrar_numero(primeros_digitos, 0);
    }

    int numero_cuentas = 2;

    num_cuenta = primeros_digitos*pow(10,6) + numero_cuentas;
    num_cuenta = num_cuenta*10 + verificador(num_cuenta);
    std::cout<<num_cuenta;
}
