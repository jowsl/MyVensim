#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>

using namespace std;

/**
 * @brief Represents a stock or reservoir in the simulation.
 *
 * A System stores a name and a numeric value that can be modified by Flows.
 */
class System {
public:

    /**
     * @brief Destroy the System object.
     */
    virtual ~System() {};

    /**
     * @brief Set the system name.
     * @param name New name for the system.
     */
    virtual void setName(string name) = 0;

    /**
     * @brief Get the system name.
     * @return string The current name.
     */
    virtual string getName() const = 0;

    /**
     * @brief Set the system value.
     * @param value New numeric value for the system.
     */
    virtual void setValue(double value) = 0;

    /**
     * @brief Get the current system value.
     * @return double The current numeric value.
     */
    virtual double getValue() const = 0;
};

#endif