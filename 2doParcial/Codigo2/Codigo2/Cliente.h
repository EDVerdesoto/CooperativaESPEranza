/***********************************************************************
  UFA - ESPE
 * Module:  Cliente.h
 * Author:  Edison Verdesoto, Joan Cobeña
 * Modified: viernes, 2 de febrero de 2024 19:31:11
 * Purpose: Declaration of the class Cliente
 ***********************************************************************/

#if !defined(__Class_Diagram_1_Cliente_h)
#define __Class_Diagram_1_Cliente_h

class Cuenta;

#include "Persona.h"

class Cliente
{
public:
   void apertura_cuenta(void);
   std::string es_moroso(void);

   void generar_ID_cliente(char ID[7], int i, bool &guardado);
   std::string generar_ID(std::string nombre, int i);
   void guardar_ID_en_archivo(const std::string &archivo, const std::string &ID);
   bool ID_existe_en_archivo(const std::string &archivo, const std::string &ID);

   Persona* get_persona();
   std::string get_id();

protected:
private:
   Persona* persona;
   std::string ID_cliente;


};

#endif
