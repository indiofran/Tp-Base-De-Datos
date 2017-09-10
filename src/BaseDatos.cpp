#include "BaseDatos.h"



using namespace std;

BaseDatos::BaseDatos() {}

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
    if(this->base().find(nombre_tabla) != this->base().end()) {
        return this->base().at(nombre_tabla);
    }else{
        return Tabla({},{},{});
    }
}

bool BaseDatos::puedo_agregar_registro(string name_table, Registro r) {
    map<string, Tabla> base_datos = this->base_de_datos;
    if (base_datos.find(name_table) == base_datos.end()) {
        return false;
    } else {
        vector<string> campos = r.campos();
        Tabla tabla_a_agregar = this->devoler_tabla(name_table);
        if(r.campos() == tabla_a_agregar.campos()){
            for (int i = 0; i < r.campos().size() ; ++i) {
                if(r.dato(r.campos()[i]).esString() !=  tabla_a_agregar.tipoCampo(r.campos()[i]).esString()){
                    return false;
                }
            }
            return true;
        }else{
            return false;
        }

    }
}

Tabla BaseDatos::busqueda(string nombre_tabla, Criterio criterio) {
    map<string, Tabla> base_datos = this->base_de_datos;
    if((base_datos.find(nombre_tabla) != base_datos.end()) && this->criterio_valido(nombre_tabla, criterio)){
        agregar_criterio_utilizado(criterio);
        Tabla tabla_busqueda = base_datos.at(nombre_tabla);
        vector<string> campos_tabla = tabla_busqueda.campos();
        vector<Registro> resultado_busqueda = tabla_busqueda.registros();
        for (int i = 0; i < criterio.size(); ++i) {
            Restricciones restriccion = criterio[i];
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
        return Tabla({},{},{});
    }
};

bool BaseDatos::hay_registro_repetidos(Tabla tabla, Registro registro){
    vector<string> claves = tabla.claves();
    for (int i = 0; i < claves.size(); ++i) {
            string clave = claves[i];
        vector<Registro> registros = tabla.registros();
        for (int j = 0; j < registros.size(); ++j) {
            if(registros[j].dato(clave) == registro.dato(clave)){
                return false;
            }
        }
    }
    return true;
}

bool BaseDatos::criterio_valido(string nombre_tabla, Criterio criterio){
    map<string, Tabla> db = this->base_de_datos;
    bool res = true;
    Tabla tabla_a_comparar = db.at(nombre_tabla);
    for(int i = 0;(i < criterio.size()) && res;i++){
        res = false;
        for(int j = 0; (j < tabla_a_comparar.campos().size()) && !res; j++) {
            if (criterio[i].get_campo() == tabla_a_comparar.campos()[j] && criterio[i].get_valor() == tabla_a_comparar.tipoCampo(criterio[i].get_campo())){
                res = true;
            }
        }

    }
    return res;
};

void BaseDatos::agregar_criterio_utilizado(Criterio criterio){
    pair<bool,int> existe_criterio_pos = this->tiene_criterio(criterio);
    if(existe_criterio_pos.first){
        pair<Criterio,int>* criterio_a_sumar = &this->criterios_utilizados[existe_criterio_pos.second];
        criterio_a_sumar->second++;
    }else{
        this->criterios_utilizados.push_back(make_pair(criterio,1));
    }
}
pair <bool,int> BaseDatos::tiene_criterio(Criterio criterio){
    vector<pair<Criterio,int>> criterios_utilizados = this->criterios_utilizados;
    for (int i = 0; i < criterios_utilizados.size() ; ++i) {
        if(criterios_utilizados[i].first == criterio){
            return make_pair(true, i);
        }
    }
    return make_pair(true, -1);
}

Criterio BaseDatos::criterio_mas_utilizado(){
    vector<pair<Criterio,int>> criterios_utilizados = this->criterios_utilizados;
    pair<Criterio, int> cantidad_mas_utilizada;
    for (int i = 0; i < criterios_utilizados.size() ; ++i) {
        if(criterios_utilizados[i].second > cantidad_mas_utilizada.second){
            cantidad_mas_utilizada = criterios_utilizados[i];
        }
    }
    return cantidad_mas_utilizada.first;
};



