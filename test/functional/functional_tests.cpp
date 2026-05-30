#include "functional_tests.h"
#include "../../src/modelImpl.h"
#include "../../src/systemImpl.h"
#include "../../src/flowImpl.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;
// Flow classes
/**
 * @brief Exponential flow implementation.
 * Transfers a percentage of the origin system value to the destination.
 */
class ExponentialFlow : public FlowImpl {
public:
    ExponentialFlow(string name = "") : FlowImpl(name) {}
    
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
class LogisticFlow : public FlowImpl {
public:
    LogisticFlow(string name = "") : FlowImpl(name) {}
    
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
class ComplexFlow : public FlowImpl {
public:
    ComplexFlow(string name = "") : FlowImpl(name) {}
    
    double execute() override {
        if (getOrigin() != nullptr) {
            return 0.01 * getOrigin()->getValue();
        }
        return 0.0;
    }
};


//tests
void exponentialFunctionalTest() {
    cout << "MODELO EXPONENCIAL" << endl;
    
    // instancia Modelo e Sistemas
    Model* model = new ModelImpl();
    System* pop1 = new SystemImpl("pop1", 100.0);
    System* pop2 = new SystemImpl("pop2", 0.0);
    
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
    // Multiplicamos por 10000 e convertendo para int
    assert((int)round(pop1->getValue() * 10000) == 366032);
    assert((int)round(pop2->getValue() * 10000) == 633968);
    cout << "POP1 :" << (int)round(pop1->getValue() * 10000) << endl;
    cout << "POP2 :" << (int)round(pop2->getValue() * 10000) << endl;
    
    //Limpeza de Memória
    delete model; delete pop1; delete pop2; delete expFlow;
    
    cout << "Teste Exponencial: OK!\n" << endl;
}

void logisticalFunctionalTest() {
    cout << "TESTES: MODELO LOGISTICO" << endl;
    
    Model* model = new ModelImpl();
    System* p1 = new SystemImpl("p1", 100.0);
    System* p2 = new SystemImpl("p2", 10.0);
    Flow* logFlow = new LogisticFlow("logistica");
    
    logFlow->connect(p1, p2);
    
    model->add(p1);
    model->add(p2);
    model->add(logFlow);
    
    model->execute(0, 100);

    assert((int)round(p1->getValue() * 10000) == 882167);
    assert((int)round(p2->getValue() * 10000) == 217833);

    cout << "P1 :" << (int)round(p1->getValue() * 10000) << endl;
    cout << "P2 :" << (int)round(p2->getValue() * 10000) << endl;
    
    delete model; delete p1; delete p2; delete logFlow;
    
    cout << "Teste Logistico: OK!\n" << endl;
}

void complexFunctionalTest() {
    cout << "TESTES: MODELO COMPLEXO" << endl;
    
    Model* model = new ModelImpl();
    System* q1 = new SystemImpl("Q1", 100.0);
    System* q2 = new SystemImpl("Q2", 0.0);
    System* q3 = new SystemImpl("Q3", 100.0);
    System* q4 = new SystemImpl("Q4", 0.0);
    System* q5 = new SystemImpl("Q5", 0.0);

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

    assert((int)round(q1->getValue() * 10000) == 318513);
    assert((int)round(q2->getValue() * 10000) == 184003);
    assert((int)round(q3->getValue() * 10000) == 771143);
    assert((int)round(q4->getValue() * 10000) == 561728);
    assert((int)round(q5->getValue() * 10000) == 164612);

    //prints para facilitar a visualização dos resultados
    cout << "Q1 :" << (int)round(q1->getValue() * 10000) << endl;
    cout << "Q2 :" << (int)round(q2->getValue() * 10000) << endl;
    cout << "Q3 :" << (int)round(q3->getValue() * 10000) << endl;
    cout << "Q4 :" << (int)round(q4->getValue() * 10000) << endl;
    cout << "Q5 :" << (int)round(q5->getValue() * 10000) << endl;

    delete model; delete q1; delete q2; delete q3; delete q4; delete q5;
    delete f; delete g; delete r; delete t; delete u; delete v;

    cout << "Teste Complexo: OK!\n" << endl;
}