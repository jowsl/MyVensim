#ifndef MODELIMPL_H
#define MODELIMPL_H

#include "model.h"
#include "singleton.h"
#include "handleBody.h"
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

class ModelBody : public Body {
protected:
    std::string name;
    std::vector<System*> systems;
    std::vector<Flow*> flows;
public:
    ModelBody(std::string name = "");
    virtual ~ModelBody();

    void clear();
    System& createSystem(std::string name, double value);
    void add(System* sys) { systems.push_back(sys); }
    void add(Flow* fl) { flows.push_back(fl); }

    void execute(double time_ini, double time_final);

    std::vector<System*>::iterator beginSystems() { return systems.begin(); }
    std::vector<System*>::iterator endSystems() { return systems.end(); }
    std::vector<Flow*>::iterator beginFlows() { return flows.begin(); }
    std::vector<Flow*>::iterator endFlows() { return flows.end(); }
};

class ModelHandle : public Model, public Handle<ModelBody> {
    friend class Model;
    friend class UnitModel; //para acessar metodos protegidos

protected:
    static vector<Model*> models;
    
    void add(System* sys) override { this->pImpl_->add(sys); }
    void add(Flow* flow) override { this->pImpl_->add(flow); }

public:
    ModelHandle(string name = "");
    virtual ~ModelHandle();

    void clear() override;
    System& createSystem(std::string name, double value) override;
    
    template <typename T_FLOW>
    Flow& createFlow(std::string name, System* orig = nullptr, System* dest = nullptr) {
        Flow* f = new T_FLOW(name, orig, dest);
        this->pImpl_->add(f);
        return *f;
    }

    void execute(double time_ini, double time_final) override;

    systemIterator beginSystems() override { return this->pImpl_->beginSystems(); }
    systemIterator endSystems() override { return this->pImpl_->endSystems(); }
    flowIterator beginFlows() override { return this->pImpl_->beginFlows(); }
    flowIterator endFlows() override { return this->pImpl_->endFlows(); }
};


#endif