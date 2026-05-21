#ifndef MODEL_H
#define MODEL_H

#include "system.h"
#include "flow.h"
#include <vector>

using namespace std;

/**
 * @brief Main class that manages the simulation.
 *
 * The Model acts as the simulation engine, storing stocks (Systems)
 * and transfer channels (Flows).
 */
class Model {
private:
    vector<System*> systems;
    vector<Flow*> flows;

public:
    // Iterator definitions
    using flowIterator = vector<Flow*>::iterator;
    using systemIterator = vector<System*>::iterator;

    /**
     * @brief Construct a new Model object.
     */
    Model();

    /**
     * @brief Copy constructor.
     * @param other The Model to copy.
     */
    Model(const Model& other);

    /**
     * @brief Destroy the Model object.
     */
    virtual ~Model();

    /**
     * @brief Assignment operator.
     * @param param_model The Model to assign from.
     * @return Model& Reference to this object.
     */
    Model& operator=(const Model& param_model);

    /**
     * @brief Add a system to the model.
     * @param sys Pointer to the system to add.
     */
    void add(System* sys);

    /**
     * @brief Add a flow to the model.
     * @param flow Pointer to the flow to add.
     */
    void add(Flow* flow);

    /**
     * @brief Get iterator to the first system.
     * @return systemIterator Iterator to the beginning of the systems list.
     */
    systemIterator beginSystems();

    /**
     * @brief Get iterator to one past the last system.
     * @return systemIterator Iterator to the end of the systems list.
     */
    systemIterator endSystems();

    /**
     * @brief Get iterator to the first flow.
     * @return flowIterator Iterator to the beginning of the flows list.
     */
    flowIterator beginFlows();

    /**
     * @brief Get iterator to one past the last flow.
     * @return flowIterator Iterator to the end of the flows list.
     */
    flowIterator endFlows();

    /**
     * @brief Execute the model simulation for a time interval.
     * @param time_ini Initial simulation time.
     * @param time_final Final simulation time.
     */
    void execute(double time_ini, double time_final);
};

#endif