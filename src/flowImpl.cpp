#include "flowImpl.h"

FlowImpl::FlowImpl(string name, System* origin, System* destination) 
    : name(name), origin(origin), destination(destination) {}
FlowImpl::~FlowImpl() {}

FlowImpl::FlowImpl(const FlowImpl& param_flow) {
    this->name = param_flow.name;
    this->origin = param_flow.origin;
    this->destination = param_flow.destination;
}

FlowImpl& FlowImpl::operator=(const FlowImpl& param_flow) {
    if (this == &param_flow) { // Evita auto-atribuição
        return *this;
    }
    this->name = param_flow.name;
    this->origin = param_flow.origin;
    this->destination = param_flow.destination;
    
    return *this;
}

void FlowImpl::setName(string name) {
    this->name = name;
}

string FlowImpl::getName() const {
    return name;
}

void FlowImpl::setOrigin(System* origin) {
    this->origin = origin;
}

System* FlowImpl::getOrigin() const {
    return origin;
}

void FlowImpl::setDestination(System* destination) {
    this->destination = destination;
}

System* FlowImpl::getDestination() const {
    return destination;
}

// Impl do connect
void FlowImpl::connect(System* orig, System* dest) {
    this->origin = orig;
    this->destination = dest;
}