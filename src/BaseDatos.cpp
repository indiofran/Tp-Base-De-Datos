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
    map<string, Tabla> base_datos = this->base_de_datos;
    if (base_datos.find(name_table) == base_datos.end()) {
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

Tabla BaseDatos::busqueda(string nombre_tabla, Criterios criterios) {
    map<string, Tabla> base_datos = this->base_de_datos;
    if((base_datos.find(nombre_tabla) != base_datos.end()) && this->criterio_valido(criterios)){
        Tabla tabla_busqueda = base_datos.at(nombre_tabla);
        vector<string> campos_tabla = tabla_busqueda.campos();
        vector<Registro> resultado_busqueda = tabla_busqueda.registros();
        for (int i = 0; i < criterios.size(); ++i) {
             Restricciones restriccion = criterios[i];
            for (int k = 0; k < resultado_busqueda.size(); ++k) {
                Registro registro = resultado_busqueda[k];
                if (registro.dato(restriccion.get_campo()) == restriccion.get_valor() ){
                    resultado_busqueda.push_back(registro);
                }
            }
        }
        vector<Dato> tipos;
        for (int j = 0; j < campos_tabla.size() ; ++j) {
            tipos.push_back(tabla_busqueda.tipoCampo(campos_tabla[j]));
        }
        Tabla resultado(campos_tabla,tabla_busqueda.claves(),tipos);
        return  resultado;
    }else{
        return Tabla({},{},{});//Tabla Vacia
    }
};

bool BaseDatos::hay_registro_repetidos(Tabla tabla, Registro registro){


}

bool BaseDatos::criterio_valido(Criterios criterios){
    map<string, Tabla> db = this->base_de_datos;
    bool res = true;
    string nombre_tabla;
    Tabla tabla_a_comparar = db.at(nombre_tabla);
    for(int i = 0;(i < criterios.size()) && (res= true);i++){
        for(int j = 0; j < tabla_a_comparar.campos().size(); j++) {
            if (criterios[i].get_campo() == tabla_a_comparar.campos()[j] && criterios[i].get_valor() == tabla_a_comparar.tipoCampo(criterios[i].get_campo())){
                j = tabla_a_comparar.campos().size();
                res = true;
            } else {
                res = false;
                j++;
            }
        }
        i++;
    }
    return res;
};
