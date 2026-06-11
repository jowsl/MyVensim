#include "unit_model.h"
#include "../../src/modelImpl.h"
#include "../../src/system.h" 
#include "../../src/flow.h"   
#include <cassert>
#include <iostream>

using namespace std;

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

    // Construtor ajustado para ser compatível com a Fábrica genérica
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

class UnitModel {
public:
    static void runTestModelSingletonAndClear() {
        ModelImpl& model = ModelImpl::getInstance();
        model.clear();
        
        assert(model.systems.size() == 0);
        assert(model.flows.size() == 0);
        cout << "  OK test Model Singleton & Clear" << endl;
    }

    static void runTestModelCreateSystem() {
        ModelImpl& model = ModelImpl::getInstance();
        model.clear();
        
        System& s1 = model.createSystem("s1", 10.0);
        assert(model.systems.size() == 1);
        assert(model.systems[0] == &s1);
        cout << "  OK test Model Create System Factory" << endl;
    }

    static void runTestModelCreateFlow() {
        ModelImpl& model = ModelImpl::getInstance();
        model.clear();
        
        System& s1 = model.createSystem("s1", 0.0);
        System& s2 = model.createSystem("s2", 0.0);
        
        Flow& f1 = model.createFlow<MockFlow>("Mock", &s1, &s2);
        assert(model.flows.size() == 1);
        assert(model.flows[0] == &f1);
        assert(f1.getOrigin() == &s1);
        cout << "  OK test Model Create Flow Factory" << endl;
    }

    // static void runTestModelSystemIterators() {
    //     ModelImpl& model = ModelImpl::getInstance();
    //     model.clear();
          //da segmentation fault porque o MockSystem é criado na stack e o clear() tenta deletar ele depois. 
    //     MockSystem s1;
    //     model.add(&s1); // Usando add protegido via friend
    //     assert(*(model.beginSystems()) == &s1);
    //     cout << "  OK test Model System Iterators" << endl;
    // }


    static void runTestModelSystemIterators() {
        ModelImpl& model = ModelImpl::getInstance();
        model.clear();
        
        MockSystem* s1 = new MockSystem(); // Usa 'new' para o clear() conseguir deletar depois
        model.add(s1); 
        assert(*(model.beginSystems()) == s1);
        cout << "  OK test Model System Iterators" << endl;
    }

    static void runTestModelFlowIterators() {
        ModelImpl& model = ModelImpl::getInstance();
        model.clear();
        
        MockFlow* f1 = new MockFlow(); // Usa 'new'
        model.add(f1); 
        assert(*(model.beginFlows()) == f1);
        cout << "  OK test Model Flow Iterators" << endl;
    }

    static void runTestModelExecute() {
        ModelImpl& model = ModelImpl::getInstance();
        model.clear();
        
        MockSystem* s1 = new MockSystem("Source", 100.0);
        MockSystem* s2 = new MockSystem("Target", 0.0);
        MockFlow* f1 = new MockFlow("Mock", s1, s2, 10.0); 

        model.add(s1);
        model.add(s2);
        model.add(f1);

        model.execute(0, 1);

        assert(s1->value == 90.0);
        assert(s2->value == 10.0);

        cout << "  OK test Model Execute" << endl;
    }

    static void runTestModelExecuteNullOrigin() {
        ModelImpl& model = ModelImpl::getInstance();
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
        ModelImpl& model = ModelImpl::getInstance();
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
    cout << "\n Unit Tests: ModelImpl ==" << endl;
    testModelSingletonAndClear();
    testModelCreateSystem();
    testModelCreateFlow();
    testModelSystemIterators();
    testModelFlowIterators();
    testModelExecute();
    testModelExecuteNullOrigin();
    testModelExecuteNullDestination();
    cout << " ModelImpl: All tests passed! ==" << endl;
}