#ifndef TP1_CRITERIOS_H
#define TP1_CRITERIOS_H

#include <vector>
#include <map>


using namespace std;

class Restricciones {

public:
    /*
    * @generador
    */
    Restricciones(vector<string> campo_y_valor, bool filtro);
    /*
    * @generador
    */
    pair<vector<string>, bool> crear_restriccion (vector<string> campo_y_valor, bool filtro);

private:

    pair<vector<string>,bool> restricciones;

};


#endif
