#include "modelImpl.h"
#include "systemImpl.h"
#include "handleBody.h"

vector<Model*> ModelImpl::models;

ModelImpl::ModelImpl(string name) {}

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

Model& Model::createModel(string name) { 
    Model* m = new ModelImpl(name); 
    ModelImpl::models.push_back(m); 
    return *m; 
}

System& ModelImpl::createSystem(string id, double qtd) {
    System* s = new SystemImpl(id, qtd); 
    add(s); 
    return *s;
}

// Impl da adição de Systems e Flows
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

std::vector<Model*> ModelHandle::models;

Model& Model::createModel(std::string name) {
    Model* m = new ModelHandle(name);
    ModelHandle::models.push_back(m);
    return *m;
}

ModelBody::ModelBody(std::string name) : name(name) {}

ModelBody::~ModelBody() {
    for (System* s : systems) delete s;
    for (Flow* f : flows) delete f;
    systems.clear();
    flows.clear();
}

System& ModelBody::createSystem(std::string name, double value) {
    System* s = new SystemHandle(name, value);
    add(s);
    return *s;
}

void ModelBody::execute(double time_ini, double time_final) {
    for (double tempo = time_ini; tempo < time_final; tempo++) {
        std::vector<double> v(flows.size());
        for (size_t i = 0; i < flows.size(); i++) {
            v[i] = flows[i]->execute();
        }
        for (size_t i = 0; i < flows.size(); i++) {
            System* orig = flows[i]->getOrigin();
            System* dest = flows[i]->getDestination();
            if (orig != nullptr) orig->setValue(orig->getValue() - v[i]);
            if (dest != nullptr) dest->setValue(dest->getValue() + v[i]);
        }
    }
}

ModelHandle::ModelHandle(std::string name) {}

ModelHandle::~ModelHandle() {
    for (auto it = models.begin(); it != models.end(); ++it) {
        if (*it == this) {
            models.erase(it);
            break;
        }
    }
}

System& ModelHandle::createSystem(std::string name, double value) {
    return this->pImpl_->createSystem(name, value);
}

void ModelHandle::execute(double time_ini, double time_final) {
    this->pImpl_->execute(time_ini, time_final);
}
