#include "gtest/gtest.h"
#include "../src/Dato.h"
#include "../src/Registro.h"
#include <vector>

using namespace std;

TEST(registro_test, generadores) {
    Registro({"LU", "Año", "Nombre", "Carrera"}, {datoNat(182), datoNat(18), datoStr("March"), datoStr("Computacion")});
    Registro({}, {});
}

TEST(registro_test, campos) {
    Registro r({"A", "B", "C"}, {datoNat(1), datoNat(2), datoNat(3)});
    Registro r2({}, {});

    EXPECT_EQ(r.campos(), vector<string>({"A", "B", "C"}));
    EXPECT_EQ(r2.campos(), vector<string>());
}

TEST(registro_test, dato) {
    Registro r({"LU", "Año", "Nombre", "Carrera"}, {datoNat(182), datoNat(18), datoStr("March"), datoStr("Computacion")});

    EXPECT_EQ(r.dato("LU").esNat(), true);
    EXPECT_EQ(r.dato("LU").esString(), false);
    EXPECT_EQ(r.dato("LU").valorNat(), 182);
    EXPECT_EQ(r.dato("Nombre").esNat(), false);
    EXPECT_EQ(r.dato("Nombre").esString(), true);
    EXPECT_EQ(r.dato("Nombre").valorStr(), "March");
}

TEST(registro_test, ig_obs) {
    Registro r1({"LU", "Año"}, {datoNat(1), datoStr("a")});
    Registro r2({"LU", "Año"}, {datoNat(1), datoStr("a")});

    // Iguales
    EXPECT_TRUE(r1 == r2);

    // Distinto orden
    Registro r3({"Año", "LU"}, {datoStr("a"), datoNat(1)});
    EXPECT_TRUE(r1 == r3);

    // Distinto tipo
    Registro r4({"Año", "LU"}, {datoNat(2), datoNat(1)});
    EXPECT_FALSE(r1 == r4);

    // Distinto valor
    Registro r5({"LU", "Año"}, {datoNat(2), datoStr("a")});
    EXPECT_FALSE(r1 == r5);

    // Más campos
    Registro r6({"LU", "Año", "Nombre"}, 
            {datoNat(2), datoStr("a"), datoStr("b")});
    EXPECT_FALSE(r1 == r6);
}
