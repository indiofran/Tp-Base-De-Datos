#ifndef BASEDATO_H
#define BASEDATO_H

#include <vector>
#include <map>
#include "Tabla.h"

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
    BaseDatos agregar_tabla();

    Tabla agregar_registro();
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




private:

    vector<Tabla> _tablas;
    map<string,Tabla> base_de_datos;

    //friend bool operator==();

};


#endif