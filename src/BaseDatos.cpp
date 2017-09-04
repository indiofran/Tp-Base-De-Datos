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

