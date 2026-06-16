#include "unit_model.h"
#include "../../src/model.h"
#include "../../src/system.h" 
#include "../../src/flow.h"   
#include <cassert>
#include <iostream>

using namespace std;

// Mocks ficam no escopo do teste para não poluir o sistema real
class MockSystem : public System {
public:
    double value; 
    string name;

    MockSystem(string n = "", double v = 0.0) : name(n), value(v) {}
    ~MockSystem() {}

    void setValue(double v) override { value = v; }
    double getValue() const override { return value; }
    void setName(string n) override { name = n; }
    string getName() const override { return name; }
};

class MockFlow : public Flow {
public:
    System* origin;
    System* destination;
    double returnValue;
    string name;

    MockFlow(string n = "", System* o = nullptr, System* d = nullptr, double ret = 10.0)
        : name(n), origin(o), destination(d), returnValue(ret) {}
    ~MockFlow() {}

    void setOrigin(System* o) override { origin = o; }
    System* getOrigin() const override { return origin; }
    void setDestination(System* d) override { destination = d; }
    System* getDestination() const override { return destination; }
    void connect(System* o, System* d) override { origin = o; destination = d; }
    void setName(string n) override { name = n; }
    string getName() const override { return name; }
    
    double execute() override { return returnValue; } 
};

// Função auxiliar para contar elementos via iterador (já que não temos .size())
int countSystems(Model& m) {
    int count = 0;
    for(auto it = m.beginSystems(); it != m.endSystems(); ++it) count++;
    return count;
}

int countFlows(Model& m) {
    int count = 0;
    for(auto it = m.beginFlows(); it != m.endFlows(); ++it) count++;
    return count;
}

class UnitModel {
public:
    static void runTestModelSingletonAndClear() {
        // Agora usamos o createModel() da interface!
        Model& model = Model::createModel();
        model.clear();
        
        assert(countSystems(model) == 0);
        assert(countFlows(model) == 0);
        cout << "  OK test Model Singleton & Clear" << endl;
    }

    static void runTestModelCreateSystem() {
        Model& model = Model::createModel();
        model.clear();
        
        System& s1 = model.createSystem("s1", 10.0);
        assert(countSystems(model) == 1);
        assert(*(model.beginSystems()) == &s1);
        cout << "  OK test Model Create System Factory" << endl;
    }

    static void runTestModelCreateFlow() {
        Model& model = Model::createModel();
        model.clear();
        
        System& s1 = model.createSystem("s1", 0.0);
        System& s2 = model.createSystem("s2", 0.0);
        
        // Passando a classe Mock diretamente pro template da interface
        Flow& f1 = model.createFlow<MockFlow>("Mock", &s1, &s2);
        assert(countFlows(model) == 1);
        assert(*(model.beginFlows()) == &f1);
        cout << "  OK test Model Create Flow Factory" << endl;
    }

    static void runTestModelSystemIterators() {
        Model& model = Model::createModel();
        model.clear();
        
        MockSystem* s1 = new MockSystem(); 
        model.add(s1); // Válido graças ao 'friend class UnitModel' na interface Model
        assert(*(model.beginSystems()) == s1);
        cout << "  OK test Model System Iterators" << endl;
    }

    static void runTestModelFlowIterators() {
        Model& model = Model::createModel();
        model.clear();
        
        MockFlow* f1 = new MockFlow(); 
        model.add(f1); 
        assert(*(model.beginFlows()) == f1);
        cout << "  OK test Model Flow Iterators" << endl;
    }

    static void runTestModelExecute() {
        Model& model = Model::createModel();
        model.clear();
        
        MockSystem* s1 = new MockSystem("Source", 100.0);
        MockSystem* s2 = new MockSystem("Target", 0.0);
        MockFlow* f1 = new MockFlow("Mock", s1, s2, 10.0); 

        model.add(s1); //erro aqui
        model.add(s2);
        model.add(f1);

        model.execute(0, 1);

        assert(s1->value == 90.0);
        assert(s2->value == 10.0);

        cout << "  OK test Model Execute" << endl;
    }

    static void runTestModelExecuteNullOrigin() {
        Model& model = Model::createModel();
        model.clear();
        
        MockSystem* dest = new MockSystem("Target", 50.0);
        MockFlow* f1 = new MockFlow("Mock", nullptr, dest, 10.0);

        model.add(dest);
        model.add(f1);

        model.execute(0, 1);

        assert(dest->value == 60.0);
        cout << "  OK test Model Execute Null Origin" << endl;
    }

    static void runTestModelExecuteNullDestination() {
        Model& model = Model::createModel();
        model.clear();
        
        MockSystem* orig = new MockSystem("Source", 100.0);
        MockFlow* f1 = new MockFlow("Mock", orig, nullptr, 10.0);

        model.add(orig);
        model.add(f1);

        model.execute(0, 1);

        assert(orig->value == 90.0);
        cout << "  OK test Model Execute Null Destination" << endl;
    }
};

void testModelSingletonAndClear() { UnitModel::runTestModelSingletonAndClear(); }
void testModelCreateSystem() { UnitModel::runTestModelCreateSystem(); }
void testModelCreateFlow() { UnitModel::runTestModelCreateFlow(); }
void testModelSystemIterators() { UnitModel::runTestModelSystemIterators(); }
void testModelFlowIterators() { UnitModel::runTestModelFlowIterators(); }
void testModelExecute() { UnitModel::runTestModelExecute(); }
void testModelExecuteNullOrigin() { UnitModel::runTestModelExecuteNullOrigin(); }
void testModelExecuteNullDestination() { UnitModel::runTestModelExecuteNullDestination(); }

void runModelTests() {
    cout << "\n= Unit Tests: Model =" << endl;
    testModelSingletonAndClear();
    testModelCreateSystem();
    testModelCreateFlow();
    testModelSystemIterators();
    testModelFlowIterators();
    testModelExecute();
    testModelExecuteNullOrigin();
    testModelExecuteNullDestination();
    cout << "= Model: All tests passed! =" << endl;
}