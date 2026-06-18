#ifndef SYSTEMIMPL_H
#define SYSTEMIMPL_H

#include "system.h"
#include <string>
#include "handleBody.h"

using namespace std;

/**
 * @brief Concrete implementation of the System interface.
 */

class SystemImpl : public System {
    //Permite que a classe de teste unitário acesse 'name' e 'value' diretamente
    friend class UnitSystem;

protected:
    string name;
    double value;

public:

    /**
     * @brief Construct a new SystemImpl object.
     * Initializes a system with the given name and value.
     * @param name The name of the system (default is an empty string).
     * @param value The initial numeric value of the system (default is 0.0
     */
    SystemImpl(string name = "", double value = 0.0);

    /**
     * @brief Destroy the SystemImpl object.
     * Cleans up any resources used by the system.
     */
    virtual ~SystemImpl();

    /**
     * @brief Construct a new SystemImpl object by copying another system.
     * @param param_system The system to copy from.
     */
    SystemImpl(const SystemImpl& param_system);

    /**
     * @brief Assign the values of another system to this system.
     * @param param_system The system to copy from.
     * @return A reference to this system.
     */
    SystemImpl& operator=(const SystemImpl& param_system);

    //Sobrescrita dos métodos virtuais da interface System
    void setName(string name) override;
    string getName() const override;
    void setValue(double value) override;
    double getValue() const override;
};

class SystemBody : public Body {
protected:
    std::string name;
    double value;
public:
    SystemBody(std::string name = "", double value = 0.0) : name(name), value(value) {}
    virtual ~SystemBody() {}

    double getValue() const { return value; }
    void setValue(double v) { value = v; }
    std::string getName() const { return name; }
    void setName(std::string n) { name = n; }
};

class SystemHandle : public System, public Handle<SystemBody> {
public:
    SystemHandle(std::string name = "", double value = 0.0) {
        pImpl_->setName(name);
        pImpl_->setValue(value);
    }
    virtual ~SystemHandle() {}

    double getValue() const override { return pImpl_->getValue(); }
    void setValue(double value) override { pImpl_->setValue(value); }
    std::string getName() const override { return pImpl_->getName(); }
    void setName(std::string name) override { pImpl_->setName(name); }
};


#endif