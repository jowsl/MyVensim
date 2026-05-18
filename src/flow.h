#ifndef FLOW_H
#define FLOW_H

#include "system.h"
#include <string>

using namespace std;

class Flow {
private:
    string name;
    System* origin;
    System* destination;

public:
    // Construtor
    Flow(string name = "");
    virtual ~Flow();

    // Getters e Setters
    void setName(string name);
    string getName() const;

    void setOrigin(System* origin);
    System* getOrigin() const;

    void setDestination(System* destination);
    System* getDestination() const;

    // Conecta origem e destino de uma vez
    void connect(System* orig, System* dest);

    // Método virtual puro (torna a classe abstrata)
    virtual double execute() = 0; 
};

#endif