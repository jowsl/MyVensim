#include "modelImpl.h"

ModelImpl::ModelImpl() {}
ModelImpl::~ModelImpl() {}

ModelImpl::ModelImpl(const ModelImpl& param_model) {
    this->systems = param_model.systems;
    this->flows = param_model.flows;
}

ModelImpl& ModelImpl::operator=(const ModelImpl& param_model) {
    if (this == &param_model) {
        return *this;
    }
    this->systems = param_model.systems;
    this->flows = param_model.flows;
    
    return *this;
}

//Impl da adição de Systems e Flows
void ModelImpl::add(System* sys) {
    systems.push_back(sys);
}

void ModelImpl::add(Flow* flow) {
    flows.push_back(flow);
}

// Implementação dos Iteradores de System
Model::systemIterator ModelImpl::beginSystems() {
    return systems.begin();
}
Model::systemIterator ModelImpl::endSystems() {
    return systems.end();
}

// Implementação dos Iteradores de Flow
Model::flowIterator ModelImpl::beginFlows() {
    return flows.begin();
}
Model::flowIterator ModelImpl::endFlows() {
    return flows.end();
}

// execução do modelo
void ModelImpl::execute(double time_ini, double time_final) {
    for (double tempo = time_ini; tempo < time_final; tempo++) {
        
        vector<double> v(flows.size());

        for (size_t i = 0; i < flows.size(); i++) {
            v[i] = flows[i]->execute();
        }

        for (size_t i = 0; i < flows.size(); i++) {
            System* orig = flows[i]->getOrigin();
            System* dest = flows[i]->getDestination();

            if (orig != nullptr) {
                orig->setValue(orig->getValue() - v[i]);
            }

            if (dest != nullptr) {
                dest->setValue(dest->getValue() + v[i]);
            }
        }
    }
}