#include "BaseDatos.h"

using namespace std;

BaseDatos::BaseDatos(vector<string> nombre_tablas, vector<Tabla> tablas):_tablas(tablas){
      for(int i = 0; i < tablas.size(); i++) {
        this->base_de_datos.insert(make_pair(nombre_tablas[i], tablas[i]));
    }

}
map<string,Tabla> BaseDatos::base() const {
    return base_de_datos;
}
map<string,Tabla> BaseDatos::agregar_tabla(string nombre_tabla, Tabla tabla){
     this->base_de_datos.insert(make_pair(nombre_tabla, tabla));
    return this->base_de_datos;
};
Tabla BaseDatos::agregar_registro(string nombre_tabla, Registro r) {
    Tabla tabla_a_agregar_registro = this->base().at(nombre_tabla);
    tabla_a_agregar_registro.agregarRegistro(r);
}

Tabla BaseDatos::devoler_tabla(string nombre_tabla){
    return  this->base().at(nombre_tabla);
}
