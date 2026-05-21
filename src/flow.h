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
private:
    string name;
    System* origin;
    System* destination;

public:
    /**
     * @brief Construct a new Flow object.
     * @param name The flow name.
     * @param origin The source system.
     * @param destination The destination system.
     */
    Flow(string name = "", System* origin = nullptr, System* destination = nullptr);

    /**
     * @brief Copy constructor.
     * @param other The Flow to copy.
     */
    Flow(const Flow& other);

    /**
     * @brief Destroy the Flow object.
     */
    virtual ~Flow();

    /**
     * @brief Assignment operator.
     * @param param_flow The Flow to assign from.
     * @return Flow& Reference to this object.
     */
    Flow& operator=(const Flow& param_flow);

    /**
     * @brief Set the flow name.
     * @param name New flow name.
     */
    void setName(string name);

    /**
     * @brief Get the flow name.
     * @return string The current name.
     */
    string getName() const;

    /**
     * @brief Set the origin system for this flow.
     * @param origin Origin system pointer.
     */
    void setOrigin(System* origin);

    /**
     * @brief Get the origin system.
     * @return System* Pointer to the origin system.
     */
    System* getOrigin() const;

    /**
     * @brief Set the destination system for this flow.
     * @param destination Destination system pointer.
     */
    void setDestination(System* destination);

    /**
     * @brief Get the destination system.
     * @return System* Pointer to the destination system.
     */
    System* getDestination() const;

    /**
     * @brief Connect origin and destination systems.
     * @param orig The origin system.
     * @param dest The destination system.
     */
    void connect(System* orig, System* dest);

    /**
     * @brief Execute the flow calculation.
     * @return double Amount to transfer from origin to destination.
     */
    virtual double execute() = 0;
};

#endif