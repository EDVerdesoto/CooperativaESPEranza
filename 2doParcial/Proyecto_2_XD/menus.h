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
#include "Imagen.h"
#include "Persona.h"
#include "ListaDoble.cpp"
#include "Nodo.cpp"
#include "TablaHash.h"
#include "Movimientos.h"
#include "Cuenta.h"
#include "arbolBinario.h"

void visibilidad_cursor(bool);
void mover_cursor(int x, int y);
void ingresar_datos_credito();
void consultar_cuota();
void elegir_backup();
void abrir_menu_ayuda();
void abrir_cuenta(TablaHash<Persona*>* personas, TablaHash<Cuenta*>* cuentas, TablaHash<Cuenta*>* cuentas_por_cedula, ArbolBinario<Cuenta*>* arbol_cuentas);
void ingresar_datos_usuario(TablaHash<Persona*>* personas);
void hacer_transacciones(TablaHash<Cuenta*>* cuentas, TablaHash<Cuenta*>* cuentas_por_cedula);
bool operator<(Fecha fecha1, Fecha fecha2);

void mover_cursor(int x, int y)
{
    HANDLE manejo_consola = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(manejo_consola, pos);
}

void visibilidad_cursor(bool visible)
{
    HANDLE manejo_consola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = visible;
    SetConsoleCursorInfo(manejo_consola, &info);
}

int desplegar_menu_movible(const char** opciones, int nopciones, int xinicial, int yinicial)
{
    const short int ANCHO_BOTON = 35;
    visibilidad_cursor(false);
    char tecla;
    HANDLE manejo_consola = GetStdHandle(STD_OUTPUT_HANDLE);
    short int cursor_x = xinicial, cursor_y = yinicial, color_act = 0, opcion = 1;
    int colores[2] = {15, 191};

    auto imprimir_opciones = [&]()
    {
        auto imprimir_boton = [&ANCHO_BOTON](const char* opcion)
        {
            short int caracteres_en_opcion = 0;
            while (opcion[caracteres_en_opcion] != '\0')
            {
                caracteres_en_opcion++;
            }
            int espacios_faltantes = ANCHO_BOTON - caracteres_en_opcion;

            for(short int i = 0; i<ANCHO_BOTON; i++)
            {
                printf("%c",' ');
            }
            printf("\n");

            for(short int i = 0; i<espacios_faltantes/2; i++)
            {
                printf("%c",' ');
            }
            printf("%s", opcion);
            if(espacios_faltantes%2 == 0)
            {
                for(short int i = 0; i<espacios_faltantes/2; i++)
                {
                    printf("%c",' ');
                }
            }
            else
            {
                for(short int i = 0; i<(espacios_faltantes/2)+1; i++)
                {
                    printf("%c",' ');
                }
            }

            printf("\n");
            for(short int i = 0; i<ANCHO_BOTON; i++)
            {
                printf("%c",' ');
            }
        };

        for (int i = 0; i<nopciones; i++)
        {
            color_act = 0;

            if(((i-1)*3)+yinicial == cursor_y)color_act = 1;

            mover_cursor(cursor_x, (i*3)+yinicial);
            SetConsoleTextAttribute(manejo_consola, colores[color_act]);
            imprimir_boton(opciones[i]);
        }
        color_act = 0;
        SetConsoleTextAttribute(manejo_consola, colores[color_act]);
    };

    imprimir_opciones();

    while((tecla = _getch()) != 13)
    {

        //mover pos cursor arriba
        if(tecla == 72 && opcion>1)cursor_y = cursor_y-3, imprimir_opciones();
        //mover pos cursor abajo
        else if(tecla == 80 && opcion<nopciones)cursor_y = cursor_y + 3, imprimir_opciones();

        mover_cursor(cursor_x, cursor_y);
        opcion = ((cursor_y-1)/3)+1;
    }

    return opcion;
}

int desplegar_menu(const char** opciones, int nopciones, int xinicial, int yinicial)
{
    const short int ANCHO_BOTON = 35;
    visibilidad_cursor(false);
    char tecla;
    HANDLE manejo_consola = GetStdHandle(STD_OUTPUT_HANDLE);
    short int cursor_x = xinicial, cursor_y = yinicial, color_act = 0, opcion = 1;
    int colores[2] = {15, 191};

    auto imprimir_opciones = [&]()
    {
        auto imprimir_boton = [&ANCHO_BOTON](const char* opcion)
        {
            short int caracteres_en_opcion = 0;
            while (opcion[caracteres_en_opcion] != '\0')
            {
                caracteres_en_opcion++;
            }
            int espacios_faltantes = ANCHO_BOTON - caracteres_en_opcion;

            for(short int i = 0; i<ANCHO_BOTON; i++)
            {
                printf("%c",' ');
            }
            printf("\n");

            for(short int i = 0; i<espacios_faltantes/2; i++)
            {
                printf("%c",' ');
            }
            printf("%s", opcion);
            if(espacios_faltantes%2 == 0)
            {
                for(short int i = 0; i<espacios_faltantes/2; i++)
                {
                    printf("%c",' ');
                }
            }
            else
            {
                for(short int i = 0; i<(espacios_faltantes/2)+1; i++)
                {
                    printf("%c",' ');
                }
            }

            printf("\n");
            for(short int i = 0; i<ANCHO_BOTON; i++)
            {
                printf("%c",' ');
            }
        };

        for (int i = 0; i<nopciones; i++)
        {
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

    while((tecla = _getch()) != 13)
    {

        //mover pos cursor arriba
        if(tecla == 72 && opcion>1)cursor_y = cursor_y-3, imprimir_opciones();
        //mover pos cursor abajo
        else if(tecla == 80 && opcion<nopciones)cursor_y = cursor_y + 3, imprimir_opciones();

        mover_cursor(cursor_x, cursor_y);
        opcion = ((cursor_y-1)/3)+1;
    }

    return opcion;
}

void desplegar_menu_principal()
{
    const int NUM_OPCIONES = 8;
    const char* OPCIONES[NUM_OPCIONES] = {"Crear personas y clientes","Realizar movimientos","Consultar cuentas","Hacer Backup","Restaurar Backup","Ayuda","Ver imagen del grupo de devs", "Salir"};

    int NUM_OPCIONES_SUB;
    int opcion_sub;

    TablaHash<Persona*>* personas = cargar_personas_al_hash(13);
    TablaHash<Cuenta*>* cuentas_por_cedula = new TablaHash<Cuenta*>(13);
    TablaHash<Cuenta*>* cuentas = cargar_cuentas_al_hash(13, personas, cuentas_por_cedula);
    ArbolBinario<Cuenta*>* arbol_cuentas = new ArbolBinario<Cuenta*>;
    cargar_cuentas_al_arbol(personas,arbol_cuentas);

    int opcion;
    do
    {
        system("cls");
        opcion = desplegar_menu(OPCIONES, NUM_OPCIONES, 0, 1);
        if (opcion == 1)
        {
            NUM_OPCIONES_SUB = 3;
            const char* OPCIONES_SUB[NUM_OPCIONES_SUB] = {"Crear persona","Abrir cuenta","Volver al menu principal"};
            do
            {

                system("cls");
                opcion_sub =  desplegar_menu(OPCIONES_SUB, NUM_OPCIONES_SUB, 0, 1);
                system("cls");
                if(opcion_sub == 1)
                {
                    ingresar_datos_usuario(personas);
                }
                else if(opcion_sub == 2)
                {
                    abrir_cuenta(personas, cuentas, cuentas_por_cedula, arbol_cuentas);
                }
                visibilidad_cursor(false);

            }
            while(opcion_sub != NUM_OPCIONES_SUB);


        }
        else if(opcion == 2){
            hacer_transacciones(cuentas, cuentas_por_cedula);
        }
        else if(opcion == 3){

        }
        else if(opcion == 4)
        {
            system("cls");
            Fecha fecha;
            if(!crear_backup(fecha))
            {
                printf("\nHubo un error al crear el backup\n");
            }
            else
            {
                printf("\nSe creo el backup exitosamente\n");
            }
            system("pause");
        }
        else if(opcion == 5)
            elegir_backup();
        else if(opcion == 6)
            abrir_menu_ayuda();
        else if(opcion == 7)
        {
            system("cls");
            Imagen imagen("Sin titulo.bmp");
            imagen.imprimirImagenEnConsola();
        }

        visibilidad_cursor(false);
    }
    while(opcion != NUM_OPCIONES);

    mover_cursor(0,(opcion*3)+1);
}

void abrir_menu_ayuda()
{
    const char* nombreArchivo = R"(E:\\html\\index.html)";

    ShellExecuteA(nullptr, "open", nombreArchivo, nullptr, nullptr, SW_SHOWNORMAL);
}

void elegir_backup()
{
    system("cls");
    int cursorx = 0, cursory = 0;
    int anuario;
    int mes;
    int dia;
    int hora;
    int minutos;
    int segundos;
    visibilidad_cursor(true);


    do
    {
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        anuario = ingresar_enteros("Ingrese el anuario del backup que desea restaurar");

        if(anuario<1900 || anuario > 2500)
        {
            mover_cursor(cursorx, cursory+3);
            printf("El anuario debe ser mayor a 1900 y menor a 2500");
        }
        else
        {
            mover_cursor(cursorx, cursory+3);
            printf("                                                                ");
        }
    }
    while(anuario<1900 || anuario>2500);
    cursory = cursory + 2;

    do
    {
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        mes = ingresar_enteros("Ingrese el mes del backup que desea restaurar");

        if(mes < 1 || mes > 12)
        {
            mover_cursor(cursorx, cursory+3);
            printf("El mes debe estar entre 1 y 12");
        }
        else
        {
            mover_cursor(cursorx, cursory+3);
            printf("                                                           ");
        }
    }
    while(mes<1 || mes>12);
    cursory = cursory + 2;
    bool invalido;
    do
    {
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        dia = ingresar_enteros("Ingrese el dia del backup que desea restaurar");


        if(dia>28)
        {
            if (mes==2)
            {
                if(anuario%4!=0)
                {
                    invalido = true;
                }
                else
                {
                    invalido = (dia > 29);
                }
            }
            else if (((mes < 8) && mes%2!=0)||(mes >= 8) && mes%2==0)
            {
                invalido = (dia > 31);
            }
            else
            {
                invalido = (dia > 30);
            }
        }
        if(invalido)
        {
            mover_cursor(cursorx, cursory+3);
            printf("El dia ingresado es invalido para el mes y anuario dados");
        }
        else
        {
            mover_cursor(cursorx, cursory+3);
            printf("                                                             ");
        }

    }
    while(invalido);
    cursory = cursory + 2;

    do
    {
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        hora = ingresar_enteros("Ingrese la hora del backup que desea restaurar");

        if(hora < 0 || hora > 23)
        {
            mover_cursor(cursorx, cursory+3);
            printf("La hora debe estar entre 0 y 23");
        }
        else
        {
            mover_cursor(cursorx, cursory+3);
            printf("                                                                ");
        }
    }
    while(hora < 0 || hora > 23);
    cursory = cursory + 2;

    do
    {
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        minutos = ingresar_enteros("Ingrese los minutos del backup que desea restaurar");

        if(minutos < 0 || minutos > 59)
        {
            mover_cursor(cursorx, cursory+3);
            printf("Los minutos debe estar entre 0 y 59");
        }
        else
        {
            mover_cursor(cursorx, cursory+3);
            printf("                                                               ");
        }
    }
    while(minutos < 0 || minutos > 59);
    cursory = cursory + 2;

    do
    {
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        segundos = ingresar_enteros("Ingrese los segundos del backup que desea restaurar");

        if(segundos < 0 || segundos > 59)
        {
            mover_cursor(cursorx, cursory+3);
            printf("Los segundos debe estar entre 0 y 59");
        }
        else
        {
            mover_cursor(cursorx, cursory+3);
            printf("                                                             ");
        }
    }
    while(segundos < 0 || segundos > 59);
    cursory = cursory + 2;

    Fecha fecha_backup(anuario, mes, dia, hora, minutos, segundos);

    if(!restaurar_backup(fecha_backup.to_string_documento()+".csv"))
    {
        printf("\nNo se pudo restaurar el backup descrito, asegurese de escribir correctamente la informacion");
    }
    else
    {
        mover_cursor(cursorx, cursory+3);
        printf("Se restauro exitosamente el backup descrito\n");
    }
    system("pause");
}

void hacer_transacciones(TablaHash<Cuenta*>* cuentas, TablaHash<Cuenta*>* cuentas_por_cedula){
    const double MONTO_MINIMO = 5.0;
    double monto;
    int num_cuenta_buscar;
    Nodo<Cuenta*>* cuenta_nodo;
    Cuenta* cuenta;
    const int NUM_OPCIONES = 6;
    const char* opciones[NUM_OPCIONES] = {"Depositar","Retirar","Consultar Saldos","Pagar cuota credito","Obtener credito","Volver al menu principal"};
    int opcion;
    int opcion_volver;
    bool cuenta_existente;
    const char* volver[2] = {"Volver al menu anterior", "Probar con otro numero de cuenta"};

    do{
        system("cls");
        num_cuenta_buscar = ingresar_enteros("Ingrese el numero de cuenta");
        cuenta_nodo = cuentas->buscar(num_cuenta_buscar);
        cuenta_existente = cuenta_nodo!=nullptr;
        if(!cuenta_existente){
            printf("\nLa cuenta ingresada no existe\n");
            system("pause");
            system("cls");
            opcion_volver = desplegar_menu(volver,2,0,1);
            if(opcion_volver==1)break;
        }
    }while(!cuenta_existente);
    if(cuenta_existente){
        cuenta = cuenta_nodo->get_valor();
        Movimientos movimientos(cuenta);
         do{
            system("cls");
            opcion = desplegar_menu(opciones, NUM_OPCIONES, 0, 1);

            if(opcion == 1){
                do
                {
                    system("cls");
                    monto = ingresar_reales("Ingrese el monto que va a depositar en la cuenta");

                    if(monto<MONTO_MINIMO)
                    {
                        printf("\nEl monto minimo requerido para abrir una cuenta es de %f USD\nIngrese de nuevo\n", MONTO_MINIMO);
                        system("pause");
                    }
                }
                while(monto<MONTO_MINIMO);

                if(movimientos.deposito(monto)){
                    if(!actualizar_cuenta(*cuenta)){
                        printf("\nHubo un error al actualizar la cuenta");
                        movimientos.borrar_ultimo();
                        printf("\nLa transaccion no fue realizada\n");
                    }
                }else{
                    printf("\nHubo un error al cargar el movimiento la transaccion no fue realizada\n");
                }

            }
            else if(opcion == 2){

            }
            else if(opcion == 3){

            }
            else if(opcion == 4){

            }
            else if(opcion == 5){

            }
            system("cls");

        }while(opcion!=NUM_OPCIONES);
    }
}

void abrir_cuenta(TablaHash<Persona*>* personas, TablaHash<Cuenta*>* cuentas, TablaHash<Cuenta*>* cuentas_por_cedula, ArbolBinario<Cuenta*>* arbol_cuentas)
{
    std::string cedula;
    bool cedula_existente, cuenta_existente;
    short int opcion;
    int opcion_volver;
    const double MONTO_MINIMO = 5.0;
    double monto_inicial;
    Nodo<Persona*>* persona_nodo;
    Nodo<Cuenta*>* cuenta_nodo;
    Cuenta* cuenta;
    Persona* persona;
    ListaDoble<Cuenta*>* lista_cuentas;
    const char* opciones[2] = {"Si", "No"};
    const char* volver[2] = {"Volver al menu anterior", "Probar con otra cedula"};

    do
    {
        system("cls");
        visibilidad_cursor(true);
        cedula = ingresar_numeros_cedula("Ingrese el No. de cedula de la persona");
        printf("\n");
        persona_nodo = personas->buscar_cedula_persona(cedula);
        cedula_existente = (persona_nodo != nullptr);

        if(!cedula_existente)
        {
            printf("\nNo se ha ingresado la persona desea ingresarla ahora mismo?\n");
            opcion = desplegar_menu_movible(opciones,2,0,6);

            if(opcion==1)
            {
                system("cls");
                visibilidad_cursor(true);
                std::cout<<cedula<<std::endl;
                std::string nombre = ingresar_string("Ingrese el nombre de la persona");
                printf("\n");
                std::string apellido = ingresar_string("Ingrese el apellido de la persona");
                printf("\n");

                persona = new Persona(nombre,apellido,cedula);

                if(!guardar_persona(*persona))
                {
                    printf("\nNo se ha podido guardar la informacion de la persona en el archivo\n");
                }

                personas->insertar(persona, cedula);
                break;
            }
        }
        else
        {
            cuenta_nodo = cuentas_por_cedula->buscar_cedula_cuenta(cedula);
            cuenta_existente = cuenta_nodo!=nullptr;
            if(cuenta_existente)
            {
                cuenta = cuenta_nodo->get_valor();
                printf("\nLa persona con la cedula ingresada ya tiene una cuenta\n");
                cuenta->imprimir();
                system("pause");

                do
                {
                    system("cls");
                    opcion_volver = desplegar_menu(volver,2,0,1);
                }
                while(opcion_volver<1 || opcion_volver>2);

                if((opcion_volver) == 1)
                {
                    break;
                }


            }
            else
            {
                persona = persona_nodo->get_valor();
            }
        }

    }
    while(!cedula_existente || cuenta_existente);

    if(!cuenta_existente)
    {
        do
        {
            system("cls");
            printf("\nAbriendo cuenta para: \n");
            persona->imprimir();
            visibilidad_cursor(true);
            monto_inicial = ingresar_reales("\nIngrese el monto incicial que va a depositar en la cuenta");

            if(monto_inicial<MONTO_MINIMO)
            {
                printf("\nEl monto minimo requerido para abrir una cuenta es de %f USD\nIngrese de nuevo\n", MONTO_MINIMO);
                system("pause");
            }

        }
        while(monto_inicial<MONTO_MINIMO);

        Cliente* cliente = new Cliente(persona);
        cuenta = new Cuenta(cliente);
        Movimientos* movimientos = new Movimientos(cuenta);
        movimientos->deposito(monto_inicial);
        guardar_cuenta(*cuenta);
        arbol_cuentas->insertar(cuenta, 1);
    }
}

void ingresar_datos_usuario(TablaHash<Persona*>* personas)
{
    std::string cedula;
    bool cedula_existente;
    do
    {
        system("cls");
        cedula = ingresar_numeros_cedula("Ingrese el No. de cedula de la persona");
        printf("\n");
        cedula_existente = (personas->buscar_cedula_persona(cedula) != nullptr);

        if(cedula_existente)printf("\nCedula ya existente\n"), system("pause");
    }
    while(cedula_existente);

    std::string nombre = ingresar_string("Ingrese el nombre de la persona");
    printf("\n");
    std::string apellido = ingresar_string("Ingrese el apellido de la persona");
    printf("\n");

    Persona* persona = new Persona(nombre,apellido,cedula);

    if(!guardar_persona(*persona))
    {
        printf("No se ha podido guardar la informacion de la persona en el archivo");
    }

    personas->insertar(persona, cedula);

    system("pause");
}

void ingresar_datos_credito()
{
    system("cls");
    Fecha sacado;
    double monto = 0, tasa_interes = 0;
    int cursorx = 0, cursory = 0;
    int ncuotas = 0;

    visibilidad_cursor(true);

    while(monto<=0 || monto > 9999999.99)
    {
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        cursory = 0;
        mover_cursor(cursorx, cursory);
        monto = ingresar_reales("Ingrese el monto del credito");

        if(monto<=0 || monto > 99999999.99)
        {
            mover_cursor(cursorx, cursory+3);
            printf("El monto debe ser mayor a 0 y menor a 10M");
        }
        else
        {
            mover_cursor(cursorx, cursory+3);
            printf("                                                           ");
        }
    }

    cursory = cursory + 2;
    while(ncuotas<=0 || ncuotas > 150)
    {
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        ncuotas = ingresar_enteros("Ingrese el numero de cuotas a pagar del credito");

        if(ncuotas<=0 || ncuotas > 150)
        {
            mover_cursor(cursorx, cursory+3);
            printf("El numero de cuotas debe ser mayor a 0 y menor a 150");
        }
        else
        {
            mover_cursor(cursorx, cursory+3);
            printf("                                                           ");
        }
    }
    cursory = cursory + 2;
    while(tasa_interes<=0 || tasa_interes>99.99)
    {
        mover_cursor(cursorx, cursory+1);
        printf("                ");
        mover_cursor(cursorx, cursory);
        tasa_interes = ingresar_reales("Ingrese la tasa de interes del credito");

        if(tasa_interes<=0 || tasa_interes>99.99)
        {
            mover_cursor(cursorx, cursory+3);
            printf("La tasa de interes debe ser mayor a 0 y menor a 100%");
        }
        else
        {
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

    if(!guardar_credito(credito))
    {
        printf("No se ha podido guardar la informacion del credito en el archivo");
    }

    system("pause");
}

void consultar_cuota()
{
    system("cls");
    int id_credito;
    Credito credito_consult;

    visibilidad_cursor(true);
    id_credito = ingresar_enteros("Ingrese el numero del credito");

    if(existe_credito(id_credito))
    {
        Fecha fecha_act, fecha_sigpago;

        credito_consult = obtener_credito(id_credito);
        TablaAmortizacion tabla(credito_consult);

        Nodo<Fecha>* fecha_sig = tabla.get_fechas_pago()->get_cabeza();
        Nodo<double>* saldo_pendiente = tabla.get_saldos_capital()->get_cabeza();
        while(fecha_sig!= nullptr && (fecha_sig->get_valor() < fecha_act))
        {
            fecha_sig = fecha_sig->get_siguiente();
            saldo_pendiente = saldo_pendiente->get_siguiente();
        }
        if(fecha_sig != nullptr)
        {
            fecha_sigpago = fecha_sig->get_valor();
            std::cout<<"\nSaldo pendiente: "<<saldo_pendiente->get_valor();
            std::cout<<"\nSiguiente fecha de pago: "<<fecha_sigpago.to_string();
        }
        else
        {
            std::cout<<"\nSaldo pendiente: 0";
        }
        printf("\n\n");
        tabla.imprimir();
    }
    else
    {
        printf("\nNo existe el credito solicitado\n");
    }


    system("pause");
}

bool operator<(Fecha fecha1, Fecha fecha2)
{
    bool menor;
    if(fecha1.get_anuario()<fecha2.get_anuario())
    {
        menor = true;
    }
    else if(fecha1.get_anuario() == fecha2.get_anuario())
    {
        if(fecha1.get_mes()<fecha2.get_mes())
        {
            menor = true;
        }
        else if(fecha1.get_mes() == fecha2.get_mes())
        {
            if(fecha1.get_dia()<fecha2.get_dia())
            {
                menor = true;
            }
            else if(fecha1.get_dia() == fecha2.get_dia())
            {
                if(fecha1.get_dia()<fecha2.get_dia())
                {
                    menor = true;
                }
                else if(fecha1.get_dia() == fecha2.get_dia())
                {
                    if(fecha1.get_hora()<fecha2.get_hora())
                    {
                        menor = true;
                    }
                    else if(fecha1.get_hora() == fecha2.get_hora())
                    {
                        if(fecha1.get_minutos()<fecha2.get_minutos())
                        {
                            menor = true;
                        }
                        else if(fecha1.get_minutos() == fecha2.get_minutos())
                        {
                            if(fecha1.get_segundos()<fecha2.get_segundos())
                            {
                                menor = true;
                            }
                            else if(fecha1.get_segundos() == fecha2.get_segundos())
                            {
                                menor = false;
                            }
                            else
                            {
                                menor = false;
                            }
                        }
                        else
                        {
                            menor = false;
                        }
                    }
                    else
                    {
                        menor = false;
                    }
                }
                else
                {
                    menor = false;
                }
            }
            else
            {
                menor = false;
            }
        }
        else
        {
            menor = false;
        }
    }
    else
    {
        menor = false;
    }

    return menor;
}



#endif // MENUS_H_INCLUDED
