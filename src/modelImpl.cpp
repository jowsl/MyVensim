#include "modelImpl.h"
#include "systemImpl.h"

ModelImpl::ModelImpl() {}

ModelImpl::~ModelImpl() {
    // Reaproveita a lógica do clear para evitar repetição de código
    clear();
}

void ModelImpl::clear() {
    // Deleta a memória alocada na RAM antes de esvaziar os vetores
    for (System* s : systems) {
        delete s;
    }
    for (Flow* f : flows) {
        delete f;
    }
    // Esvazia os vetores
    systems.clear();
    flows.clear();
}

Model& Model::createModel() {
    return ModelImpl::getInstance();
}

System& ModelImpl::createSystem(string id, double qtd) {
    System* s = new SystemImpl(id, qtd); // A fábrica dá o 'new'
    add(s); // Guarda no vetor interno
    return *s; // Retorna a interface como referência
}

// Impl da adição de Systems e Flows (agora protegidos)
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

// Execução do modelo
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