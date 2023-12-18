/***********************************************************************
 UFA - ESPE
 * Module:  Imagen.h
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: domingo, 17 de diciembre de 2023 11:05:27 p. m.
 * Purpose: Archivo de imagen para imprimir en consola
 ***********************************************************************/
#ifndef IMAGEN_H
#define IMAGEN_H
#include <string>
#include <windows.h>
#include "../../../../../Bibliotecas/EasyBMP.h"


class Imagen{
	public:
		Imagen(std::string);
		void setArchivo (std::string);
		std::string getArchivo();
		int imprimirImagenEnConsola();
	private:
		void dibujarImagen(std::string, HDC*);
		std::string archivo;
};
#endif
