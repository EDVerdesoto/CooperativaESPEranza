/***********************************************************************
 * Module:  validaciones.h
 * Author:  Edison Verdesoto
 * Modified: viernes, 20 de noviembre de 2023 11:05:38 a. m.
 * Purpose: Declaration of the class validaciones
 ***********************************************************************/

#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <cctype>

int ingresar_enteros(const char* msj);
int borrar(char* datos, int& i);
float ingresar_reales(const char* msj);
std::string ingresar_alfabetico(const char* msj);

bool esEspecial(char tecla){
	return(tecla == 'c' || tecla == 's' ||tecla == 'r'  || tecla == 't');
}

bool esParentesis(char tecla){
	return (tecla == '('|| tecla == ')');
}

bool esOperador(char tecla){
	return (tecla == '+' || tecla == '-' || tecla == '*' || tecla == '/'|| tecla == '^');
}

int ingresar_enteros(const char* msj) {
    char* datos = new char[10];
    char c;
    int i = 0;

    printf("%s", msj);
    printf("\n");

    while ((c = _getch()) != 13 && i < 9) {
        if ((c >= '0' && c <= '9')|| c == 8) {
            if(c == 8){
                i = borrar(datos,i);
            }else{
                printf("%c", c);
                datos[i++] = c;
            }

        }
    }
    datos[i] = '\0';
    return atoi(datos);
}

float ingresar_reales(const char* msj) {
    char* datos = new char[12];
    char c;
    int i = 0;
    bool hay_punto = false;
    int posicion_punto;

    printf("%s", msj);
    printf("\n");

    while ((c = _getch()) != 13 && i < 11) {
        if ((c >= '0' && c <= '9') || (c == '.' && !hay_punto)|| c == 8 || c == '-') {
            if(!((c == '.')&& i == 0)){
                if(!((c == '-') && i != 0)){
                    if (c == 8) {
                        i = borrar(datos, i);
                        if((i+1) == posicion_punto){
                            hay_punto = false;
                        }
                    }
                    else {
                        printf("%c", c);
                        datos[i++] = c;

                        if (c == '.') {
                            posicion_punto = i;
                            hay_punto = true;
                        }
                    }
                }
            }
        }
    }
    datos[i] = '\0';
    return atof(datos);
}

std::string ingresar_alfabetico(const char* msj) {
    char datos[21];
    char c;
    int i = 0;

    printf("%s", msj);
    printf("\n");

    while ((c = _getch()) != 13 && i < 20) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')|| c == 32||c == 8) {
            if (c == 8) {
                i = borrar(datos, i);
            } else {
                printf("%c", c);
                datos[i++] = c;
            }
        }
    }
    datos[i] = '\0';
    return std::string(datos);
}


int borrar(char* datos, int& i) {
    if (i > 0) {
        printf("\b \b");
        i--;
        datos[i] = '\0';
        return i;
    }
    return 0;
}

std::string ingresarExpresion() {
    char *entrada = new char[10000];
    char tecla;
    int i = 0;
    int parentesisApertura = 0;
    int parentesisCierre = 0;
	bool eliminarEspeciales = false;
	int caracteresEliminar= 0;
	char elementoAnterior = '\0';
	bool huboPunto = false;
	bool hayPunto = false;
    while (true) {
        tecla = _getch();
        elementoAnterior = (i > 0) ? entrada[i - 1] : '\0';
		if (tecla == '\r' && i > 0 && !esOperador(elementoAnterior) && elementoAnterior !='.') {
            if (parentesisApertura == parentesisCierre){
            	break;
			}
        }else if (tecla == '\b' && i > 0) {
		      if (elementoAnterior == 'i' || (elementoAnterior == '(' && (entrada[i - 2] == 's' ||
			                                  entrada[i - 2] == 'n' || entrada[i - 2] == 'z'))) {
		        caracteresEliminar = 4;
				if(elementoAnterior == 'i'){
		        	caracteresEliminar = 2;
		    	}else if(entrada[i - 2] == 'z'){
		    		caracteresEliminar = 5;
				}
				eliminarEspeciales = true;
		    } else if (esParentesis(elementoAnterior)) {
		        std::cout << "\b \b";
			    entrada[i] = 0;
			    i--;
			    parentesisCierre -= (elementoAnterior == ')');
			    parentesisApertura -= (elementoAnterior == '(');
		    }
				else if (elementoAnterior == '.'){
				std::cout << "\b \b";
		        i--;
		        entrada[i] = 0;
				hayPunto = false;
		    }
                else if (esOperador(elementoAnterior)){
		    	std::cout << "\b \b";
		        i--;
		        entrada[i] = 0;
				hayPunto = huboPunto;
			}else {
		        std::cout << "\b \b";
		        i--;
		        entrada[i] = 0;
		    }
		    if (eliminarEspeciales){
		        for (int j = 1; j<=caracteresEliminar; j++){
		        	std::cout << "\b \b";
		        	elementoAnterior = 0;
		        	i--;
				}
				if(caracteresEliminar > 2){
					parentesisApertura--;
				}
				eliminarEspeciales = false;
			}
        } else if (isalpha(tecla) && elementoAnterior !='.' && (esOperador(elementoAnterior) || elementoAnterior == '('|| i == 0)) {
			if (esEspecial(tecla)){
			    const char* texto = "";
			    switch (tecla) {
			        case 'c':
			            entrada[i++] = 'c';
			            entrada[i++] = 'o';
			            entrada[i++] = 's';
			            texto = "os(";
			            break;
			        case 's':
			            entrada[i++] = 's';
			            entrada[i++] = 'i';
			            entrada[i++] = 'n';
			            texto = "in(";
			            break;
			        case 't':
			            entrada[i++] = 't';
			            entrada[i++] = 'a';
			            entrada[i++] = 'n';
			            texto = "an(";
			            break;
			        case 'r':
			            entrada[i++] = 'r';
			            entrada[i++] = 'a';
			            entrada[i++] = 'i';
			            entrada[i++] = 'z';
			            texto = "aiz(";
			            break;
			    	}
		        entrada[i++] = '(';
			    parentesisApertura++;
			    std::cout << tecla << texto;
			}else if ((tecla == 'p')){
			    entrada[i++] = tecla;
			    entrada[i++] = 'i';
			    std::cout << tecla << "i";
			}
        }else if(esParentesis(tecla)){
        	if (tecla == '(' && elementoAnterior !='.' && (esOperador(elementoAnterior) || elementoAnterior == '(' || i == 0)) {
			    parentesisApertura++;
			    entrada[i++] = tecla;
				std::cout << tecla;
			} else if (tecla == ')' && elementoAnterior !='.' && elementoAnterior != '(' && !esOperador(elementoAnterior) && (isdigit(elementoAnterior) || elementoAnterior == ')'|| elementoAnterior == 'i')) {
			    parentesisCierre++;
				if(parentesisApertura>0 && parentesisCierre <= parentesisApertura){
				    entrada[i++] = tecla;
					std::cout << tecla;
				}else{
					parentesisCierre--;
				}
			}
		} else if (isdigit(tecla) && elementoAnterior!= 'i' && (esOperador(elementoAnterior)||
		                       elementoAnterior == '(' || isdigit(elementoAnterior) || i == 0 || elementoAnterior =='.')){
			int k = 1;
			while(isdigit(entrada[i-k])){
				k++;
			}
			if(k<7){
				entrada[i++] = tecla;
				std::cout << tecla;
			}
		} else if(esOperador(tecla) && elementoAnterior !='.' && !esOperador(elementoAnterior) && tecla != '-' && elementoAnterior!='(' && i>0){
			entrada[i++] = tecla;
			std::cout << tecla;
			huboPunto = hayPunto;
			hayPunto = false;
		} else if(tecla == '-' && !esOperador(elementoAnterior) && elementoAnterior !='.'){
			entrada[i++] = tecla;
			std::cout << tecla;
			hayPunto = false;
		} else if(tecla =='.' && isdigit(elementoAnterior)){
			if(!hayPunto){
				entrada[i++] = tecla;
				std::cout << tecla;
				hayPunto = true;
			}

		}
    }
    entrada[i] = '\0';
	return entrada;
}

std::string ingresar_string() {
    char *entrada = new char[21];
    char tecla;
    int i = 0;


    while (true){
        tecla = _getch();

        if (tecla == '\r' && i > 0) {
            break;
        }

        else if (tecla == '\b' && i > 0) {
            std::cout << "\b \b";
            i--;
            entrada[i] = 0;
        }
        else if (isalpha(tecla)) {
            if (i == 0) {
                char tecla_M = toupper(tecla);
                entrada[i++] = tecla_M;
                std::cout << tecla_M;
            }
            else if (std::isupper(tecla)) {
                char tecla_m = tolower(tecla);
                entrada[i++] = tecla_m;
                std::cout << tecla_m;
            }
            else if (std::islower(tecla)) {
                entrada[i++] = tecla;
                std::cout << tecla;
            }
        }
    }
    entrada[i] = '\0';
	return entrada;
}
#endif // VALIDACIONES_H_INCLUDED
