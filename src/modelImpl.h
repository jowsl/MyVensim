#ifndef MODELIMPL_H
#define MODELIMPL_H

#include "model.h"
#include "singleton.h" 
#include <vector>

using namespace std;

/**
 * @brief Concrete implementation of the Model interface.
 */
class ModelImpl : public Model, public TempSingleton<ModelImpl> {
    // Permite que a classe de testes acesse 'systems' e 'flows' diretamente
    friend class UnitModel;

    // Permite que o template instancie o objeto acessando o construtor privado
    friend class TempSingleton<ModelImpl>;

private:
    /**
     * @brief Construct a new ModelImpl object.
     * Initializes an empty model with no systems or flows.
     */
    ModelImpl();

protected:
    vector<System*> systems;
    vector<Flow*> flows;

    // Métodos add() protegidos para forçar o uso da Fábrica
    void add(System* sys) override;
    void add(Flow* flow) override;

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