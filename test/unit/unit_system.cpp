#include "unit_system.h"
#include "../../src/systemImpl.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

// UnitSystem: friend class para acessar os
// atributos protegidos de SystemImpl diretamente
/**
 * @brief Friend test class that accesses SystemImpl internals.
 *
 * Declared as friend in SystemImpl, so its static methods can
 * read the protected 'name' and 'value' fields directly.
 */
class UnitSystem {
public:
    /**
     * @brief Returns the raw protected 'name' field of a SystemImpl.
     * @param s Reference to the SystemImpl under test.
     * @return The internal name string.
     */
    static string getName(const SystemImpl& s) { return s.name; }

    /**
     * @brief Returns the raw protected 'value' field of a SystemImpl.
     * @param s Reference to the SystemImpl under test.
     * @return The internal double value.
     */
    static double getValue(const SystemImpl& s) { return s.value; }
};

// Test implementations

void testSystemDefaultConstructor() {
    SystemImpl s;

    // Acessa atributos protegidos via friend class
    assert(UnitSystem::getName(s) == "");
    assert(UnitSystem::getValue(s) == 0.0);

    // Também valida via interface pública
    assert(s.getName() == "");
    assert(s.getValue() == 0.0);

    cout << "  [OK] test System Default Constructor" << endl;
}

void testSystemParameterizedConstructor() {
    SystemImpl s("reservoir", 200.5);

    assert(UnitSystem::getName(s) == "reservoir");
    assert(UnitSystem::getValue(s) == 200.5);

    assert(s.getName() == "reservoir");
    assert(s.getValue() == 200.5);

    cout << "  [OK] test System Parameterized Constructor" << endl;
}

void testSystemCopyConstructor() {
    SystemImpl original("source", 42.0);
    SystemImpl copy(original);

    // Cópia deve ter os mesmos valores
    assert(copy.getName() == "source");
    assert(copy.getValue() == 42.0);

    // Modificar a cópia não deve afetar o original
    copy.setName("modified");
    copy.setValue(99.0);

    assert(original.getName() == "source");
    assert(original.getValue() == 42.0);

    cout << "  [OK] test System Copy Constructor" << endl;
}

void testSystemAssignmentOperator() {
    SystemImpl s1("alpha", 10.0);
    SystemImpl s2("beta", 20.0);

    s2 = s1;

    assert(s2.getName() == "alpha");
    assert(s2.getValue() == 10.0);

    // Auto-atribuição: não deve alterar o objeto
    s1 = s1;
    assert(s1.getName() == "alpha");
    assert(s1.getValue() == 10.0);

    cout << "  [OK] test System Assignment Operator" << endl;
}

void testSystemSetGetName() {
    SystemImpl s;

    s.setName("population");
    assert(s.getName() == "population");

    // Sobrescreve o nome
    s.setName("biomass");
    assert(s.getName() == "biomass");

    // Nome vazio é válido
    s.setName("");
    assert(s.getName() == "");

    cout << "  [OK] test System Set/Get Name" << endl;
}

void testSystemSetGetValue() {
    SystemImpl s;

    s.setValue(100.0);
    assert(s.getValue() == 100.0);

    // Valor negativo
    s.setValue(-50.75);
    assert(s.getValue() == -50.75);

    // Zero explícito
    s.setValue(0.0);
    assert(s.getValue() == 0.0);

    // Valor decimal de precisão
    s.setValue(3.14159265);
    assert(s.getValue() == 3.14159265);

    cout << "  [OK] test System Set/Get Value" << endl;
}

void runSystemTests() {
    cout << "\n=== Unit Tests: SystemImpl ===" << endl;

    testSystemDefaultConstructor();
    testSystemParameterizedConstructor();
    testSystemCopyConstructor();
    testSystemAssignmentOperator();
    testSystemSetGetName();
    testSystemSetGetValue();

    cout << "=== SystemImpl: All tests passed! ===" << endl;
}
