#include "unit_model.h"
#include "../../src/modelImpl.h"
#include "../../src/systemImpl.h"
#include "../../src/flowImpl.h"
#include <cassert>
#include <iostream>
#include <cmath>

using namespace std;

// ModelTestFlow: subclasse concreta mínima de FlowImpl
// necessária pois FlowImpl::execute() é virtual puro.
/**
 * @brief Minimal concrete flow used to instantiate FlowImpl inside model tests.
 *
 * Implements a simple exponential-style equation (0.01 * origin value)
 * so that testModelExecuteExponential can validate the same acceptance
 * criteria used in the functional tests.
 */
class ModelTestFlow : public FlowImpl {
public:
    /**
     * @brief Constructs a ModelTestFlow with optional name, origin, destination.
     */
    ModelTestFlow(string name = "", System* origin = nullptr, System* destination = nullptr)
        : FlowImpl(name, origin, destination) {}

    /**
     * @brief Returns 0.01 * origin value, or 0.0 if origin is null.
     */
    double execute() override {
        if (getOrigin() != nullptr) {
            return 0.01 * getOrigin()->getValue();
        }
        return 0.0;
    }
};

// UnitModel: friend class para acessar os
// atributos protegidos de ModelImpl diretamente
/**
 * @brief Friend test class that accesses ModelImpl internals.
 *
 * Declared as friend in ModelImpl, so its static methods can
 * read the protected 'systems' and 'flows' vectors directly.
 */
class UnitModel {
public:
    /** @brief Returns the number of systems stored inside the model. */
    static size_t systemCount(const ModelImpl& m) { return m.systems.size(); }
    /** @brief Returns the number of flows stored inside the model.   */
    static size_t flowCount  (const ModelImpl& m) { return m.flows.size();   }
    /** @brief Returns the system pointer at a given index.           */
    static System* getSystem(const ModelImpl& m, size_t i) { return m.systems[i]; }
    /** @brief Returns the flow pointer at a given index.             */
    static Flow*   getFlow  (const ModelImpl& m, size_t i) { return m.flows[i];   }
};

// Test implementations

void testModelDefaultConstructor() {
    ModelImpl model;

    // O modelo recém-criado não deve conter sistemas nem fluxos
    assert(UnitModel::systemCount(model) == 0);
    assert(UnitModel::flowCount(model)   == 0);

    // Iteradores begin == end para coleções vazias
    assert(model.beginSystems() == model.endSystems());
    assert(model.beginFlows()   == model.endFlows());

    cout << "  [OK] test Model Default Constructor" << endl;
}

void testModelCopyConstructor() {
    ModelImpl original;
    SystemImpl s("s1", 10.0);
    ModelTestFlow f("f1");

    original.add(&s);
    original.add(&f);

    ModelImpl copy(original);

    // A cópia deve conter os mesmos ponteiros
    assert(UnitModel::systemCount(copy) == 1);
    assert(UnitModel::flowCount(copy)   == 1);
    assert(UnitModel::getSystem(copy, 0) == &s);
    assert(UnitModel::getFlow(copy, 0)   == &f);

    // O original não deve ser afetado
    assert(UnitModel::systemCount(original) == 1);
    assert(UnitModel::flowCount(original)   == 1);

    cout << "  [OK] test Model Copy Constructor" << endl;
}

void testModelAssignmentOperator() {
    ModelImpl m1, m2;
    SystemImpl s1("sA", 5.0);
    SystemImpl s2("sB", 8.0);

    m1.add(&s1);
    m2.add(&s2);

    m2 = m1;

    assert(UnitModel::systemCount(m2) == 1);
    assert(UnitModel::getSystem(m2, 0) == &s1);

    // Auto-atribuição: modelo não deve ser corrompido
    m1 = m1;
    assert(UnitModel::systemCount(m1) == 1);
    assert(UnitModel::getSystem(m1, 0) == &s1);

    cout << "  [OK] test Model Assignment Operator" << endl;
}

void testModelAddSystem() {
    ModelImpl model;
    SystemImpl s1("Q1", 100.0);
    SystemImpl s2("Q2",   0.0);

    model.add(&s1);
    assert(UnitModel::systemCount(model) == 1);
    assert(UnitModel::getSystem(model, 0) == &s1);

    model.add(&s2);
    assert(UnitModel::systemCount(model) == 2);
    assert(UnitModel::getSystem(model, 1) == &s2);

    cout << "  [OK] test Model Add System" << endl;
}

void testModelAddFlow() {
    ModelImpl model;
    ModelTestFlow f1("flow1");
    ModelTestFlow f2("flow2");

    model.add(&f1);
    assert(UnitModel::flowCount(model) == 1);
    assert(UnitModel::getFlow(model, 0) == &f1);

    model.add(&f2);
    assert(UnitModel::flowCount(model) == 2);
    assert(UnitModel::getFlow(model, 1) == &f2);

    cout << "  [OK] test Model Add Flow" << endl;
}

void testModelSystemIterators() {
    ModelImpl model;
    SystemImpl s1("sys1", 1.0);
    SystemImpl s2("sys2", 2.0);
    SystemImpl s3("sys3", 3.0);

    model.add(&s1);
    model.add(&s2);
    model.add(&s3);

    // Itera e verifica a ordem de inserção
    auto it = model.beginSystems();
    assert(*it == &s1); ++it;
    assert(*it == &s2); ++it;
    assert(*it == &s3); ++it;
    assert(it == model.endSystems());

    cout << "  [OK] test Model System Iterators" << endl;
}

void testModelFlowIterators() {
    ModelImpl model;
    ModelTestFlow f1("f1");
    ModelTestFlow f2("f2");

    model.add(&f1);
    model.add(&f2);

    auto it = model.beginFlows();
    assert(*it == &f1); ++it;
    assert(*it == &f2); ++it;
    assert(it == model.endFlows());

    cout << "  [OK] test Model Flow Iterators" << endl;
}

void testModelExecuteExponential() {
    // Reproduz o mesmo cenário do teste funcional exponencial
    // para garantir que execute() produz os valores esperados.
    ModelImpl model;
    SystemImpl pop1("pop1", 100.0);
    SystemImpl pop2("pop2",   0.0);
    ModelTestFlow expFlow("exp");

    expFlow.connect(&pop1, &pop2);
    model.add(&pop1);
    model.add(&pop2);
    model.add(&expFlow);

    model.execute(0, 100);

    // Critérios de aceitação idênticos aos do teste funcional
    assert((int)round(pop1.getValue() * 10000) == 366032);
    assert((int)round(pop2.getValue() * 10000) == 633968);

    cout << "  [OK] test Model Execute Exponential" << endl;
}

void testModelExecuteNullOrigin() {
    // Fluxo sem origem: apenas o destino deve ser atualizado
    ModelImpl model;
    SystemImpl dest("dest", 0.0);
    ModelTestFlow f("noOrigin", nullptr, &dest);

    model.add(&dest);
    model.add(&f);

    // execute() retorna 0.0 quando origin == nullptr,
    // portanto o destino permanece inalterado.
    model.execute(0, 5);

    assert(dest.getValue() == 0.0);

    cout << "  [OK] test Model Execute Null Origin" << endl;
}

void testModelExecuteNullDestination() {
    // Fluxo sem destino: apenas a origem deve ser subtraída
    ModelImpl model;
    SystemImpl orig("orig", 100.0);

    // Subclasse que retorna sempre 10.0 para tornar o teste determinístico
    class FixedFlow : public FlowImpl {
    public:
        FixedFlow(System* o) : FlowImpl("fixed", o, nullptr) {}
        double execute() override { return 10.0; }
    };

    FixedFlow f(&orig);

    model.add(&orig);
    model.add(&f);

    // Após 1 passo: orig = 100 - 10 = 90; sem destino não há crash
    model.execute(0, 1);

    assert(orig.getValue() == 90.0);

    cout << "  [OK] test Model Execute Null Destination" << endl;
}

void runModelTests() {
    cout << "\n=== Unit Tests: ModelImpl ===" << endl;

    testModelDefaultConstructor();
    testModelCopyConstructor();
    testModelAssignmentOperator();
    testModelAddSystem();
    testModelAddFlow();
    testModelSystemIterators();
    testModelFlowIterators();
    testModelExecuteExponential();
    testModelExecuteNullOrigin();
    testModelExecuteNullDestination();

    cout << "=== ModelImpl: All tests passed! ===" << endl;
}
