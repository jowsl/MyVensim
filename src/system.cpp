#include "system.h"

System::System(string name, double value) : name(name), value(value) {}

System::~System() {}

void System::setName(string name) { this->name = name; }
string System::getName() const { return name; }

void System::setValue(double value) { this->value = value; }
double System::getValue() const { return value; }