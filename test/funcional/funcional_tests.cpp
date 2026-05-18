#include "funcional_tests.h"
#include "../../src/model.h"
#include "../../src/system.h"
#include "../../src/flow.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

// Flow classes
// exponentialFlow
class ExponentialFlow : public Flow {
public:
    ExponentialFlow(string name = "") : Flow(name) {}
    
    double execute() override {
        if (getOrigin() != nullptr) {
            return 0.01 * getOrigin()->getValue();
        }
        return 0.0;
    }
};

// logisticFlow
class LogisticFlow : public Flow {
public:
    LogisticFlow(string name = "") : Flow(name) {}
    
    double execute() override {
        if (getDestination() != nullptr) {
            double p2 = getDestination()->getValue();
            return 0.01 * p2 * (1.0 - p2 / 70.0);
        }
        return 0.0;
    }
};

// ComplexFlow
class ComplexFlow : public Flow {
public:
    ComplexFlow(string name = "") : Flow(name) {}
    
    double execute() override {
        if (getOrigin() != nullptr) {
            return 0.01 * getOrigin()->getValue();
        }
        return 0.0;
    }
};


//tests
void exponentialFuncionalTest() {
    cout << "MODELO EXPONENCIAL" << endl;
    
    // instancia Modelo e Sistemas
    Model* model = new Model();
    System* pop1 = new System("pop1", 100.0);
    System* pop2 = new System("pop2", 0.0);
    
    // Instancia o Fluxo Exponencial
    Flow* expFlow = new ExponentialFlow("exponencial");
    
    //Conecta Origem(Pop1) -> Destino(Pop2)
    expFlow->connect(pop1, pop2);
    
    //Adiciona tudo ao modelo
    model->add(pop1);
    model->add(pop2);
    model->add(expFlow);
    
    //Executa a simulação
    model->execute(0, 100);
    
    // assert para validar os Critérios de Aceitação
    // Multiplicamos por 10000 + 0.5 e convertendo para int evita problemas de precisão com double
    assert((int)trunc(pop1->getValue() * 10000 + 0.5) == 366032);
    assert((int)trunc(pop2->getValue() * 10000 + 0.5) == 633968);
    cout << "POP1 :" << (int)trunc(pop1->getValue() * 10000 + 0.5) << endl;
    cout << "POP2 :" << (int)trunc(pop2->getValue() * 10000 + 0.5) << endl;
    
    //Limpeza de Memória
    delete model; delete pop1; delete pop2; delete expFlow;
    
    cout << "Teste Exponencial: OK!\n" << endl;
}

void logisticalFuncionalTest() {
    cout << "TESTES: MODELO LOGISTICO" << endl;
    
    Model* model = new Model();
    System* p1 = new System("p1", 100.0);
    System* p2 = new System("p2", 10.0);
    Flow* logFlow = new LogisticFlow("logistica");
    
    logFlow->connect(p1, p2);
    
    model->add(p1);
    model->add(p2);
    model->add(logFlow);
    
    model->execute(0, 100);

    cout << "P1 :" << (int)trunc(p1->getValue() * 10000 + 0.5) << endl;
    cout << "P2 :" << (int)trunc(p2->getValue() * 10000 + 0.5) << endl;
    
    assert((int)trunc(p1->getValue() * 10000 + 0.5) == 882167);
    assert((int)trunc(p2->getValue() * 10000 + 0.5) == 217833);

    cout << "P1 :" << (int)trunc(p1->getValue() * 10000 + 0.5) << endl;
    cout << "P2 :" << (int)trunc(p2->getValue() * 10000 + 0.5) << endl;
    
    delete model; delete p1; delete p2; delete logFlow;
    
    cout << "Teste Logistico: OK!\n" << endl;
}

void complexFuncionalTest() {
    cout << "TESTES: MODELO COMPLEXO" << endl;
    
    Model* model = new Model();
    System* q1 = new System("Q1", 100.0);
    System* q2 = new System("Q2", 0.0);
    System* q3 = new System("Q3", 100.0);
    System* q4 = new System("Q4", 0.0);
    System* q5 = new System("Q5", 0.0);

    Flow* f = new ComplexFlow("f"); f->connect(q1, q2);
    Flow* g = new ComplexFlow("g"); g->connect(q1, q3);
    Flow* r = new ComplexFlow("r"); r->connect(q2, q5);
    Flow* t = new ComplexFlow("t"); t->connect(q2, q3);
    Flow* u = new ComplexFlow("u"); u->connect(q3, q4);
    Flow* v = new ComplexFlow("v"); v->connect(q4, q1);

    model->add(q1); model->add(q2); model->add(q3); 
    model->add(q4); model->add(q5);
    model->add(f); model->add(g); model->add(r); 
    model->add(t); model->add(u); model->add(v);

    model->execute(0, 100);

    assert((int)trunc(q1->getValue() * 10000 + 0.5) == 318513);
    assert((int)trunc(q2->getValue() * 10000 + 0.5) == 184003);
    assert((int)trunc(q3->getValue() * 10000 + 0.5) == 771143);
    assert((int)trunc(q4->getValue() * 10000 + 0.5) == 561728);
    assert((int)trunc(q5->getValue() * 10000 + 0.5) == 164612);

    delete model; delete q1; delete q2; delete q3; delete q4; delete q5;
    delete f; delete g; delete r; delete t; delete u; delete v;

    cout << "Teste Complexo: OK!\n" << endl;
}