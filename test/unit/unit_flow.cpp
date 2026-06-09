#include "unit_flow.h"
#include "../../src/flowImpl.h"
#include "../../src/systemImpl.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

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

/**
 * @brief Friend test class that accesses FlowImpl internals.
 *
 * Declared as a friend in FlowImpl. Its static methods directly manipulate
 * the protected 'name', 'origin', and 'destination' attributes. This ensures
 * that tests are decoupled from other public methods, guaranteeing single-method
 * isolation per test.
 */
class UnitFlow {
public:
    /**
     * @brief Executes the default constructor test.
     */
    static void runTestFlowDefaultConstructor() {
        // Execução: Método sob teste
        TestFlow f; 

        // Validação: Acesso direto aos atributos protegidos da classe base
        assert(f.name == "");
        assert(f.origin == nullptr);
        assert(f.destination == nullptr);

        cout << "  OK test Flow Default Constructor" << endl;
    }

    /**
     * @brief Executes the parameterized constructor test.
     */
    static void runTestFlowParameterizedConstructor() {
        SystemImpl s1, s2;
        
        // Execução: Método sob teste
        TestFlow f("transfer", &s1, &s2); 

        // Validação: Checagem direta dos ponteiros e string
        assert(f.name == "transfer");
        assert(f.origin == &s1);
        assert(f.destination == &s2);

        cout << "  OK test Flow Parameterized Constructor" << endl;
    }

    /**
     * @brief Executes the copy constructor test.
     */
    static void runTestFlowCopyConstructor() {
        SystemImpl s1, s2;
        TestFlow original;
        
        // Setup: Configuração direta no objeto original
        original.name = "flow1";
        original.origin = &s1;
        original.destination = &s2;

        // Execução: Construtor de cópia (método sob teste)
        TestFlow copy(original); 

        // Validação: A cópia deve compartilhar as mesmas referências
        assert(copy.name == "flow1");
        assert(copy.origin == &s1);
        assert(copy.destination == &s2);

        cout << "  OK test Flow Copy Constructor" << endl;
    }

    /**
     * @brief Executes the assignment operator test.
     */
    static void runTestFlowAssignmentOperator() {
        SystemImpl s1, s2;
        TestFlow f1;
        
        // Setup: Configuração direta do objeto fonte
        f1.name = "flowA";
        f1.origin = &s1;
        f1.destination = &s2;
        
        TestFlow f2;

        // Execução: Operador de atribuição (método sob teste)
        f2 = f1; 

        // Validação: O estado de f2 deve refletir o de f1 via acesso direto
        assert(f2.name == "flowA");
        assert(f2.origin == &s1);
        assert(f2.destination == &s2);

        cout << "  OK test Flow Assignment Operator" << endl;
    }

    /**
     * @brief Executes the setName test.
     */
    static void runTestFlowSetName() {
        TestFlow f;
        
        // Execução e Validação 1
        f.setName("evaporation"); // Método sob teste
        assert(f.name == "evaporation"); // Acesso direto

        // Execução e Validação 2
        f.setName("precipitation");
        assert(f.name == "precipitation");

        // Execução e Validação 3
        f.setName(""); 
        assert(f.name == "");

        cout << "  OK test Flow Set Name" << endl;
    }

    /**
     * @brief Executes the getName test.
     */
    static void runTestFlowGetName() {
        TestFlow f;
        
        // Setup: Configuração direta na variável
        f.name = "precipitation"; 

        // Execução e Validação: O getter (método sob teste) deve retornar o valor
        assert(f.getName() == "precipitation"); 

        cout << "  OK test Flow Get Name" << endl;
    }

    /**
     * @brief Executes the setOrigin test.
     */
    static void runTestFlowSetOrigin() {
        SystemImpl s1;
        TestFlow f;

        // Execução 1
        f.setOrigin(&s1); // Método sob teste
        
        // Validação 1: Acesso direto ao ponteiro origin
        assert(f.origin == &s1);

        // Execução 2: Reseta para nullptr
        f.setOrigin(nullptr); 
        
        // Validação 2
        assert(f.origin == nullptr);

        cout << "  OK test Flow Set Origin" << endl;
    }

    /**
     * @brief Executes the getOrigin test.
     */
    static void runTestFlowGetOrigin() {
        TestFlow f;
        SystemImpl s1;
        
        // Setup: Atribuição direta ao ponteiro
        f.origin = &s1; 

        // Execução e Validação: Método sob teste
        assert(f.getOrigin() == &s1); 

        cout << "  OK test Flow Get Origin" << endl;
    }

    /**
     * @brief Executes the setDestination test.
     */
    static void runTestFlowSetDestination() {
        SystemImpl s1;
        TestFlow f;

        // Execução 1
        f.setDestination(&s1); // Método sob teste
        
        // Validação 1
        assert(f.destination == &s1); // Acesso direto ao ponteiro

        // Execução 2: Reseta para nullptr
        f.setDestination(nullptr); 
        
        // Validação 2
        assert(f.destination == nullptr);

        cout << "  OK test Flow Set Destination" << endl;
    }

    /**
     * @brief Executes the getDestination test.
     */
    static void runTestFlowGetDestination() {
        TestFlow f;
        SystemImpl s1;
        
        // Setup: Atribuição direta ao ponteiro
        f.destination = &s1; 

        // Execução e Validação: Método sob teste
        assert(f.getDestination() == &s1); 

        cout << "  OK test Flow Get Destination" << endl;
    }

    /**
     * @brief Executes the connect test.
     */
    static void runTestFlowConnect() {
        SystemImpl s1, s2, s3;
        TestFlow f;

        // Execução 1: Conecta origem e destino em um único chamado
        f.connect(&s1, &s2); // Método sob teste
        
        // Validação 1
        assert(f.origin == &s1);
        assert(f.destination == &s2);

        // Execução 2: Reconectar deve sobrescrever a conexão anterior
        f.connect(&s3, &s1); 
        
        // Validação 2
        assert(f.origin == &s3);
        assert(f.destination == &s1);

        // Execução 3: Conectar com nullptr (fluxo desconectado)
        f.connect(nullptr, nullptr); 
        
        // Validação 3
        assert(f.origin == nullptr);
        assert(f.destination == nullptr);

        cout << "  OK test Flow Connect" << endl;
    }
};

// Funções globais de teste (Repassam a execução para a Friend Class)
void testFlowDefaultConstructor() { UnitFlow::runTestFlowDefaultConstructor(); }
void testFlowParameterizedConstructor() { UnitFlow::runTestFlowParameterizedConstructor(); }
void testFlowCopyConstructor() { UnitFlow::runTestFlowCopyConstructor(); }
void testFlowAssignmentOperator() { UnitFlow::runTestFlowAssignmentOperator(); }
void testFlowSetName() { UnitFlow::runTestFlowSetName(); }
void testFlowGetName() { UnitFlow::runTestFlowGetName(); }
void testFlowSetOrigin() { UnitFlow::runTestFlowSetOrigin(); }
void testFlowGetOrigin() { UnitFlow::runTestFlowGetOrigin(); }
void testFlowSetDestination() { UnitFlow::runTestFlowSetDestination(); }
void testFlowGetDestination() { UnitFlow::runTestFlowGetDestination(); }
void testFlowConnect() { UnitFlow::runTestFlowConnect(); }

void runFlowTests() {
    cout << "\n Unit Tests: FlowImpl ==" << endl;

    testFlowDefaultConstructor();
    testFlowParameterizedConstructor();
    testFlowCopyConstructor();
    testFlowAssignmentOperator();
    testFlowSetName();
    testFlowGetName();
    testFlowSetOrigin();
    testFlowGetOrigin();
    testFlowSetDestination();
    testFlowGetDestination();
    testFlowConnect();

    cout << " FlowImpl: All tests passed! ==" << endl;
}