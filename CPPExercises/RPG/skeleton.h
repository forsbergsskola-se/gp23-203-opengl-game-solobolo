#pragma once
#include "unit.h"

class skeleton : virtual unit
{
public:
    skeleton() : unit("Skeleton", 50)
    {
        cout << "An Infected \033[1;32mSpawned\033[0m with \033[1;34m50 Health\033[0m.\n";
    }

    virtual void takeDamage(int damage) override
    {
        cout << "The attack is very effective!" << endl;
        set_health(get_health() - (damage * 2));
    }
    
};
