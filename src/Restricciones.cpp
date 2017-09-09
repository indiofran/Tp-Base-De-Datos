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
    if (r2._campo != r1._campo) {
        return false;
    }else{
        if (r1._valor != r2._valor) {
            return false;
        }else{
            return r1._filtro == r2._filtro;
        }
    }
}

bool operator!=(const Restricciones& r1, const Restricciones& r2){
    return not (r1 == r2);
}

