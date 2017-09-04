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
};
TEST_F(BasedatosTests, nueva){
    string tabla_nombres[] = {"Alumnos", "Carreras"};
    vector <string> tablas_nombre(tabla_nombres, tabla_nombres + sizeof(tabla_nombres) / sizeof(string));
    Tabla array_tablas[]= {alumnos, carreras};
    vector <Tabla> tablas(array_tablas,array_tablas + sizeof(array_tablas) / sizeof(Tabla));
    BaseDatos universidad(tablas_nombre,tablas);
    EXPECT_EQ(universidad.base().at("Alumnos"),alumnos);
}
