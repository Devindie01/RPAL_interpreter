
#include "Environment.h"

Environment::Environment(int id)
{

    this->id = id;
}

Environment::~Environment()
{
}

void Environment::assignParent(Environment *parent)
{
    this->parent = parent;
}

Control *Environment::lookup(string str)
{
    map<string, Control *>::iterator it;
    it = symbolTable.find(str);
    if (symbolTable.end() == it)
        return parent->lookup(str);
    else
        return (*it).second;
}

void Environment::prettyPrint()
{
    map<string, Control *>::iterator it;
    for (it = symbolTable.begin(); symbolTable.end() != it; it++)
        cout << (*it).first << " => " << (*it).second->toStr() << endl;
}
