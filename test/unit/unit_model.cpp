#include "unit_model.h"
#include "../../src/modelImpl.h"
#include "../../src/systemImpl.h"
#include "../../src/flowImpl.h"
#include <cassert>
#include <iostream>
#include <cmath>

using namespace std;

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

/**
 * @brief Friend test class that accesses ModelImpl internals.
 *
 * Declared as a friend in ModelImpl. It manages testing by directly inspecting 
 * and modifying the protected 'systems' and 'flows' vectors. This guarantees
 * no hidden dependencies on add(), begin(), or end() while testing core 
 * functionalities like execute() or the assignment operators.
 */
class UnitModel {
public:
    /**
     * @brief Executes the default constructor test.
     */
    static void runTestModelDefaultConstructor() {
        // Execução: Método sob teste
        ModelImpl model; 

        // Validação: Verificando o tamanho interno dos vetores diretamente
        assert(model.systems.size() == 0);
        assert(model.flows.size() == 0);

        // Validação secundária: Iteradores begin == end para coleções vazias
        assert(model.beginSystems() == model.endSystems());
        assert(model.beginFlows() == model.endFlows());

        cout << "  [OK] test Model Default Constructor" << endl;
    }

    /**
     * @brief Executes the copy constructor test.
     */
    static void runTestModelCopyConstructor() {
        ModelImpl original;
        SystemImpl s("s1", 10.0);
        ModelTestFlow f("f1");

        // Setup: Inserção direta nos vetores, contornando model.add()
        original.systems.push_back(&s);
        original.flows.push_back(&f);

        // Execução: Construtor de cópia (método sob teste)
        ModelImpl copy(original); 

        // Validação: A cópia deve conter exatamente os mesmos ponteiros
        assert(copy.systems.size() == 1);
        assert(copy.flows.size() == 1);
        assert(copy.systems[0] == &s);
        assert(copy.flows[0] == &f);

        // O modelo original não deve ser afetado pela cópia
        assert(original.systems.size() == 1);
        assert(original.flows.size() == 1);

        cout << "  [OK] test Model Copy Constructor" << endl;
    }

    /**
     * @brief Executes the assignment operator test.
     */
    static void runTestModelAssignmentOperator() {
        ModelImpl m1, m2;
        SystemImpl s1("sA", 5.0);
        
        // Setup: Injeção direta no estado interno
        m1.systems.push_back(&s1);

        // Execução 1: Atribuição (método sob teste)
        m2 = m1; 

        // Validação 1: m2 deve receber a cópia dos ponteiros de m1
        assert(m2.systems.size() == 1);
        assert(m2.systems[0] == &s1);

        // Execução 2: Auto-atribuição (método sob teste)
        m1 = m1; 
        
        // Validação 2: Estado interno não deve corromper
        assert(m1.systems.size() == 1);
        assert(m1.systems[0] == &s1);

        cout << "  [OK] test Model Assignment Operator" << endl;
    }

    /**
     * @brief Executes the addSystem test.
     */
    static void runTestModelAddSystem() {
        ModelImpl model;
        SystemImpl s1("Q1", 100.0);
        SystemImpl s2("Q2", 0.0);

        // Execução 1: Adicionar o primeiro sistema (método sob teste)
        model.add(&s1); 
        
        // Validação 1: Inspeciona o vetor protegido diretamente
        assert(model.systems.size() == 1);
        assert(model.systems[0] == &s1);

        // Execução 2: Adicionar o segundo sistema
        model.add(&s2); 
        
        // Validação 2
        assert(model.systems.size() == 2);
        assert(model.systems[1] == &s2);

        cout << "  [OK] test Model Add System" << endl;
    }

    /**
     * @brief Executes the addFlow test.
     */
    static void runTestModelAddFlow() {
        ModelImpl model;
        ModelTestFlow f1("flow1");
        ModelTestFlow f2("flow2");

        // Execução 1: Método sob teste
        model.add(&f1); 
        
        // Validação 1: Inspeciona o vetor protegido diretamente
        assert(model.flows.size() == 1);
        assert(model.flows[0] == &f1);

        // Execução 2: Adicionando segundo fluxo
        model.add(&f2); 
        
        // Validação 2
        assert(model.flows.size() == 2);
        assert(model.flows[1] == &f2);

        cout << "  [OK] test Model Add Flow" << endl;
    }

    /**
     * @brief Executes the begin/end system iterators test.
     */
    static void runTestModelSystemIterators() {
        ModelImpl model;
        SystemImpl s1("sys1", 1.0);
        SystemImpl s2("sys2", 2.0);
        SystemImpl s3("sys3", 3.0);

        // Setup: Preparação via acesso direto para não testar "add()"
        model.systems.push_back(&s1);
        model.systems.push_back(&s2);
        model.systems.push_back(&s3);

        // Execução: Métodos sob teste (beginSystems e endSystems)
        auto it = model.beginSystems();
        
        // Validação: Iterando e comparando diretamente os ponteiros
        assert(*it == &s1); ++it;
        assert(*it == &s2); ++it;
        assert(*it == &s3); ++it;
        assert(it == model.endSystems());

        cout << "  [OK] test Model System Iterators" << endl;
    }

    /**
     * @brief Executes the begin/end flow iterators test.
     */
    static void runTestModelFlowIterators() {
        ModelImpl model;
        ModelTestFlow f1("f1");
        ModelTestFlow f2("f2");

        // Setup: Preparação via acesso direto
        model.flows.push_back(&f1);
        model.flows.push_back(&f2);

        // Execução e Validação (Métodos sob teste)
        auto it = model.beginFlows(); 
        assert(*it == &f1); ++it;
        assert(*it == &f2); ++it;
        assert(it == model.endFlows()); 

        cout << "  [OK] test Model Flow Iterators" << endl;
    }

    /**
     * @brief Executes the exponential execution flow test.
     */
    static void runTestModelExecuteExponential() {
        ModelImpl model;
        SystemImpl pop1("pop1", 100.0);
        SystemImpl pop2("pop2", 0.0);
        ModelTestFlow expFlow("exp", &pop1, &pop2);

        // Setup: Inserindo no modelo contornando a API pública
        model.systems.push_back(&pop1);
        model.systems.push_back(&pop2);
        model.flows.push_back(&expFlow);

        // Execução: Método sob teste
        model.execute(0, 100); 

        // Validação: Checagem dos side-effects nos sistemas interligados
        assert((int)round(pop1.getValue() * 10000) == 366032);
        assert((int)round(pop2.getValue() * 10000) == 633968);

        cout << "  [OK] test Model Execute Exponential" << endl;
    }

    /**
     * @brief Executes a flow without an origin to test safe behavior.
     */
    static void runTestModelExecuteNullOrigin() {
        ModelImpl model;
        SystemImpl dest("dest", 0.0);
        ModelTestFlow f("noOrigin", nullptr, &dest);

        // Setup isolado
        model.systems.push_back(&dest);
        model.flows.push_back(&f);

        // Execução: Método sob teste
        model.execute(0, 5); 

        // Validação: Destino permanece inalterado pois origem é null
        assert(dest.getValue() == 0.0);

        cout << "  [OK] test Model Execute Null Origin" << endl;
    }

    /**
     * @brief Executes a flow without a destination to test safe behavior.
     */
    static void runTestModelExecuteNullDestination() {
        ModelImpl model;
        SystemImpl orig("orig", 100.0);

        // Fluxo fixo que remove sempre 10 unidades da origem
        class FixedFlow : public FlowImpl {
        public:
            FixedFlow(System* o) : FlowImpl("fixed", o, nullptr) {}
            double execute() override { return 10.0; }
        };

        FixedFlow f(&orig);

        // Setup isolado
        model.systems.push_back(&orig);
        model.flows.push_back(&f);

        // Execução: Método sob teste
        model.execute(0, 1); 

        // Validação: Apenas a origem é afetada; sem destino, modelo não quebra
        assert(orig.getValue() == 90.0);

        cout << "  [OK] test Model Execute Null Destination" << endl;
    }
};

// Funções globais de teste (Repassam a execução para a Friend Class)
void testModelDefaultConstructor() { UnitModel::runTestModelDefaultConstructor(); }
void testModelCopyConstructor() { UnitModel::runTestModelCopyConstructor(); }
void testModelAssignmentOperator() { UnitModel::runTestModelAssignmentOperator(); }
void testModelAddSystem() { UnitModel::runTestModelAddSystem(); }
void testModelAddFlow() { UnitModel::runTestModelAddFlow(); }
void testModelSystemIterators() { UnitModel::runTestModelSystemIterators(); }
void testModelFlowIterators() { UnitModel::runTestModelFlowIterators(); }
void testModelExecuteExponential() { UnitModel::runTestModelExecuteExponential(); }
void testModelExecuteNullOrigin() { UnitModel::runTestModelExecuteNullOrigin(); }
void testModelExecuteNullDestination() { UnitModel::runTestModelExecuteNullDestination(); }

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