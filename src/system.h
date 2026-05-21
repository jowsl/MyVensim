#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>

using namespace std;

class System {
private:
    string name;
    double value;

public:
    // Default Contructor
    System(string name = "", double value = 0.0);

    // Copy Constructor
    System(const System& param_system);

    // Destructor
    ~System();

    // Attribution Operator
    System& operator=(const System& outra);

    // Getters and Setters
    void setName(string name);
    string getName() const;
    void setValue(double value);
    double getValue() const;
};

#endif