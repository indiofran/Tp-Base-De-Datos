#ifndef RESTRICCIONES_H
#define RESTRICCIONES_H

#include <vector>
#include <map>
#include "Dato.h"


using namespace std;

class Restricciones {

public:
    /*
    * @generador
    */
    Restricciones(string campo, Dato valor, bool filtro);

    string get_campo() const;

    Dato get_valor() const;

    bool get_filtro() const;



private:

    string _campo;
    Dato _valor;
    bool _filtro;

};

bool operator==(const Restricciones&, const Restricciones&);

bool operator!=(const Restricciones&, const Restricciones&);

#endif
