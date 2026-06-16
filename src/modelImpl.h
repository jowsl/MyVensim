#ifndef MODELIMPL_H
#define MODELIMPL_H

#include "model.h"
#include "singleton.h" 
#include <vector>

using namespace std;

/**
 * @brief Concrete implementation of the Model interface.
 */
class ModelImpl : public Model {
    //Permite que a classe de testes acesse 'systems' e 'flows' diretamente
    friend class UnitModel;
    friend class Model;

    //Permite que o template instancie o objeto acessando o construtor privado
protected:
    vector<System*> systems;
    vector<Flow*> flows;

    // vector for keeping track of all created model instances
    static vector<Model*> models;
    
    //métodos add() protegidos para forçar o uso da Fábrica
    void add(System* sys) override;
    void add(Flow* flow) override;

private:
    /**
     * @brief Construct a new ModelImpl object.
     * Initializes an empty model with no systems or flows.
     * That constructor is private to enforce the use of the Factory Method (createModel).
     * @param name Optional name for the model.
     */
    ModelImpl(string name = "");

public:
    /**
     * @brief Destroy the ModelImpl object.
     * Cleans up any resources used by the model.
     */
    virtual ~ModelImpl();

    ModelImpl(const ModelImpl& param_model) = delete;
    ModelImpl& operator=(const ModelImpl& param_model) = delete;

    System& createSystem(string id, double qtd) override;
    void clear() override;

    // Sobrescritas dos iteradores e execução
    systemIterator beginSystems() override;
    systemIterator endSystems() override;
    flowIterator beginFlows() override;
    flowIterator endFlows() override;

    void execute(double time_ini, double time_final) override;
};

#endif