#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include <iostream>
#include <conio.h>
#include <windows.h>

#include "GestorArchivos.h"
#include "validaciones.h"
#include "Fecha.h"
#include "Credito.h"
#include "TablaAmortizacion.h"

void visibilidad_cursor(bool);
void mover_cursor(int x, int y);
void ingresar_datos_credito();
void consultar_cuota();
void elegir_backup();

void mover_cursor(int x, int y){
    HANDLE manejo_consola = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(manejo_consola, pos);
}

void visibilidad_cursor(bool visible) {
    HANDLE manejo_consola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = visible;
    SetConsoleCursorInfo(manejo_consola, &info);
}

int desplegar_menu(const char** opciones, int nopciones){
    const short int ANCHO_BOTON = 35;
    visibilidad_cursor(false);
    char tecla;
    HANDLE manejo_consola = GetStdHandle(STD_OUTPUT_HANDLE);
    short int cursor_x = 0, cursor_y = 1, color_act = 0, opcion = 1;
    int colores[2] = {15, 191};

    auto imprimir_opciones = [&](){
        auto imprimir_boton = [&ANCHO_BOTON](const char* opcion){
            short int caracteres_en_opcion = 0;
            while (opcion[caracteres_en_opcion] != '\0') {
                caracteres_en_opcion++;
            }
            int espacios_faltantes = ANCHO_BOTON - caracteres_en_opcion;

            for(short int i = 0; i<ANCHO_BOTON; i++){
                printf("%c",' ');
            }
            printf("\n");

            for(short int i = 0; i<espacios_faltantes/2; i++){
                printf("%c",' ');
            }
            printf("%s", opcion);
            if(espacios_faltantes%2 == 0){
                for(short int i = 0; i<espacios_faltantes/2; i++){
                    printf("%c",' ');
                }
            }else{
                for(short int i = 0; i<(espacios_faltantes/2)+1; i++){
                    printf("%c",' ');
                }
            }

            printf("\n");
            for(short int i = 0; i<ANCHO_BOTON; i++){
                printf("%c",' ');
            }
        };

        for (int i = 0; i<nopciones; i++){
            color_act = 0;

            if((i*3)+1 == cursor_y)color_act = 1;

            mover_cursor(cursor_x, (i*3));
            SetConsoleTextAttribute(manejo_consola, colores[color_act]);
            imprimir_boton(opciones[i]);
        }
        color_act = 0;
        SetConsoleTextAttribute(manejo_consola, colores[color_act]);
    };

    imprimir_opciones();

    while((tecla = getch()) != 13){

        //mover pos cursor arriba
        if(tecla == 72 && opcion>1)cursor_y = cursor_y-3, imprimir_opciones();
        //mover pos cursor abajo
        else if(tecla == 80 && opcion<nopciones)cursor_y = cursor_y + 3, imprimir_opciones();

        mover_cursor(cursor_x, cursor_y);
        opcion = ((cursor_y-1)/3)+1;
    }

    return opcion;
}

void desplegar_menu_principal(){
    const int NUM_OPCIONES = 7;
    const char* OPCIONES[NUM_OPCIONES] = {"Generar credito y tabla","Consultar credito","Hacer Backup","Restaurar Backup","Ayuda","Ver imagen del grupo de devs", "Salir"};

    int opcion;
    do{
        system("cls");
        opcion = desplegar_menu(OPCIONES, NUM_OPCIONES);
        if(opcion == 1)
            ingresar_datos_credito();
        else if(opcion == 2)
            consultar_cuota();
        else if(opcion == 3){
            Fecha fecha;
            crear_backup(fecha);
        }
        else if(opcion == 4)
            elegir_backup();
        else if(opcion == 5);
        else if(opcion == 6);

        visibilidad_cursor(false);
    }while(opcion != NUM_OPCIONES);

    mover_cursor(0,(opcion*3)+1);
}

void elegir_backup(){
    system("cls");
    int cursorx = 0, cursory = 0;
    int anuario;
    int mes;
    int dia;
    int hora;
    int minutos;
    int segundos;
    visibilidad_cursor(true);


    do{
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        anuario = ingresar_enteros("Ingrese el anuario del backup que desea restaurar");

        if(anuario<1900 || anuario > 2500){
            mover_cursor(cursorx, cursory+3);
            printf("El anuario debe ser mayor a 1900 y menor a 2500");
        }else{
            mover_cursor(cursorx, cursory+3);
            printf("                                                                ");
        }
    }while(anuario<1900 || anuario>2500);
    cursory = cursory + 2;

    do{
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        mes = ingresar_enteros("Ingrese el mes del backup que desea restaurar");

        if(mes < 1 || mes > 12){
            mover_cursor(cursorx, cursory+3);
            printf("El mes debe estar entre 1 y 12");
        }else{
            mover_cursor(cursorx, cursory+3);
            printf("                                                           ");
        }
    }while(mes<1 || mes>12);
    cursory = cursory + 2;

    do{
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        dia = ingresar_enteros("Ingrese el dia del backup que desea restaurar");

        if(dia>28){
            if(((mes==2 && ((anuario%4!=0)||dia>29))) || ((((mes < 8) && mes%2!=0)||(mes >= 8) && mes%2==0) && dia > 31) ||
                ((((mes < 8) && mes%2==0)||(mes >= 8) && mes%2!=0) && dia > 30)){
                    mover_cursor(cursorx, cursory+3);
                    printf("El dia es invalido para el mes y a�o ingresados");
            }
            else{
                mover_cursor(cursorx, cursory+3);
                printf("                                                             ");
            }
        }

    }while(mes<1 || mes>12);
    cursory = cursory + 2;

    do{
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        hora = ingresar_enteros("Ingrese la hora del backup que desea restaurar");

        if(hora < 0 || hora > 23){
            mover_cursor(cursorx, cursory+3);
            printf("La hora debe estar entre 0 y 23");
        }else{
            mover_cursor(cursorx, cursory+3);
            printf("                                                                ");
        }
    }while(hora < 0 || hora > 23);
    cursory = cursory + 2;

    do{
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        minutos = ingresar_enteros("Ingrese los minutos del backup que desea restaurar");

        if(minutos < 0 || minutos > 59){
            mover_cursor(cursorx, cursory+3);
            printf("Los minutos debe estar entre 0 y 59");
        }else{
            mover_cursor(cursorx, cursory+3);
            printf("                                                               ");
        }
    }while(minutos < 0 || minutos > 59);
    cursory = cursory + 2;

    do{
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        segundos = ingresar_enteros("Ingrese los segundos del backup que desea restaurar");

        if(segundos < 0 || segundos > 59){
            mover_cursor(cursorx, cursory+3);
            printf("Los segundos debe estar entre 0 y 59");
        }else{
            mover_cursor(cursorx, cursory+3);
            printf("                                                             ");
        }
    }while(segundos < 0 || segundos > 59);
    cursory = cursory + 2;

    Fecha fecha_backup(anuario, mes, dia, hora, minutos, segundos);

    if(!restaurar_backup(fecha_backup.to_string_documento()+".csv")){
        printf("\nNo se pudo restaurar el backup descrito, asegurese de escribir correctamente la informacion");
    }else{
        printf("Se restauro exitosamente el backup descrito\n");
    }
    system("pause");
}

void ingresar_datos_credito(){
    system("cls");
    Fecha sacado;
    double monto = 0 , tasa_interes = 0;
    int cursorx = 0, cursory = 0;
    int ncuotas = 0;

    visibilidad_cursor(true);

    while(monto<=0 || monto > 9999999.99){
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        cursory = 0;
        mover_cursor(cursorx, cursory);
        monto = ingresar_reales("Ingrese el monto del credito");

        if(monto<=0 || monto > 99999999.99){
            mover_cursor(cursorx, cursory+3);
            printf("El monto debe ser mayor a 0 y menor a 10M");
        }else{
            mover_cursor(cursorx, cursory+3);
            printf("                                                           ");
        }
    }

    cursory = cursory + 2;
    while(ncuotas<=0 || ncuotas > 500){
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        ncuotas = ingresar_enteros("Ingrese el numero de cuotas a pagar del credito");

        if(ncuotas<=0 || ncuotas > 500){
            mover_cursor(cursorx, cursory+3);
            printf("El numero de cuotas debe ser mayor a 0 y menor a 500");
        }else{
            mover_cursor(cursorx, cursory+3);
            printf("                                                           ");
        }
    }
    cursory = cursory + 2;
    while(tasa_interes<=0 || tasa_interes>99.99){
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        tasa_interes = ingresar_reales("Ingrese la tasa de interes del credito");

        if(tasa_interes<=0 || tasa_interes>99.99){
            mover_cursor(cursorx, cursory+3);
            printf("La tasa de interes debe ser mayor a 0 y menor a 100%");
        }else{
            mover_cursor(cursorx, cursory+3);
            printf("                                                           ");
        }
    }

    mover_cursor(cursorx, cursory+1);
    visibilidad_cursor(false);

    Credito credito(ncuotas, monto, sacado, tasa_interes);
    TablaAmortizacion tabla(credito);
    printf("\n");
    tabla.imprimir();

    if(!guardar_credito(credito)){
        printf("No se ha podido guardar la informacion del credito en el archivo");
    }

    system("pause");
}

void consultar_cuota(){
    system("cls");
    int id_credito;
    Credito credito_consult;

    visibilidad_cursor(true);
    id_credito = ingresar_enteros("Ingrese el numero del credito");

    if(existe_credito(id_credito)){
        credito_consult = obtener_credito(id_credito);
        TablaAmortizacion tabla(credito_consult);
        printf("\n");
        tabla.imprimir();
    }else{
        printf("No existe el credito solicitado");
    }


    system("pause");
}




#endif // MENUS_H_INCLUDED
