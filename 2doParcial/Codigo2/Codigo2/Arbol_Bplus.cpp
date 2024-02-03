#include <iostream>
#include "Arbol_Bplus.h"
#include "Nodo.cpp"
#include "ListaDoble.cpp"
#include "NodoB.h"
#include <graphics.h>
#include <string>
#include <windows.h>

Arbol_Bplus::Arbol_Bplus(int grado_max){
    grado = grado_max;
    raiz = new NodoB();
}

Nodo<int>* obtener_nodo_central(ListaDoble<int>* claves, int grado){
    Nodo<int>* aux = claves->get_cabeza();
    int i;
    for(i = 0; i<grado/2; i++){
        aux = aux->get_siguiente();
    }
    if(i%2==0){
        aux = aux->get_anterior();
    }
    return aux;
}

void insertar_en_claves(ListaDoble<int>* claves, int dato){
    Nodo<int>* aux = claves->get_cabeza();
    while(aux!=nullptr){
        if(dato <= aux->get_valor()){
            break;
        }
        aux = aux->get_siguiente();
    }
    if(aux == nullptr){
        claves->insertar_cola(dato);
    }
    else if (aux == claves->get_cabeza()){
        claves->insertar_cabeza(dato);
    }
    else{
        claves->insertar_entre(aux->get_anterior()->get_valor(), dato);
    }
}

Arbol_Bplus* obtener_hijo_a_insertar(NodoB* raiz, int dato){
    ListaDoble<int>* claves = raiz->get_claves();
    ListaDoble<Arbol_Bplus*>* hijos = raiz->get_hijos();

    Nodo<int>* clave = claves->get_cabeza();
    Nodo<Arbol_Bplus*>* hijo = hijos->get_cabeza();

    while(clave!= nullptr && dato > clave->get_valor()){
        clave = clave->get_siguiente();
        hijo = hijo->get_siguiente();
    }

    return hijo->get_valor();
}


void configurar_hijos(Nodo<int>* nodo_central, Arbol_Bplus* hijo_izq, Arbol_Bplus* hijo_der){
    Nodo<int>* cabeza_izq = nodo_central->get_anterior();
    Nodo<int>* cola_der = nodo_central->get_siguiente();

    while (cabeza_izq->get_anterior() != nullptr){
        cabeza_izq = cabeza_izq ->get_anterior();
    }
    while (cola_der->get_siguiente() != nullptr){
        cola_der = cola_der->get_siguiente();
    }

    hijo_izq->get_raiz()->get_claves()->set_cabeza(cabeza_izq);
    hijo_izq->get_raiz()->get_claves()->set_cola(nodo_central->get_anterior());
    hijo_der->get_raiz()->get_claves()->set_cabeza(nodo_central->get_siguiente());
    hijo_der->get_raiz()->get_claves()->set_cola(cola_der);

    nodo_central->get_anterior()->set_siguiente(nullptr);
    nodo_central->get_siguiente()->set_anterior(nullptr);
}

void conservar_hijos(ListaDoble<Arbol_Bplus*>* hijos_previos, Arbol_Bplus* hijo_izq, Arbol_Bplus* hijo_der, int grado){
    Nodo<Arbol_Bplus*>* hijo_prev1 = hijos_previos->get_cabeza();
    Nodo<Arbol_Bplus*>* hijo_prev2 = hijos_previos->get_cola();
    int i = (grado%2==0)?1:0;
    for(int i; i<=grado/2; i++){
        hijo_izq->get_raiz()->get_hijos()->insertar_cola(hijo_prev1->get_valor());
        hijo_der->get_raiz()->get_hijos()->insertar_cabeza(hijo_prev2->get_valor());
        hijo_prev1 = hijo_prev1->get_siguiente();
        hijo_prev2 = hijo_prev2->get_anterior();
    }

}

void Arbol_Bplus::partir(NodoB* _raiz, NodoB* raiz_anterior){

    Nodo<int>* aux = obtener_nodo_central(_raiz->get_claves(), grado);
    Arbol_Bplus* hijo_izq = new Arbol_Bplus(grado);
    Arbol_Bplus* hijo_der = new Arbol_Bplus(grado);

    configurar_hijos(aux, hijo_izq, hijo_der);

    if(raiz_anterior == nullptr){
        NodoB* nueva_raiz = new NodoB();
        nueva_raiz->get_claves()->insertar_cabeza(aux->get_valor());

        if(!_raiz->get_hijos()->esta_vacia()){
            conservar_hijos(_raiz->get_hijos(), hijo_izq, hijo_der, grado);
        }

        nueva_raiz->get_hijos()->insertar_cola(hijo_izq);
        nueva_raiz->get_hijos()->insertar_cola(hijo_der);

        aux->set_anterior(nullptr);
        aux->set_siguiente(nullptr);

        this->raiz = nueva_raiz;
    }
    else{

        Arbol_Bplus* hijo_previo = obtener_hijo_a_insertar(raiz_anterior, aux->get_valor());

        if(!_raiz->get_hijos()->esta_vacia()){
            conservar_hijos(_raiz->get_hijos(), hijo_izq, hijo_der, grado);
        }

        raiz_anterior->get_hijos()->insertar_entre(hijo_previo, hijo_der);
        raiz_anterior->get_hijos()->insertar_entre(hijo_previo, hijo_izq);

        raiz_anterior->get_hijos()->eliminar(hijo_previo);

        insertar_en_claves(raiz_anterior->get_claves(), aux->get_valor());

    }
}

void Arbol_Bplus::insertar(int dato){
    insertar_rec(dato, nullptr);
}

void Arbol_Bplus::insertar_rec(int dato, NodoB* raiz_anterior){

        if(raiz->get_claves()->esta_vacia()){
            raiz->get_claves()->insertar_cabeza(dato);
        }
        else{
            if(raiz->get_hijos()->esta_vacia()){
                insertar_en_claves(raiz->get_claves(), dato);
            }
            else{
                obtener_hijo_a_insertar(raiz, dato)->insertar_rec(dato, raiz);
            }
        }

        if(raiz->get_claves()->tam() == grado){
            partir(raiz, raiz_anterior);
        }
}


void Arbol_Bplus::eliminar(int dato){

}



void Arbol_Bplus::imprimir_rec(int x, int y, int nclaves, int nhijos,
                               int ancho, int alto, int xprev, int yprev,
                               NodoB* raiz_princ, Nodo<int>* clave, Nodo<Arbol_Bplus*>* hijo, int* tam){

    if(clave!=nullptr && clave->get_siguiente()!=nullptr){
        if(raiz == raiz_princ){
            imprimir_rec(x, y, nclaves+1, nhijos, ancho+80, alto, xprev, yprev, raiz_princ, clave->get_siguiente(), hijo, tam);
        }
        else{
            imprimir_rec(x-10, y, nclaves+1, nhijos, ancho+80, alto, xprev, yprev, raiz_princ, clave->get_siguiente(), hijo, tam);
        }
    }
    else{
        rectangle(x-ancho/2, y-alto/2, x+ancho/2, y+alto/2);
        *tam = nclaves+1;
    }

    outtextxy(x+(75*(nclaves-(*tam/2))), y-alto/4, (char*)std::to_string(clave->get_valor()).c_str());

    if(clave->get_anterior() == nullptr){
        *tam = 0;
        if(hijo!=nullptr){

        }
    }

}

void Arbol_Bplus::imprimir(){
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    initwindow(width, height,"Arbol B+");
    int ancho = 80;
    int alto = 40;
    int x = getmaxx()/2;
    int y = 30;
    int tam = 0;
    imprimir_rec(x, y, 0, 0, ancho, alto, x, y, raiz, raiz->get_claves()->get_cabeza(), raiz->get_hijos()->get_cabeza(), &tam);
}

NodoB* Arbol_Bplus::get_raiz(){
    return raiz;
}

Arbol_Bplus::~Arbol_Bplus(){

}
