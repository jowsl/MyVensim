#include "unit_system.h"
#include "../../src/systemImpl.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Friend test class that accesses SystemImpl internals.
 *
 * Declared as a friend in SystemImpl. This class contains static methods 
 * that execute the tests by directly reading and writing to the protected 
 * 'name' and 'value' fields. This guarantees that each test strictly 
 * validates only one method at a time, avoiding cross-contamination 
 * from other public methods (like getters or setters) during setup or assertions.
 */
class UnitSystem {
public:
    /**
     * @brief Executes the default constructor test.
     */
    static void runTestSystemDefaultConstructor() {
        // Execução: Instanciação usando o construtor padrão (método sob teste)
        SystemImpl s;

        // Validação: Acesso direto aos atributos protegidos (sem usar getters)
        assert(s.name == "");
        assert(s.value == 0.0);

        cout << "  [OK] test System Default Constructor" << endl;
    }

    /**
     * @brief Executes the parameterized constructor test.
     */
    static void runTestSystemParameterizedConstructor() {
        // Execução: Instanciação usando o construtor parametrizado (método sob teste)
        SystemImpl s("reservoir", 200.5);

        // Validação: Acesso direto aos atributos protegidos para confirmar a inicialização
        assert(s.name == "reservoir");
        assert(s.value == 200.5);

        cout << "  [OK] test System Parameterized Constructor" << endl;
    }

    /**
     * @brief Executes the copy constructor test.
     */
    static void runTestSystemCopyConstructor() {
        SystemImpl original;
        
        // Setup: Configuração direta do estado original sem usar setters
        original.name = "source";
        original.value = 42.0;

        // Execução: Construtor de cópia (método sob teste)
        SystemImpl copy(original);

        // Validação: Verifica os atributos da cópia diretamente
        assert(copy.name == "source");
        assert(copy.value == 42.0);

        cout << "  [OK] test System Copy Constructor" << endl;
    }

    /**
     * @brief Executes the assignment operator test.
     */
    static void runTestSystemAssignmentOperator() {
        SystemImpl s1, s2;
        
        // Setup: Configuração direta de ambos os objetos sem usar construtores ou setters
        s1.name = "alpha";
        s1.value = 10.0;
        s2.name = "beta";
        s2.value = 20.0;

        // Execução 1: Atribuição normal (método sob teste)
        s2 = s1; 

        // Validação 1: O estado de s2 deve ser idêntico ao de s1
        assert(s2.name == "alpha");
        assert(s2.value == 10.0);

        // Execução 2: Auto-atribuição (método sob teste)
        s1 = s1; 
        
        // Validação 2: O objeto não deve ter sido corrompido
        assert(s1.name == "alpha");
        assert(s1.value == 10.0);

        cout << "  [OK] test System Assignment Operator" << endl;
    }

    /**
     * @brief Executes the setName test.
     */
    static void runTestSystemSetName() {
        SystemImpl s;

        // Execução 1: Chamada do setter (método sob teste)
        s.setName("population"); 
        
        // Validação 1: Confirmação direta na variável protegida
        assert(s.name == "population");

        // Execução 2: Sobrescrevendo o nome
        s.setName("biomass"); 
        assert(s.name == "biomass");

        // Execução 3: Nome vazio
        s.setName(""); 
        assert(s.name == "");

        cout << "  [OK] test System Set Name" << endl;
    }

    /**
     * @brief Executes the getName test.
     */
    static void runTestSystemGetName() {
        SystemImpl s;
        
        // Setup: Injeção direta da string no atributo protegido
        s.name = "biomass"; 

        // Execução e Validação: O retorno do getter (método sob teste) deve bater com o estado interno
        assert(s.getName() == "biomass"); 

        cout << "  [OK] test System Get Name" << endl;
    }

    /**
     * @brief Executes the setValue test.
     */
    static void runTestSystemSetValue() {
        SystemImpl s;

        // Execução 1: Chamada do setter (método sob teste)
        s.setValue(100.0); 
        
        // Validação 1: Acesso direto ao atributo 'value'
        assert(s.value == 100.0);

        // Execução 2: Valor negativo
        s.setValue(-50.75);
        assert(s.value == -50.75);

        // Execução 3: Zero explícito
        s.setValue(0.0); 
        assert(s.value == 0.0);

        // Execução 4: Valor com casas decimais
        s.setValue(3.14159265); 
        assert(s.value == 3.14159265);

        cout << "  [OK] test System Set Value" << endl;
    }

    /**
     * @brief Executes the getValue test.
     */
    static void runTestSystemGetValue() {
        SystemImpl s;
        
        // Setup: Injeção direta do valor no atributo protegido
        s.value = 3.14159265; 

        // Execução e Validação: O retorno do getter (método sob teste) deve bater com o internal
        assert(s.getValue() == 3.14159265); 

        cout << "  [OK] test System Get Value" << endl;
    }
};

// Funções globais de teste (Repassam a execução para a Friend Class)
void testSystemDefaultConstructor() { UnitSystem::runTestSystemDefaultConstructor(); }
void testSystemParameterizedConstructor() { UnitSystem::runTestSystemParameterizedConstructor(); }
void testSystemCopyConstructor() { UnitSystem::runTestSystemCopyConstructor(); }
void testSystemAssignmentOperator() { UnitSystem::runTestSystemAssignmentOperator(); }
void testSystemSetName() { UnitSystem::runTestSystemSetName(); }
void testSystemGetName() { UnitSystem::runTestSystemGetName(); }
void testSystemSetValue() { UnitSystem::runTestSystemSetValue(); }
void testSystemGetValue() { UnitSystem::runTestSystemGetValue(); }

void runSystemTests() {
    cout << "\n=== Unit Tests: SystemImpl ===" << endl;

    testSystemDefaultConstructor();
    testSystemParameterizedConstructor();
    testSystemCopyConstructor();
    testSystemAssignmentOperator();
    testSystemSetName();
    testSystemGetName();
    testSystemSetValue();
    testSystemGetValue();

    cout << "=== SystemImpl: All tests passed! ===" << endl;
}