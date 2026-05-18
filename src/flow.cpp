#include "flow.h"

// Inicializa com ponteiros nulos
Flow::Flow(string name) : name(name), origin(nullptr), destination(nullptr) {}

Flow::~Flow() {}

void Flow::setName(string name) { this->name = name; }
string Flow::getName() const { return name; }

void Flow::setOrigin(System* origin) { this->origin = origin; }
System* Flow::getOrigin() const { return origin; }

void Flow::setDestination(System* destination) { this->destination = destination; }
System* Flow::getDestination() const { return destination; }

void Flow::connect(System* orig, System* dest) {
    this->origin = orig;
    this->destination = dest;
}