#include "system.h"

// Default Contructor
System::System(string name, double value) {
    this->name = name;
    this->value = value;
}

// Copy Constructor
System::System(const System& param_system){
    this->name  = param_system.name;
    this->value = param_system.value;
}

// Destructor
System::~System() {}

// Attribution Operator
System& System::operator=(const System& outra){
    name = outra.name;
    value = outra.value;

    return *this;
}

// Getters and Setters
void System::setName(string name){
    this->name = name;
}
string System::getName() const{
    return name;
}
void System::setValue(double value){
    this->value = value;
}
double System::getValue() const{ 
    return value;
}