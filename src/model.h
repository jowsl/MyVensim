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
#include <string>

using namespace std;

/**
 * @brief Main class that manages the simulation.
 * The Model acts as the simulation engine, storing stocks (Systems)
 * and transfer channels (Flows).
 */

class UnitModel;

class Model {

friend class UnitModel;

protected:
    /**
     * @brief Add a system to the model.
     * Protected to enforce the use of the Factory Method (createSystem).
     * @param sys Pointer to the system to add.
     */
    virtual void add(System* sys) = 0;

    /**
     * @brief Add a flow to the model.
     * Protected to enforce the use of the Factory Method (createFlow).
     * @param flow Pointer to the flow to add.
     */
    virtual void add(Flow* flow) = 0;

public:
    // Iterator definitions
    using flowIterator = vector<Flow*>::iterator;
    using systemIterator = vector<System*>::iterator;

    /**
     * @brief Destroy the Model object.
     */
    virtual ~Model() {};

    static Model& createModel();
    /**
     * @brief Factory Method to create a System.
     * @param name Name of the system.
     * @param value Initial value of the system.
     * @return System& Reference to the created system.
     */
    virtual System& createSystem(string name, double value) = 0;

    
    /**
     * @brief Factory Method to create a Flow using Generics (Templates).
     * Instantiates a generic flow of type T_FLOW, connects it, and adds it to the model.
     * @tparam T_FLOW The specific concrete class of the flow (e.g., ExponentialFlow).
     * @param name Name of the flow.
     * @param orig Pointer to the origin system.
     * @param dest Pointer to the destination system.
     * @return Flow& Reference to the created flow.
     */
    
    template <typename T_FLOW>
    Flow& createFlow(string name, System* orig = nullptr, System* dest = nullptr) {
        // A fábrica instancia o tipo genérico, conecta e armazena na coleção protegida
        Flow* f = new T_FLOW(name);
        f->connect(orig, dest);
        add(f); 
        return *f;
    }

    /**
     * @brief Clears all systems and flows from the model.
     * Essential for resetting the Singleton state between tests.
     */
    virtual void clear() = 0;

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