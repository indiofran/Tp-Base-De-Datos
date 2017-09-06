#include "Restricciones.h"

Restricciones::Restricciones (string campo, Dato valor, bool filtro):
_campo(campo), _valor(valor), _filtro(filtro) {};

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

