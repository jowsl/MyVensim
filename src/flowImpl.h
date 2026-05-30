#ifndef FLOWIMPL_H
#define FLOWIMPL_H

#include "flow.h"
#include <string>

using namespace std;

/**
 * @brief Concrete implementation of the Flow interface.
 */

class FlowImpl : public Flow {
    // Permite que a classe de teste unitário acesse os atributos diretamente
    friend class UnitFlow;

protected:
    string name;
    System* origin;
    System* destination;

public:

    /**
     * @brief Construct a new FlowImpl object.
     * Initializes a flow with the given name, origin, and destination.
     * @param name The name of the flow (default is an empty string).
     * @param origin Pointer to the origin system (default is nullptr).
     * @param destination Pointer to the destination system (default is nullptr).
     */
    FlowImpl(string name = "", System* origin = nullptr, System* destination = nullptr);

    /**
     * @brief Destroy the FlowImpl object.
     * Cleans up any resources used by the flow.
     */
    virtual ~FlowImpl();

    /**
     * @brief Construct a new FlowImpl object by copying another flow.
     * @param param_flow The flow to copy from.
     */
    FlowImpl(const FlowImpl& param_flow);

    /**
     * @brief Assign the values of another flow to this flow.
     * @param param_flow The flow to copy from.
     * @return A reference to this flow.
     */
    FlowImpl& operator=(const FlowImpl& param_flow);

    // Sobrescrita dos métodos da Interface
    void setName(string name) override;
    string getName() const override;
    void setOrigin(System* origin) override;
    System* getOrigin() const override;
    void setDestination(System* destination) override;
    System* getDestination() const override;
    
    void connect(System* orig, System* dest) override;
    //Continua virtual puro para o flowimpl ficar abstrato.
    virtual double execute() = 0; 
};

#endif