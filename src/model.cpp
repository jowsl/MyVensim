#include "model.h"

Model::Model() {}

Model::~Model() {}

void Model::add(System* sys) {
    systems.push_back(sys);
}

void Model::add(Flow* flow) {
    flows.push_back(flow);
}

void Model::execute(double time_ini, double time_final) {
    //loop principal
    for (double tempo = time_ini; tempo < time_final; tempo++) {
        
        //vetor para armazenar os resultados temporarios de cada fluxo
        vector<double> v(flows.size());

        //executa a função de dado fluxo e armazena o resultado no vetor
        for (size_t i = 0; i < flows.size(); i++) {
            v[i] = flows[i]->execute();
        }

        //Atualiza os estoques (subtrai origem, soma destino) 
        for (size_t i = 0; i < flows.size(); i++) {
            System* orig = flows[i]->getOrigin();
            System* dest = flows[i]->getDestination();

            //subtrai se a origem não for a nullptr
            if (orig != nullptr) {
                orig->setValue(orig->getValue() - v[i]);
            }

            //soma se o destino não for nullptr
            if (dest != nullptr) {
                dest->setValue(dest->getValue() + v[i]);
            }
        }
    }
}