#ifndef BASEDATO_H
#define BASEDATO_H

#include <vector>
#include <map>
#include "Tabla.h"
#include "Registro.h"
#include "Restricciones.h"

using namespace std;

class BaseDatos{

public:
    /*
     * @generador
     */
    BaseDatos (vector<string> nombre_tablas, vector<Tabla> tabla);
    /*
     * @generador
     */
    map<string,Tabla> agregar_tabla(string nombre_tabla, Tabla tabla);

    Tabla agregar_registro(string nombre_tabla, Registro r);

    //Depende de las restricciones especificadas
    /*
     * TODO RESTRICCIONES
     */
    bool puedo_agregar_registro();

    Tabla busqueda();
    /*
     * @observador
     */
    map<string,Tabla> base() const;

    void show_base_datos();

    Tabla devoler_tabla(string nombre_tabla);

//    Tabla busqueda(Tabla tabla_a_buscar, vector<Restricciones> criterios);



private:

    vector<Tabla> _tablas;
    map<string,Tabla> base_de_datos;

    //friend bool operator==();

};


#endif