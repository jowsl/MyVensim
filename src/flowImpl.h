#ifndef FLOWIMPL_H
#define FLOWIMPL_H

#include "flow.h"
#include <string>
#include "handleBody.h"

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

class FlowBody : public Body {
protected:
    std::string name;
    System* origin;
    System* destination;
public:
    FlowBody(std::string name = "", System* orig = nullptr, System* dest = nullptr) 
        : name(name), origin(orig), destination(dest) {}
    virtual ~FlowBody() {}

    void setOrigin(System* o) { origin = o; }
    System* getOrigin() const { return origin; }
    void setDestination(System* d) { destination = d; }
    System* getDestination() const { return destination; }
    void connect(System* o, System* d) { origin = o; destination = d; }
    void setName(std::string n) { name = n; }
    std::string getName() const { return name; }
    virtual double execute() = 0;
};

// Exemplo de classe de suporte para os fluxos do usuário
template <class T_BODY>
class FlowHandle : public Flow, public Handle<T_BODY> {
public:
    FlowHandle(std::string name = "", System* orig = nullptr, System* dest = nullptr) {
        this->pImpl_->setName(name);
        this->pImpl_->connect(orig, dest);
    }
    virtual ~FlowHandle() {}

    void setOrigin(System* o) override { this->pImpl_->setOrigin(o); }
    System* getOrigin() const override { return this->pImpl_->getOrigin(); }
    void setDestination(System* d) override { this->pImpl_->setDestination(d); }
    System* getDestination() const override { return this->pImpl_->getDestination(); }
    void connect(System* o, System* d) override { this->pImpl_->connect(o, d); }
    void setName(std::string name) override { this->pImpl_->setName(name); }
    std::string getName() const override { return this->pImpl_->getName(); }
    double execute() override { return this->pImpl_->execute(); }
};


#endif