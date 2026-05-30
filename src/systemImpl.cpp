#include "systemImpl.h"

//construtor
SystemImpl::SystemImpl(string name, double value) : name(name), value(value) {}

//Destrutor
SystemImpl::~SystemImpl() {}

//Construtor de Cópia
SystemImpl::SystemImpl(const SystemImpl& param_system) {
    this->name = param_system.name;
    this->value = param_system.value;
}

//Operador de Atribuição
SystemImpl& SystemImpl::operator=(const SystemImpl& param_system) {
    if (this == &param_system) {//evita atribuição para si mesmo
        return *this;
    }
    this->name = param_system.name;
    this->value = param_system.value;
    
    return *this;
}

//sobrescritas dos métodos virtuais da interface System
void SystemImpl::setName(string name) {
    this->name = name;
}

string SystemImpl::getName() const {
    return name;
}

void SystemImpl::setValue(double value) {
    this->value = value;
}

double SystemImpl::getValue() const {
    return value;
}