#include "BaseDatos.h"

using namespace std;

BaseDatos::BaseDatos(vector<string> nombre_tablas, vector<Tabla> tablas) : _tablas(tablas) {
    for (int i = 0; i < tablas.size(); i++) {
        this->base_de_datos.insert(make_pair(nombre_tablas[i], tablas[i]));
    }

}

map<string, Tabla> BaseDatos::base() const {
    return base_de_datos;
}

map<string, Tabla> BaseDatos::agregar_tabla(string nombre_tabla, Tabla tabla) {
    this->base_de_datos.insert(make_pair(nombre_tabla, tabla));
    return this->base_de_datos;
};

void BaseDatos::agregar_registro(string nombre_tabla, Registro r) {
    if (this->puedo_agregar_registro(nombre_tabla, r)) {
        this->base_de_datos.at(nombre_tabla).agregarRegistro(r);
    }
}

Tabla BaseDatos::devoler_tabla(string nombre_tabla) {
    return this->base().at(nombre_tabla);
}

bool BaseDatos::puedo_agregar_registro(string name_table, Registro r) {
    map db = this->base_de_datos;
    if (db.find(name_table) == db.end()) {
        return false;
    } else {
        vector<string> campos = r.campos();
        for (int i = 0; i < campos.size(); ++i) {
            string campo_seleccionado = campos[i];
            if (!(((r.dato(campo_seleccionado).esNat() && r.dato(campo_seleccionado).valorNat())) ||
                    (r.dato(campo_seleccionado).esString() && (r.dato(campo_seleccionado).valorStr() != "")))) {
                return false;
            }
        }
        return true;

    }
}

Tabla BaseDatos::busqueda(Tabla tabla, vector<Restricciones> criterios) {
    if(true){//es criterio valido ejecuta la funcion

    }else{
        //devolver tabla vacia
    }
};