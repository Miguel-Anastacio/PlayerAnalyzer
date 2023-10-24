#pragma once
struct Role;
#include <vector>
class State
{
public:
    State();
    ~State();

    //virtual void Execute() {};
    virtual void Execute(const std::vector<Role>& allRoles) {};

};

