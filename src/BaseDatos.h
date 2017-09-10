#ifndef BASEDATO_H
#define BASEDATO_H

#include <vector>
#include <map>
#include "Tabla.h"
#include "Registro.h"
#include "Restricciones.h"

using namespace std;
typedef vector<Restricciones> Criterio;
class BaseDatos {

public:
    /*
     * @generador
     */
    BaseDatos(vector<string> nombre_tablas, vector<Tabla> tabla);

    /*
     * @generador
     */
    map<string, Tabla> agregar_tabla(string nombre_tabla, Tabla tabla);

    void agregar_registro(string nombre_tabla, Registro r);

    //Depende de las restricciones especificadas
    /*
     * TODO RESTRICCIONES
     */
    bool puedo_agregar_registro(string name_table, Registro r);

    Tabla busqueda(string nombre_tabla, Criterio criterio);

    /*
     * @observador
     */
    map<string, Tabla> base() const;

    void show_base_datos();

    Tabla devoler_tabla(string nombre_tabla);

    bool hay_registro_repetidos(Tabla tabla, Registro registro);

    bool criterio_valido(string nombre_tabla, Criterio criterio);

    Criterio criterio_mas_utilizado();

    void agregar_criterio_utilizado(Criterio criterio);

    pair <bool,int> tiene_criterio(Criterio criterio);



    // bool operator==(const BaseDatos&, const BaseDatos&);

private:


    vector<pair<Criterio, int>> criterios_utilizados;
    vector<Tabla> _tablas;
    map<string, Tabla> base_de_datos;


};


#endif