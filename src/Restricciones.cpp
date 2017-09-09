#include "Restricciones.h"

Restricciones::Restricciones (string campo, Dato valor, bool filtro):
_campo(campo), _valor(valor), _filtro(filtro) {};

string Restricciones::get_campo() const{
    return _campo;
};

Dato Restricciones::get_valor() const{
    return _valor;
};

bool Restricciones::get_filtro() const{
    return _filtro;
};


bool operator==(const Restricciones& r1, const Restricciones& r2){
    if (r2.get_campo() != r1.get_campo()) {
        return false;
    }else{
        if (r1.get_valor() != r2.get_valor()) {
            return false;
        }else{
            return r1.get_filtro() == r2.get_filtro();
        }
    }
}

bool operator!=(const Restricciones& r1, const Restricciones& r2){
    return not (r1 == r2);
}

