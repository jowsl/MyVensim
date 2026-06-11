#include "functional_tests.h"
#include "../../src/model.h"  // APENAS INTERFACE
#include "../../src/system.h" // APENAS INTERFACE
#include "../../src/flow.h"   // APENAS INTERFACE
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

// ====================================================================
// BASE DE FLUXO PARA TESTES (Substitui a necessidade do FlowImpl)
// ====================================================================
class TestFlow : public Flow {
protected:
    System* origin;
    System* destination;
    string name;

public:
    TestFlow(string name = "") : name(name), origin(nullptr), destination(nullptr) {}
    virtual ~TestFlow() {}

    void setOrigin(System* o) override { origin = o; }
    System* getOrigin() const override { return origin; }
    
    void setDestination(System* d) override { destination = d; }
    System* getDestination() const override { return destination; }
    
    void connect(System* o, System* d) override { origin = o; destination = d; }
    
    void setName(string n) override { name = n; }
    string getName() const override { return name; }
    
    // Mantém virtual puro para as classes matemáticas implementarem
    virtual double execute() = 0; 
};

// ====================================================================
// CLASSES MATEMÁTICAS (Agora herdam do TestFlow)
// ====================================================================

/**
 * @brief Exponential flow implementation.
 * Transfers a percentage of the origin system value to the destination.
 */
class ExponentialFlow : public TestFlow {
public:
    ExponentialFlow(string name = "") : TestFlow(name) {}
    
    double execute() override {
        if (getOrigin() != nullptr) {
            return 0.01 * getOrigin()->getValue();
        }
        return 0.0;
    }
};

/**
 * @brief Logistic flow implementation.
 * Computes a logistic transfer based on the destination system value.
 */
class LogisticFlow : public TestFlow {
public:
    LogisticFlow(string name = "") : TestFlow(name) {}
    
    double execute() override {
        if (getDestination() != nullptr) {
            double p2 = getDestination()->getValue();
            return 0.01 * p2 * (1.0 - p2 / 70.0);
        }
        return 0.0;
    }
};

/**
 * @brief Complex flow implementation.
 * Uses the same transfer rule as the exponential flow for complex network tests.
 */
class ComplexFlow : public TestFlow {
public:
    ComplexFlow(string name = "") : TestFlow(name) {}
    
    double execute() override {
        if (getOrigin() != nullptr) {
            return 0.01 * getOrigin()->getValue();
        }
        return 0.0;
    }
};

// ====================================================================
// TESTES FUNCIONAIS
// ====================================================================

void exponentialFunctionalTest() {
    cout << "MODELO EXPONENCIAL" << endl;

    // Acessa o modelo global usando apenas a interface
    Model& model = Model::createModel();
    model.clear();

    System& pop1 = model.createSystem("pop1", 100.0);
    System& pop2 = model.createSystem("pop2", 0.0);

    model.createFlow<ExponentialFlow>("exponencial", &pop1, &pop2);

    model.execute(0, 100);

    assert((int)round(pop1.getValue() * 10000) == 366032);
    assert((int)round(pop2.getValue() * 10000) == 633968);
    cout << "POP1 :" << (int)round(pop1.getValue() * 10000) << endl;
    cout << "POP2 :" << (int)round(pop2.getValue() * 10000) << endl;

    cout << "Teste Exponencial: OK!\n" << endl;
}

void logisticalFunctionalTest() {
    cout << "TESTES: MODELO LOGISTICO" << endl;

    Model& model = Model::createModel();
    model.clear();

    System& p1 = model.createSystem("p1", 100.0);
    System& p2 = model.createSystem("p2", 10.0);

    model.createFlow<LogisticFlow>("logistica", &p1, &p2);

    model.execute(0, 100);

    assert((int)round(p1.getValue() * 10000) == 882167);
    assert((int)round(p2.getValue() * 10000) == 217833);
    cout << "P1 :" << (int)round(p1.getValue() * 10000) << endl;
    cout << "P2 :" << (int)round(p2.getValue() * 10000) << endl;

    cout << "Teste Logistico: OK!\n" << endl;
}

void complexFunctionalTest() {
    cout << "TESTES: MODELO COMPLEXO" << endl;

    Model& model = Model::createModel();
    model.clear();

    System& q1 = model.createSystem("Q1", 100.0);
    System& q2 = model.createSystem("Q2", 0.0);
    System& q3 = model.createSystem("Q3", 100.0);
    System& q4 = model.createSystem("Q4", 0.0);
    System& q5 = model.createSystem("Q5", 0.0);

    model.createFlow<ComplexFlow>("f", &q1, &q2);
    model.createFlow<ComplexFlow>("g", &q1, &q3);
    model.createFlow<ComplexFlow>("r", &q2, &q5);
    model.createFlow<ComplexFlow>("t", &q2, &q3);
    model.createFlow<ComplexFlow>("u", &q3, &q4);
    model.createFlow<ComplexFlow>("v", &q4, &q1);

    model.execute(0, 100);

    assert((int)round(q1.getValue() * 10000) == 318513);
    assert((int)round(q2.getValue() * 10000) == 184003);
    assert((int)round(q3.getValue() * 10000) == 771143);
    assert((int)round(q4.getValue() * 10000) == 561728);
    assert((int)round(q5.getValue() * 10000) == 164612);

    cout << "Q1 :" << (int)round(q1.getValue() * 10000) << endl;
    cout << "Q2 :" << (int)round(q2.getValue() * 10000) << endl;
    cout << "Q3 :" << (int)round(q3.getValue() * 10000) << endl;
    cout << "Q4 :" << (int)round(q4.getValue() * 10000) << endl;
    cout << "Q5 :" << (int)round(q5.getValue() * 10000) << endl;

    cout << "Teste Complexo: OK!\n" << endl;
}