#ifndef FLOW_H
#define FLOW_H

#include "system.h"
#include <string>

using namespace std;

/**
 * @brief Represents a transfer channel between two Systems.
 *
 * A Flow can move value from an origin System to a destination System.
 */
class Flow {
public:
    /**
     * @brief Destroy the Flow object.
     */
    virtual ~Flow() {};

    /**
     * @brief Set the flow name.
     * @param name New flow name.
     */
    virtual void setName(string name) = 0;

    /**
     * @brief Get the flow name.
     * @return string The current name.
     */
    virtual string getName() const = 0;

    /**
     * @brief Set the origin system for this flow.
     * @param origin Origin system pointer.
     */
    virtual void setOrigin(System* origin) = 0;

    /**
     * @brief Get the origin system.
     * @return System* Pointer to the origin system.
     */
    virtual System* getOrigin() const = 0;

    /**
     * @brief Set the destination system for this flow.
     * @param destination Destination system pointer.
     */
    virtual void setDestination(System* destination) = 0;

    /**
     * @brief Get the destination system.
     * @return System* Pointer to the destination system.
     */
    virtual System* getDestination() const = 0;

    /**
     * @brief Connect origin and destination systems.
     * @param orig The origin system.
     * @param dest The destination system.
     */
    virtual void connect(System* orig, System* dest) = 0;

    /**
     * @brief Execute the flow calculation.
     * @return double Amount to transfer from origin to destination.
     */
    virtual double execute() = 0;
};

#endif