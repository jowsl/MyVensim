#ifndef MODELIMPL_H
#define MODELIMPL_H

#include "model.h"
#include <vector>

using namespace std;

/**
 * @brief Concrete implementation of the Model interface.
 */

class ModelImpl : public Model {
    //Permite que a classe de testes acesse 'systems' e 'flows' diretamente
    friend class UnitModel;

protected:
    vector<System*> systems;
    vector<Flow*> flows;

public:
    /**
     * @brief Construct a new ModelImpl object.
     * Initializes an empty model with no systems or flows.
     */
    ModelImpl();
    /**
     * @brief Destroy the ModelImpl object.
     * Cleans up any resources used by the model.
     */
    virtual ~ModelImpl();

    /**
     * @brief Construct a new ModelImpl object by copying another model.
     * @param param_model The model to copy from.
     */
    ModelImpl(const ModelImpl& param_model);
    /**
     * @brief Assign the values of another model to this model.
     * @param param_model The model to copy from.
     * @return A reference to this model.
     */
    ModelImpl& operator=(const ModelImpl& param_model);

    //sobrescritas
    void add(System* sys) override;
    void add(Flow* flow) override;

    systemIterator beginSystems() override;
    systemIterator endSystems() override;
    flowIterator beginFlows() override;
    flowIterator endFlows() override;

    void execute(double time_ini, double time_final) override;
};

#endif