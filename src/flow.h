#ifndef FLOW_H
#define FLOW_H

#include "system.h"
#include <string>

using namespace std;

class Flow {
private:
    string name;
    System* origin;
    System* destination;

public:
    // Default Constructor
    Flow(string name = "", System* origin = nullptr, System* destination = nullptr);

    // Copy Constructor
    Flow(const Flow& other);

    // Destructor
    virtual ~Flow();

    // Attribution Operator
    Flow& operator=(const Flow& other);

    // Getters and Setters
    void setName(string name);
    string getName() const;

    void setOrigin(System* origin);
    System* getOrigin() const;

    void setDestination(System* destination);
    System* getDestination() const;

    // Connect origin and destination
    void connect(System* orig, System* dest);

    // Pure virtual method
    virtual double execute() = 0;
};

#endif