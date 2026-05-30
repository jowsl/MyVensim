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
 * - @b System: An interface representing stocks (such as material, population, or energy) that store values over time.
 * - @b Flow: An interface representing the transfer pathways and algebraic differential equations connecting the systems.
 * - @b Model: An interface representing the orchestration engine responsible for running the simulation timeline and ensuring synchronized updates.
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
public:
    // Iterator definitions
    using flowIterator = vector<Flow*>::iterator;
    using systemIterator = vector<System*>::iterator;

    /**
     * @brief Destroy the Model object.
     */
    virtual ~Model() {};


    /**
     * @brief Add a system to the model.
     * @param sys Pointer to the system to add.
     */
    virtual void add(System* sys) = 0;

    /**
     * @brief Add a flow to the model.
     * @param flow Pointer to the flow to add.
     */
    virtual void add(Flow* flow) = 0;

    /**
     * @brief Get iterator to the first system.
     * @return systemIterator Iterator to the beginning of the systems list.
     */
    virtual systemIterator beginSystems() = 0;

    /**
     * @brief Get iterator to one past the last system.
     * @return systemIterator Iterator to the end of the systems list.
     */
    virtual systemIterator endSystems() = 0;

    /**
     * @brief Get iterator to the first flow.
     * @return flowIterator Iterator to the beginning of the flows list.
     */
    virtual flowIterator beginFlows() = 0;

    /**
     * @brief Get iterator to one past the last flow.
     * @return flowIterator Iterator to the end of the flows list.
     */
    virtual flowIterator endFlows() = 0;

    /**
     * @brief Execute the model simulation for a time interval.
     * @param time_ini Initial simulation time.
     * @param time_final Final simulation time.
     */
    virtual void execute(double time_ini, double time_final) = 0;
};

#endif