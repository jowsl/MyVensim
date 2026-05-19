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

    //definição dos iterators
    using flowIterator = vector<Flow*>::iterator;
    using systemIterator = vector<System*>::iterator;

    Model();
    virtual ~Model();

    void add(System* sys);
    void add(Flow* flow);

    //metodos de incio e fim dos iterators
    systemIterator beginSystems();
    systemIterator endSystems();

    flowIterator beginFlows();  
    flowIterator endFlows();
    
    void execute(double time_ini, double time_final);
};

#endif