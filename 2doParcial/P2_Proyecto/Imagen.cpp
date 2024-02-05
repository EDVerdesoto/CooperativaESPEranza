/***********************************************************************
 UFA - ESPE
 * Module:  Imagen.cpp
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: domingo, 17 de diciembre de 2023 11:06:27 p. m.
 * Purpose: Archivo de imagen para imprimir en consola
 ***********************************************************************/

#include "Imagen.h"
#include <conio.h>
#include <windows.h>
#include <wchar.h>

////////////////////////////////////////////////////////////////////////
// Name:       Imagen(std::string)
// Purpose:    Constructor de la clase Imagen
// Parameters:
// - archivo
// Return:
////////////////////////////////////////////////////////////////////////
Imagen::Imagen(std::string archivo)
{
    this->archivo = archivo;
}

////////////////////////////////////////////////////////////////////////
// Name:       setArchivo(std::string)
// Purpose:    Cambia el atributo archivo
// Parameters:
// - newArchivo
// Return:     void
////////////////////////////////////////////////////////////////////////

void Imagen::setArchivo(std::string newArchivo)
{
    this->archivo = newArchivo;
}

////////////////////////////////////////////////////////////////////////
// Name:       getArchivo()
// Purpose:    Devuelve el atributo archivo.
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Imagen::getArchivo()
{
    return this->archivo;
}

////////////////////////////////////////////////////////////////////////
// Name:       imprimirImagenEnConsola()
// Purpose:    Imprime la imagen correspondiente al archivo en consola
// Return:     int
////////////////////////////////////////////////////////////////////////

int Imagen::imprimirImagenEnConsola()
{
    // Se obtiene el identificador de la ventana de la consola
    HWND console = GetConsoleWindow();
    // Se obtiene el identificador de salida estándar de la consola
    HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
    // Se obtiene el contexto de dispositivo de la consola
    HDC dc = GetDC(console);

    // Se obtiene la información de la fuente de la consola actual
    CONSOLE_FONT_INFOEX Font = { sizeof(Font) };
    GetCurrentConsoleFontEx(output, FALSE, &Font);

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 1;
    cfi.dwFontSize.Y = 1;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");
    // Se establece la nueva fuente de la consola
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    // Se muestra la ventana de la consola maximizada
    ShowWindow(console, SW_SHOWMAXIMIZED);

    // Se imprime una línea en blanco
    std::cout << std::endl;

    // Se dibuja la imagen en la consola utilizando el método drawImage
    dibujarImagen(this->archivo, &dc);

    // Se espera la entrada de un carácter del usuario
    _getch();

    // Se restaura la fuente de la consola original
    SetCurrentConsoleFontEx(output, FALSE, &Font);

    // Se limpia la pantalla de la consola
    system("cls");

    // Se devuelve 0 para indicar que la función se ejecutó correctamente
    return 0;
}

////////////////////////////////////////////////////////////////////////
// Name:       dibujarImagen(std::string, HDC*)
// Purpose:    Pixelea la imagen
// Parameters:
// - imagePath
// - console
// Return:     void
////////////////////////////////////////////////////////////////////////

void Imagen::dibujarImagen(std::string imagePath, HDC* console)
{
    // Se lee la imagen desde el archivo especificado
    BMP image;
    image.ReadFromFile(imagePath.c_str());

    // Se obtiene el ancho y alto originales de la imagen
    double original_width = image.TellWidth();
    double original_height = image.TellHeight();

    // Se calcula la relación de aspecto de la imagen
    double ratio = ratio = original_width / original_height;

    // Se establece el ancho máximo deseado para la imagen
    double max_width = 500;
    double width = original_width;
    double height = original_height;

    // Se ajusta la altura proporcionalmente si el ancho original es mayor que el ancho máximo
    if (original_width > max_width)
    {
        height = max_width / ratio;
    }

    // Se itera sobre cada píxel de la imagen
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Se obtienen los valores de los componentes de color (rojo, verde, azul, alfa)
            int RED = image.GetPixel(x, y).Red;
            int GREEN = image.GetPixel(x, y).Green;
            int BLUE = image.GetPixel(x, y).Blue;
            int ALPHA = image.GetPixel(x, y).Alpha;

            // Se crea un valor de color utilizando los componentes RGB
            COLORREF COLOUR = RGB(RED, GREEN, BLUE);

            // Si el valor de alfa es cero, se imprime un bloque de color en la consola
            if (ALPHA == 0)
            {
                std::cout << "\033["
                          << 48
                          << ";2;"
                          << RED << ";"
                          << GREEN << ";"
                          << BLUE << "m"
                          << "##"
                          << "\033[0;00m";

                // Si se llega al final de la línea, se imprime un salto de línea
                if (x == width - 1)
                {
                    std::cout << std::endl;
                }
            }
        }
    }
}
