
#ifndef RPAL_COMPILER_ENVIRONMENT_H_
#define RPAL_COMPILER_ENVIRONMENT_H_

#include <map>
#include <string>
#include "Control.h"

using namespace std;

class Environment
{
public:
    int id;
    Environment *parent; 
    void assignParent(Environment *);
    Control *lookup(string);
    void prettyPrint();
    Environment(int);
    virtual ~Environment();
    map<string, Control *> symbolTable;
};

#endif 
