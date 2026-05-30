#ifndef SYSTEMIMPL_H
#define SYSTEMIMPL_H

#include "system.h"
#include <string>

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

#endif