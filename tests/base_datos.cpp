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
    vector <string> tablas_nombre;
    tablas_nombre.push_back("Alumnos");
    vector <Tabla> tablas;
    tablas.push_back(alumnos);
    BaseDatos universidad(tablas_nombre,tablas);
    EXPECT_EQ(universidad.devoler_tabla("Alumnos"),alumnos);
}
TEST_F(BasedatosTests, Argregar_tabla){
    BaseDatos universidad;
    universidad.agregar_tabla("carreras", carreras);
    EXPECT_EQ(universidad.devoler_tabla("carreras"),carreras);
}
TEST_F(BasedatosTests, Argregar_registro_no_puedo){
    BaseDatos universidad;
    universidad.agregar_tabla("carreras", carreras);
    universidad.agregar_registro("Alumnos",Registro({"LU", "Mes", "Nombre", "Carrera"}, {datoNat(182), datoNat(12), datoStr("March"), datoStr("Computacion")}));
    EXPECT_EQ(universidad.devoler_tabla("carreras"),carreras);
    universidad.agregar_registro("carreras",Registro({"LU", "Mes", "Nombre", "Carrera"}, {datoNat(182), datoNat(12), datoStr("March"), datoStr("Computacion")}));
    EXPECT_EQ(universidad.devoler_tabla("carreras"),carreras);
}
TEST_F(BasedatosTests, Argregar_registro_puedo){
    BaseDatos universidad;
    universidad.agregar_tabla("Alumnos", alumnos);
    Registro r({"LU", "Año", "Nombre", "Carrera"}, {datoNat(182), datoNat(12), datoStr("March"), datoStr("Computacion")});
    universidad.agregar_registro("Alumnos",r);
    alumnos.agregarRegistro(r);
    EXPECT_EQ(universidad.devoler_tabla("Alumnos"),alumnos);
}
//TEST_F(BasedatosTests, Busqueda){
//    BaseDatos universidad;
//    universidad.agregar_tabla("carreras", carreras);
//    universidad.agregar_registro("Alumnos",Registro({"LU", "Año", "Nombre", "Carrera"}, {datoNat(182), datoNat(12), datoStr("March"), datoStr("Computacion")}));
//    EXPECT_EQ(universidad.devoler_tabla("carreras"),carreras);
//}

