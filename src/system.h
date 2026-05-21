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
private:
    string name;
    double value;

public:
    /**
     * @brief Construct a new System object.
     * @param name The name of the system.
     * @param value The initial stored value.
     */
    System(string name = "", double value = 0.0);

    /**
     * @brief Copy constructor.
     * @param param_system The System to copy.
     */
    System(const System& param_system);

    /**
     * @brief Destroy the System object.
     */
    ~System();

    /**
     * @brief Assignment operator.
     * @param outra The System to assign from.
     * @return System& Reference to this object.
     */
    System& operator=(const System& outra);

    /**
     * @brief Set the system name.
     * @param name New name for the system.
     */
    void setName(string name);

    /**
     * @brief Get the system name.
     * @return string The current name.
     */
    string getName() const;

    /**
     * @brief Set the system value.
     * @param value New numeric value for the system.
     */
    void setValue(double value);

    /**
     * @brief Get the current system value.
     * @return double The current numeric value.
     */
    double getValue() const;
};

#endif