#include "model.h"

// Default Constructor
Model::Model() {}

// Copy Constructor
Model::Model(const Model& other) {
    this->systems = other.systems;
    this->flows = other.flows;
}

// Destructor
Model::~Model() {}

// Attribution Operator
Model& Model::operator=(const Model& param_model) {
    if (this == &param_model)
        return *this;

    systems = param_model.systems;
    flows = param_model.flows;

    return *this;
}

void Model::add(System* sys) {
    systems.push_back(sys);
}

void Model::add(Flow* flow) {
    flows.push_back(flow);
}

// Iterator implementations
Model::systemIterator Model::beginSystems() {
    return systems.begin();
}

Model::systemIterator Model::endSystems() {
    return systems.end();
}

Model::flowIterator Model::beginFlows() {
    return flows.begin();
}

Model::flowIterator Model::endFlows() {
    return flows.end();
}

void Model::execute(double time_ini, double time_final) {
    for (double tempo = time_ini; tempo < time_final; tempo++) {
        
        // Auxiliar Vector to store temporary results
        vector<double> v(flows.size());
        for (size_t i = 0; i < flows.size(); i++) {
            v[i] = flows[i]->execute();
        }

        // Update values: add on destination and subtracts in origin
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