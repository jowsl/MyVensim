#include "flow.h"

// Default Constructor
Flow::Flow(string name, System* origin, System* destination) {
    this->name = name;
    this->origin = origin;
    this->destination = destination;
}

// Copy Constructor
Flow::Flow(const Flow& other) {
    this->name = other.name;
    this->origin = other.origin;
    this->destination = other.destination;
}

// Destructor
Flow::~Flow() {}

// Attribution Operator
Flow& Flow::operator=(const Flow& param_flow) {
    if (this == &param_flow)
        return *this;
    name = param_flow.name;
    origin = param_flow.origin;
    destination = param_flow.destination;

    return *this;
}

// Getters and Setters
void Flow::setName(string name) {
    this->name = name;
}

string Flow::getName() const {
    return name;
}

void Flow::setOrigin(System* origin) {
    this->origin = origin;
}

System* Flow::getOrigin() const {
    return origin;
}

void Flow::setDestination(System* destination) {
    this->destination = destination;
}

System* Flow::getDestination() const {
    return destination;
}

void Flow::connect(System* orig, System* dest) {
    this->origin = orig;
    this->destination = dest;
}