#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>

using namespace std;

class System {
private:
    string name;
    double value;

public:
    System(string name = "", double value = 0.0);
    virtual ~System();

    void setName(string name);
    string getName() const;

    void setValue(double value);
    double getValue() const;
};

#endif