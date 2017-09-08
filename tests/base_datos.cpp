//
// Created by Francisco on 03/09/2017.
//
#include "gtest/gtest.h"
#include "../src/BaseDatos.h"

using namespace std;

class BasedatosTests : public ::testing::Test {
protected:
    BasedatosTests() : alumnos({"LU", "Año", "Nombre", "Carrera"},
                         { "LU", "Año" },
                         { datoNat(0), datoNat(0), datoStr(""), datoStr("")}),
                       carreras({"Cod", "Carrera"},
                          {"Cod"},
                          {datoNat(0), datoStr("")}) {};

    Tabla alumnos;
    Tabla carreras;

};
TEST(Base_test, crear) {
    Tabla alumnos({ "LU", "Año", "Nombre", "Carrera" },
            {"LU", "Año"},
            {datoNat(0), datoNat(0), datoStr(""), datoStr("")});
    Tabla carreras({ "Cod", "Carrera" },
             {"Cod"},
             {datoNat(0), datoStr("")});
    Registro({"LU", "Año", "Nombre", "Carrera"}, {datoNat(182), datoNat(18), datoStr("March"), datoStr("Computacion")});
    Registro({}, {});
};
TEST_F(BasedatosTests, nueva){
    string tabla_nombres[] = {"Alumnos"};
    vector <string> tablas_nombre(tabla_nombres, tabla_nombres + sizeof(tabla_nombres) / sizeof(string));
    Tabla array_tablas[]= {alumnos};
    vector <Tabla> tablas(array_tablas,array_tablas + sizeof(array_tablas) / sizeof(Tabla));
    BaseDatos universidad(tablas_nombre,tablas);
    universidad.agregar_tabla("carreras", carreras);
    Registro nuevo_registro({"Nombre", "LU"}, {datoStr("March"), datoStr("64/9")});
    alumnos.agregarRegistro(nuevo_registro);
    universidad.agregar_registro("Alumnos",nuevo_registro);
    EXPECT_EQ(universidad.devoler_tabla("Alumnos"),alumnos);
}
//TEST_F(BasedatosTests, Argregar_registro){
//    string tabla_nombres[] = {"Alumnos"};
//    vector <string> tablas_nombre(tabla_nombres, tabla_nombres + sizeof(tabla_nombres) / sizeof(string));
//    Tabla array_tablas[]= {alumnos};
//    vector <Tabla> tablas(array_tablas,array_tablas + sizeof(array_tablas) / sizeof(Tabla));
//    BaseDatos universidad(tablas_nombre,tablas);
//    universidad.agregar_registro("Alumnos",Registro({"Nombre", "LU"}, {datoStr("March"), datoStr("64/9")}));
//    EXPECT_EQ(universidad.devoler_tabla("Alumnos"),alumnos);
//}

