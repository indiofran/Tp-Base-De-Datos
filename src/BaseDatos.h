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

    BaseDatos();

    /*
     * @generador
     */
    map<string, Tabla> agregar_tabla(string nombre_tabla, Tabla tabla);

    void agregar_registro(string nombre_tabla, Registro r);

    /*
     * TODO buscar:
     * que no se sume dos veces
     * ver el true y el false
     */

    bool puedo_agregar_registro(string name_table, Registro r);

    Tabla busqueda(string nombre_tabla, Criterio criterio);

    /*
     * @observador
     */
    map<string, Tabla> base() const;


    Tabla devoler_tabla(string nombre_tabla);


    bool criterio_valido(string nombre_tabla, Criterio criterio);

    int criterio_mas_utilizado();







    // bool operator==(const BaseDatos&, const BaseDatos&);

private:


    vector<pair<Criterio, int>> criterios_utilizados;
    vector<Tabla> _tablas;
    map<string, Tabla> base_de_datos;

    vector<Registro> filtrar_resgitros_que_tiene(vector<Registro> registros_donde_buscar, Restricciones restriccion);
    vector<Registro> filtrar_resgitros_que_no_tiene(vector<Registro> registros_donde_buscar, Restricciones restriccion);

    pair<bool, int> tiene_criterio(Criterio criterio);

    void agregar_criterio_utilizado(Criterio criterio);

    bool hay_registro_repetidos(Tabla tabla, Registro registro);
};


#endif