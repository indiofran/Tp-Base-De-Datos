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
            {datoStr(""), datoNat(0), datoStr(""), datoStr("")});
    Tabla carreras({ "Cod", "Carrera" },
             {"Cod"},
             {datoNat(0), datoStr("")});
    Registro({"LU", "Año", "Nombre", "Carrera"}, {datoStr("45/6"), datoNat(18), datoStr("March"), datoStr("Computacion")});
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

TEST_F(BasedatosTests, criterio_valido) {
    vector<string> tablas_nombres;
    tablas_nombres.push_back("Alumnos");
    vector<Tabla> tablas;
    Tabla alumnos({"Nombre", "LU", "Ano"},
                  {"LU"},
                  {datoStr(""), datoStr (""), datoNat(0)});
    tablas.push_back(alumnos);
    BaseDatos universidad(tablas_nombres, tablas);
    Registro nuevo_registro1({"Nombre", "LU", "Ano"}, {datoStr("March"), datoStr("64/9"), datoStr("2017")});
    Registro nuevo_registro2({"Nombre", "LU", "Ano"}, {datoStr("Ciro"), datoStr("45/16"), datoStr("2017")});
    Registro nuevo_registro3({"Nombre", "LU", "Ano"}, {datoStr("Fran"), datoStr("76/15"), datoStr("2017")});
    Registro nuevo_registro4({"Nombre", "LU", "Ano"}, {datoStr("Pepe"), datoStr("89/16"), datoStr("2017")});
    universidad.agregar_registro("Alumnos",nuevo_registro1);
    universidad.agregar_registro("Alumnos",nuevo_registro2);
    universidad.agregar_registro("Alumnos",nuevo_registro3);
    universidad.agregar_registro("Alumnos",nuevo_registro4);
    Restricciones buscar_ciro ({"Nombre"},datoStr("Ciro"),false);
    Criterio criterio_valido;
    criterio_valido.push_back(buscar_ciro);
    EXPECT_EQ(universidad.criterio_valido("Alumnos", criterio_valido),true);
    }

TEST_F(BasedatosTests, criterio_no_valido) {
    vector<string> tablas_nombres;
    tablas_nombres.push_back("Alumnos");
    vector<Tabla> tablas;
    Tabla alumnos({"Nombre", "LU", "Ano"},
                  {"LU"},
                  {datoStr(""), datoStr (""), datoNat(0)});
    tablas.push_back(alumnos);
    BaseDatos universidad(tablas_nombres, tablas);
    Registro nuevo_registro1({"Nombre", "LU", "Ano"}, {datoStr("March"), datoStr("64/9"), datoStr("2017")});
    Registro nuevo_registro2({"Nombre", "LU", "Ano"}, {datoStr("Ciro"), datoStr("45/16"), datoStr("2017")});
    Registro nuevo_registro3({"Nombre", "LU", "Ano"}, {datoStr("Fran"), datoStr("76/15"), datoStr("2017")});
    Registro nuevo_registro4({"Nombre", "LU", "Ano"}, {datoStr("Pepe"), datoStr("89/16"), datoStr("2017")});
    universidad.agregar_registro("Alumnos",nuevo_registro1);
    universidad.agregar_registro("Alumnos",nuevo_registro2);
    universidad.agregar_registro("Alumnos",nuevo_registro3);
    universidad.agregar_registro("Alumnos",nuevo_registro4);
    Restricciones buscar_ciro ({"Nombre"},datoNat(0),false);
    Criterio criterio_valido;
    criterio_valido.push_back(buscar_ciro);
    EXPECT_EQ(universidad.criterio_valido("Alumnos", criterio_valido),false);
}