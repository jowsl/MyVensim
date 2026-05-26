/**
 * @mainpage MyVensim - System Dynamics Simulator
 *
 * @section intro_sec Introduction
 * MyVensim is a generic C++ API designed to simulate System Dynamics models, 
 * closely mirroring behaviors found in professional tools like Vensim. It allows users 
 * to model complex dynamic structures and run continuous numerical integration.
 *
 * @section arch_sec Core Architecture
 * The framework is built upon three fundamental structural blocks:
 * - @b System: Represents stocks (such as material, population, or energy) that store values over time.
 * - @b Flow: Represents the transfer pathways and algebraic differential equations connecting the systems.
 * - @b Model: The orchestration engine responsible for running the simulation timeline and ensuring synchronized updates.
 *
 *
 * @section authors_sec Project Developers
 * - @b Jouberth Matheus Simão Pereira
 * - @b Enzo Bigodeiro Bernardes
 *
 * @note Developed as an academic assignment for the BCC322.
 */


#ifndef MODEL_H
#define MODEL_H

#include "system.h"
#include "flow.h"
#include <vector>

using namespace std;

/**
 * @brief Main class that manages the simulation.
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