#include "unit_flow.h"
#include "../../src/flowImpl.h"
#include "../../src/systemImpl.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

// ─────────────────────────────────────────────
// TestFlow: subclasse concreta mínima de FlowImpl
// necessária pois FlowImpl::execute() é virtual puro
// ─────────────────────────────────────────────
/**
 * @brief Minimal concrete subclass used to instantiate FlowImpl in tests.
 *
 * execute() returns a fixed constant so tests are deterministic
 * and independent of any real flow equation.
 */
class TestFlow : public FlowImpl {
public:
    /**
     * @brief Constructs a TestFlow with optional name, origin and destination.
     */
    TestFlow(string name = "", System* origin = nullptr, System* destination = nullptr)
        : FlowImpl(name, origin, destination) {}

    /**
     * @brief Returns a fixed value of 1.0 for all test calls.
     */
    double execute() override { return 1.0; }
};

// ─────────────────────────────────────────────
// UnitFlow: friend class para acessar os
// atributos protegidos de FlowImpl diretamente
// ─────────────────────────────────────────────
/**
 * @brief Friend test class that accesses FlowImpl internals.
 *
 * Declared as friend in FlowImpl, so its static methods can
 * read the protected 'name', 'origin' and 'destination' fields directly.
 */
class UnitFlow {
public:
    /** @brief Returns the raw protected 'name' field. */
    static string getName(const FlowImpl& f)        { return f.name; }
    /** @brief Returns the raw protected 'origin' pointer. */
    static System* getOrigin(const FlowImpl& f)     { return f.origin; }
    /** @brief Returns the raw protected 'destination' pointer. */
    static System* getDestination(const FlowImpl& f){ return f.destination; }
};

// ─────────────────────────────────────────────
// Test implementations
// ─────────────────────────────────────────────

void testFlowDefaultConstructor() {
    TestFlow f;

    // Valida via friend class (acesso direto aos atributos protegidos)
    assert(UnitFlow::getName(f) == "");
    assert(UnitFlow::getOrigin(f) == nullptr);
    assert(UnitFlow::getDestination(f) == nullptr);

    // Valida via interface pública
    assert(f.getName() == "");
    assert(f.getOrigin() == nullptr);
    assert(f.getDestination() == nullptr);

    cout << "  [OK] test Flow Default Constructor" << endl;
}

void testFlowParameterizedConstructor() {
    SystemImpl s1("A", 10.0);
    SystemImpl s2("B", 20.0);

    TestFlow f("transfer", &s1, &s2);

    assert(UnitFlow::getName(f) == "transfer");
    assert(UnitFlow::getOrigin(f) == &s1);
    assert(UnitFlow::getDestination(f) == &s2);

    assert(f.getName() == "transfer");
    assert(f.getOrigin() == &s1);
    assert(f.getDestination() == &s2);

    cout << "  [OK] test Flow Parameterized Constructor" << endl;
}

void testFlowCopyConstructor() {
    SystemImpl s1("orig", 5.0);
    SystemImpl s2("dest", 15.0);

    TestFlow original("flow1", &s1, &s2);
    TestFlow copy(original);

    // A cópia deve referenciar os mesmos sistemas
    assert(copy.getName() == "flow1");
    assert(copy.getOrigin() == &s1);
    assert(copy.getDestination() == &s2);

    // Modificar o nome da cópia não deve afetar o original
    copy.setName("flow_copy");
    assert(original.getName() == "flow1");

    cout << "  [OK] test Flow Copy Constructor" << endl;
}

void testFlowAssignmentOperator() {
    SystemImpl s1("x", 1.0);
    SystemImpl s2("y", 2.0);
    SystemImpl s3("z", 3.0);

    TestFlow f1("flowA", &s1, &s2);
    TestFlow f2("flowB", &s3, nullptr);

    f2 = f1;

    assert(f2.getName() == "flowA");
    assert(f2.getOrigin() == &s1);
    assert(f2.getDestination() == &s2);

    // Auto-atribuição: objeto não deve ser corrompido
    f1 = f1;
    assert(f1.getName() == "flowA");
    assert(f1.getOrigin() == &s1);
    assert(f1.getDestination() == &s2);

    cout << "  [OK] test Flow Assignment Operator" << endl;
}

void testFlowSetGetName() {
    TestFlow f;

    f.setName("evaporation");
    assert(f.getName() == "evaporation");

    f.setName("precipitation");
    assert(f.getName() == "precipitation");

    f.setName("");
    assert(f.getName() == "");

    cout << "  [OK] test Flow Set/Get Name" << endl;
}

void testFlowSetGetOrigin() {
    SystemImpl s1("tank", 50.0);
    TestFlow f;

    assert(f.getOrigin() == nullptr);

    f.setOrigin(&s1);
    assert(f.getOrigin() == &s1);

    // Reseta para nullptr
    f.setOrigin(nullptr);
    assert(f.getOrigin() == nullptr);

    cout << "  [OK] test Flow Set/Get Origin" << endl;
}

void testFlowSetGetDestination() {
    SystemImpl s1("ocean", 1000.0);
    TestFlow f;

    assert(f.getDestination() == nullptr);

    f.setDestination(&s1);
    assert(f.getDestination() == &s1);

    f.setDestination(nullptr);
    assert(f.getDestination() == nullptr);

    cout << "  [OK] test Flow Set/Get Destination" << endl;
}

void testFlowConnect() {
    SystemImpl s1("source", 100.0);
    SystemImpl s2("sink",     0.0);
    SystemImpl s3("mid",     50.0);

    TestFlow f;

    // Conecta origem e destino em um único chamado
    f.connect(&s1, &s2);
    assert(f.getOrigin()      == &s1);
    assert(f.getDestination() == &s2);

    // Reconectar deve sobrescrever a conexão anterior
    f.connect(&s3, &s1);
    assert(f.getOrigin()      == &s3);
    assert(f.getDestination() == &s1);

    // Conectar com nullptr é permitido (fluxo sem origem/destino)
    f.connect(nullptr, nullptr);
    assert(f.getOrigin()      == nullptr);
    assert(f.getDestination() == nullptr);

    cout << "  [OK] test Flow Connect" << endl;
}

void runFlowTests() {
    cout << "\n=== Unit Tests: FlowImpl ===" << endl;

    testFlowDefaultConstructor();
    testFlowParameterizedConstructor();
    testFlowCopyConstructor();
    testFlowAssignmentOperator();
    testFlowSetGetName();
    testFlowSetGetOrigin();
    testFlowSetGetDestination();
    testFlowConnect();

    cout << "=== FlowImpl: All tests passed! ===" << endl;
}
