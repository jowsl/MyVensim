#include "unit_model.h"
#include "../../src/modelImpl.h"
#include "../../src/system.h" // Inclui apenas a INTERFACE!
#include "../../src/flow.h"   // Inclui apenas a INTERFACE!
#include <cassert>
#include <iostream>

using namespace std;

/**
 * @brief MockSystem implementa a interface System.
 * Usado exclusivamente para injetar valores previsíveis no Model.
 */
class MockSystem : public System {
public:
    double value; // Público para facilitar a asserção no teste
    string name;

    MockSystem(string n = "", double v = 0.0) : name(n), value(v) {}
    ~MockSystem() {}

    void setValue(double v) override { value = v; }
    double getValue() const override { return value; }
    void setName(string n) override { name = n; }
    string getName() const override { return name; }
};

/**
 * @brief MockFlow implementa a interface Flow.
 * Retorna um valor fixo no execute() para não depender de matemática complexa.
 */
class MockFlow : public Flow {
public:
    System* origin;
    System* destination;
    double returnValue; // Valor fixo que o fluxo vai transferir

    MockFlow(System* o = nullptr, System* d = nullptr, double ret = 10.0) 
        : origin(o), destination(d), returnValue(ret) {}
    ~MockFlow() {}

    void setOrigin(System* o) override { origin = o; }
    System* getOrigin() const override { return origin; }
    void setDestination(System* d) override { destination = d; }
    System* getDestination() const override { return destination; }
    void connect(System* o, System* d) override { origin = o; destination = d; }
    void setName(string n) override {}
    string getName() const override { return "Mock"; }
    
    // Retorna o valor fixo injetado no construtor
    double execute() override { return returnValue; } 
};


class UnitModel {
public:
    static void runTestModelDefaultConstructor() {
        ModelImpl model;
        assert(model.systems.size() == 0);
        assert(model.flows.size() == 0);
        cout << "  OK test Model Default Constructor" << endl;
    }

    static void runTestModelCopyConstructor() {
        ModelImpl model1;
        MockSystem s1("s1", 10.0);
        model1.systems.push_back(&s1);

        ModelImpl model2(model1);
        assert(model2.systems.size() == 1);
        assert(model2.systems[0] == &s1);
        cout << "  OK test Model Copy Constructor" << endl;
    }

    static void runTestModelAssignmentOperator() {
        ModelImpl model1;
        MockSystem s1("s1", 10.0);
        model1.systems.push_back(&s1);

        ModelImpl model2;
        model2 = model1;
        
        assert(model2.systems.size() == 1);
        assert(model2.systems[0] == &s1);
        cout << "  OK test Model Assignment Operator" << endl;
    }

    static void runTestModelAddSystem() {
        ModelImpl model;
        MockSystem s1("s1", 0.0);
        model.add(&s1);
        assert(model.systems.size() == 1);
        assert(model.systems[0] == &s1);
        cout << "  OK test Model Add System" << endl;
    }

    static void runTestModelAddFlow() {
        ModelImpl model;
        MockFlow f1;
        model.add(&f1);
        assert(model.flows.size() == 1);
        assert(model.flows[0] == &f1);
        cout << "  OK test Model Add Flow" << endl;
    }

    static void runTestModelSystemIterators() {
        ModelImpl model;
        MockSystem s1;
        model.systems.push_back(&s1);
        assert(*(model.beginSystems()) == &s1);
        cout << "  OK test Model System Iterators" << endl;
    }

    static void runTestModelFlowIterators() {
        ModelImpl model;
        MockFlow f1;
        model.flows.push_back(&f1);
        assert(*(model.beginFlows()) == &f1);
        cout << "  OK test Model Flow Iterators" << endl;
    }

    static void runTestModelExecute() {
        ModelImpl model;
        MockSystem s1("Source", 100.0);
        MockSystem s2("Target", 0.0);
        
        // Cria um fluxo que SEMPRE transfere o valor 10.0
        MockFlow f1(&s1, &s2, 10.0); 

        model.systems.push_back(&s1);
        model.systems.push_back(&s2);
        model.flows.push_back(&f1);

        // Executa 1 único passo de tempo
        model.execute(0, 1);

        // Verificamos o 'value' do mock diretamente!
        assert(s1.value == 90.0);
        assert(s2.value == 10.0);

        cout << "  OK test Model Execute (Isolated Unit)" << endl;
    }

    static void runTestModelExecuteNullOrigin() {
        ModelImpl model;
        MockSystem dest("Target", 50.0);
        MockFlow f1(nullptr, &dest, 10.0); // Origem nula

        model.systems.push_back(&dest);
        model.flows.push_back(&f1);

        model.execute(0, 1);

        // Apenas o destino recebe valor
        assert(dest.value == 60.0);

        cout << "  OK test Model Execute Null Origin" << endl;
    }

    static void runTestModelExecuteNullDestination() {
        ModelImpl model;
        MockSystem orig("Source", 100.0);
        MockFlow f1(&orig, nullptr, 10.0); // Destino nulo

        model.systems.push_back(&orig);
        model.flows.push_back(&f1);

        model.execute(0, 1);

        // Apenas a origem perde valor
        assert(orig.value == 90.0);

        cout << "  OK test Model Execute Null Destination" << endl;
    }
};

void testModelDefaultConstructor() { UnitModel::runTestModelDefaultConstructor(); }
void testModelCopyConstructor() { UnitModel::runTestModelCopyConstructor(); }
void testModelAssignmentOperator() { UnitModel::runTestModelAssignmentOperator(); }
void testModelAddSystem() { UnitModel::runTestModelAddSystem(); }
void testModelAddFlow() { UnitModel::runTestModelAddFlow(); }
void testModelSystemIterators() { UnitModel::runTestModelSystemIterators(); }
void testModelFlowIterators() { UnitModel::runTestModelFlowIterators(); }
void testModelExecuteExponential() { UnitModel::runTestModelExecute(); } // Substituído!
void testModelExecuteNullOrigin() { UnitModel::runTestModelExecuteNullOrigin(); }
void testModelExecuteNullDestination() { UnitModel::runTestModelExecuteNullDestination(); }

void runModelTests() {
    cout << "\n Unit Tests: ModelImpl ==" << endl;
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
    cout << " ModelImpl: All tests passed! ==" << endl;
}