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
    Model();
    virtual ~Model();

    void add(System* sys);
    void add(Flow* flow);

    void execute(double time_ini, double time_final);
};

#endif