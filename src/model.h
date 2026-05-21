#ifndef MODEL_H
#define MODEL_H

#include "system.h"
#include "flow.h"
#include <vector>

using namespace std;

class Model {
private:
    vector<System*> systems;
    vector<Flow*> flows;

public:
    // Iterator definitions
    using flowIterator = vector<Flow*>::iterator;
    using systemIterator = vector<System*>::iterator;

    // Default Constructor
    Model();

    // Copy Constructor
    Model(const Model& other);

    // Destructor
    virtual ~Model();

    // Attribution Operator
    Model& operator=(const Model& other);

    void add(System* sys);
    void add(Flow* flow);

    // Iterator begin/end methods
    systemIterator beginSystems();
    systemIterator endSystems();

    flowIterator beginFlows();
    flowIterator endFlows();

    void execute(double time_ini, double time_final);
};

#endif