#include "functional_tests.h"
#include "../../src/modelImpl.h"
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


// Tests
void exponentialFunctionalTest() {
    cout << "MODELO EXPONENCIAL" << endl;

    // 1. Pega a instância global e zera ela
    Model& model = ModelImpl::getInstance();
    model.clear();

    // 2. A Fábrica cria, guarda e devolve a referência pronta
    System& pop1 = model.createSystem("pop1", 100.0);
    System& pop2 = model.createSystem("pop2", 0.0);

    // 3. O template cria o fluxo específico e já conecta
    model.createFlow<ExponentialFlow>("exponencial", &pop1, &pop2);

    // 4. Executa a simulação
    model.execute(0, 100);

    // 5. Usa o ponto (.) pois pop1/pop2 são referências, não ponteiros
    assert((int)round(pop1.getValue() * 10000) == 366032);
    assert((int)round(pop2.getValue() * 10000) == 633968);
    cout << "POP1 :" << (int)round(pop1.getValue() * 10000) << endl;
    cout << "POP2 :" << (int)round(pop2.getValue() * 10000) << endl;

    // Sem delete! A Fábrica (Model) limpa a memória sozinha.
    cout << "Teste Exponencial: OK!\n" << endl;
}

void logisticalFunctionalTest() {
    cout << "TESTES: MODELO LOGISTICO" << endl;

    // 1. Pega a instância global e zera ela
    Model& model = ModelImpl::getInstance();
    model.clear();

    // 2. A Fábrica cria, guarda e devolve a referência pronta
    System& p1 = model.createSystem("p1", 100.0);
    System& p2 = model.createSystem("p2", 10.0);

    // 3. O template cria o fluxo específico e já conecta
    model.createFlow<LogisticFlow>("logistica", &p1, &p2);

    // 4. Executa a simulação
    model.execute(0, 100);

    // 5. Usa o ponto (.) pois p1/p2 são referências, não ponteiros
    assert((int)round(p1.getValue() * 10000) == 882167);
    assert((int)round(p2.getValue() * 10000) == 217833);
    cout << "P1 :" << (int)round(p1.getValue() * 10000) << endl;
    cout << "P2 :" << (int)round(p2.getValue() * 10000) << endl;

    // Sem delete! A Fábrica (Model) limpa a memória sozinha.
    cout << "Teste Logistico: OK!\n" << endl;
}

void complexFunctionalTest() {
    cout << "TESTES: MODELO COMPLEXO" << endl;

    // 1. Pega a instância global e zera ela
    Model& model = ModelImpl::getInstance();
    model.clear();

    // 2. A Fábrica cria, guarda e devolve as referências prontas
    System& q1 = model.createSystem("Q1", 100.0);
    System& q2 = model.createSystem("Q2", 0.0);
    System& q3 = model.createSystem("Q3", 100.0);
    System& q4 = model.createSystem("Q4", 0.0);
    System& q5 = model.createSystem("Q5", 0.0);

    // 3. O template cria cada fluxo e já conecta
    model.createFlow<ComplexFlow>("f", &q1, &q2);
    model.createFlow<ComplexFlow>("g", &q1, &q3);
    model.createFlow<ComplexFlow>("r", &q2, &q5);
    model.createFlow<ComplexFlow>("t", &q2, &q3);
    model.createFlow<ComplexFlow>("u", &q3, &q4);
    model.createFlow<ComplexFlow>("v", &q4, &q1);

    // 4. Executa a simulação
    model.execute(0, 100);

    // 5. Usa o ponto (.) pois q1..q5 são referências, não ponteiros
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

    // Sem delete! A Fábrica (Model) limpa a memória sozinha.
    cout << "Teste Complexo: OK!\n" << endl;
}