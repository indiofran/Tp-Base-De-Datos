//
// Created by Francisco on 03/09/2017.
//
#include "gtest/gtest.h"
#include "../src/BaseDatos.h"

using namespace std;

class BasedatosTests : public ::testing::Test {
protected:
    BasedatosTests() : alumnos({"LU", "Año", "Nombre", "Carrera"},
                         { "LU"},
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

TEST_F(BasedatosTests, criterio_valido) {
    vector<string> tablas_nombres;
    tablas_nombres.push_back("Alumnos");
    vector<Tabla> tablas;
    Tabla tabla_alumnos({"Nombre", "LU", "Ano"},
                  {"LU"},
                  {datoStr(""), datoStr (""), datoNat(0)});
    tablas.push_back(tabla_alumnos);
    BaseDatos universidad(tablas_nombres, tablas);
    Registro nuevo_registro1({"Nombre", "LU", "Ano"}, {datoStr("March"), datoStr("64/9"), datoStr("2017")});
    Registro nuevo_registro2({"Nombre", "LU", "Ano"}, {datoStr("Ciro"), datoStr("45/16"), datoStr("2017")});
    Registro nuevo_registro3({"Nombre", "LU", "Ano"}, {datoStr("Fran"), datoStr("76/15"), datoStr("2017")});
    Registro nuevo_registro4({"Nombre", "LU", "Ano"}, {datoStr("Pepe"), datoStr("89/16"), datoStr("2017")});
    universidad.agregar_registro("Alumnos",nuevo_registro1);
    universidad.agregar_registro("Alumnos",nuevo_registro2);
    universidad.agregar_registro("Alumnos",nuevo_registro3);
    universidad.agregar_registro("Alumnos",nuevo_registro4);
    Restricciones buscar_ciro ("Nombre",datoStr("Ciro"),false);
    Criterio criterio_valido;
    criterio_valido.push_back(buscar_ciro);
    EXPECT_EQ(universidad.criterio_valido("Alumnos", criterio_valido),true);
    }

TEST_F(BasedatosTests, criterio_no_valido) {
    vector<string> tablas_nombres;
    tablas_nombres.push_back("Alumnos");
    vector<Tabla> tablas;
    Tabla tabla_alumnos({"Nombre", "LU", "Ano"},
                  {"LU"},
                  {datoStr(""), datoStr (""), datoNat(0)});
    tablas.push_back(tabla_alumnos);
    BaseDatos universidad(tablas_nombres, tablas);
    Registro nuevo_registro1({"Nombre", "LU", "Ano"}, {datoStr("March"), datoStr("64/9"), datoStr("2017")});
    Registro nuevo_registro2({"Nombre", "LU", "Ano"}, {datoStr("Ciro"), datoStr("45/16"), datoStr("2017")});
    Registro nuevo_registro3({"Nombre", "LU", "Ano"}, {datoStr("Fran"), datoStr("76/15"), datoStr("2017")});
    Registro nuevo_registro4({"Nombre", "LU", "Ano"}, {datoStr("Pepe"), datoStr("89/16"), datoStr("2017")});
    universidad.agregar_registro("Alumnos",nuevo_registro1);
    universidad.agregar_registro("Alumnos",nuevo_registro2);
    universidad.agregar_registro("Alumnos",nuevo_registro3);
    universidad.agregar_registro("Alumnos",nuevo_registro4);
    Restricciones buscar_ciro ("Nombre",datoNat(0),false);
    Criterio criterio_valido;
    criterio_valido.push_back(buscar_ciro);
    EXPECT_EQ(universidad.criterio_valido("Alumnos", criterio_valido),false);
}

TEST_F(BasedatosTests, Busqueda){
    BaseDatos universidad;
    universidad.agregar_tabla("Alumnos", alumnos);
    Registro r0({"LU", "Año", "Nombre", "Carrera"}, {datoNat(125), datoNat(12), datoStr("Ciro"), datoStr("Computacion")});
    Registro r1({"LU", "Año", "Nombre", "Carrera"}, {datoNat(250), datoNat(10), datoStr("Fran"), datoStr("Matematica")});
    Registro r2({"LU", "Año", "Nombre", "Carrera"}, {datoNat(352), datoNat(15), datoStr("Julian"), datoStr("Biologia")});
    Registro r3({"LU", "Año", "Nombre", "Carrera"}, {datoNat(512), datoNat(16), datoStr("Pepe"), datoStr("Computacion")});
    universidad.agregar_registro("Alumnos",r0);
    universidad.agregar_registro("Alumnos",r1);
    universidad.agregar_registro("Alumnos",r2);
    universidad.agregar_registro("Alumnos",r3);
    Restricciones buscar_ciro("Nombre",datoStr("Ciro"),true);
    Criterio criterio_bucasr_ciro;
    criterio_bucasr_ciro.push_back(buscar_ciro);
    Tabla alumno_ciro({"LU", "Año", "Nombre", "Carrera"},{"LU"},{ datoNat(0), datoNat(0), datoStr(""), datoStr("")});
    alumno_ciro.agregarRegistro(r0);
    EXPECT_EQ(universidad.busqueda("Alumnos", criterio_bucasr_ciro),alumno_ciro);
    Restricciones buscar_computacion("Carrera",datoStr("Computacion"),true);
    Criterio criterio_ciro_computacion;
    criterio_ciro_computacion.push_back(buscar_ciro);
    criterio_ciro_computacion.push_back(buscar_computacion);
    EXPECT_EQ(universidad.busqueda("Alumnos", criterio_ciro_computacion),alumno_ciro);
    Restricciones buscar_todos_menos_ciro("Nombre",datoStr("Ciro"),false);
    Criterio todos_menos_ciro;
    todos_menos_ciro.push_back(buscar_todos_menos_ciro);
    Tabla tabla_menos_ciro({"LU", "Año", "Nombre", "Carrera"},{"LU"},{ datoNat(0), datoNat(0), datoStr(""), datoStr("")});
    tabla_menos_ciro.agregarRegistro(r1);
    tabla_menos_ciro.agregarRegistro(r2);
    tabla_menos_ciro.agregarRegistro(r3);
    EXPECT_EQ(universidad.busqueda("Alumnos", todos_menos_ciro),tabla_menos_ciro);
    Criterio todos_menos_ciro_computacion;
    todos_menos_ciro.push_back(buscar_computacion);
    todos_menos_ciro.push_back(buscar_todos_menos_ciro);
    Tabla tabla_menos_ciro_computacion({"LU", "Año", "Nombre", "Carrera"},{"LU"},{ datoNat(0), datoNat(0), datoStr(""), datoStr("")});
    tabla_menos_ciro_computacion.agregarRegistro(r3);
    EXPECT_EQ(universidad.busqueda("Alumnos", todos_menos_ciro),tabla_menos_ciro_computacion);
    Criterio nada;
    Restricciones buscar_no_computacion("Carrera",datoStr("Computacion"),false);
    nada.push_back(buscar_computacion);
    nada.push_back(buscar_no_computacion);
    Tabla vacia({"LU", "Año", "Nombre", "Carrera"},{"LU"},{ datoNat(0), datoNat(0), datoStr(""), datoStr("")});
    EXPECT_EQ(universidad.busqueda("Alumnos", nada),vacia);
    nada.push_back(buscar_ciro);
    EXPECT_EQ(universidad.busqueda("Alumnos", nada),vacia);
    universidad.busqueda("Alumnos", nada);
    EXPECT_EQ(universidad.criterio_mas_utilizado(), nada);
}