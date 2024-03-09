#pragma once
#include "unit.h"

class infected : virtual public unit
{
    bool _deathrattle = true;
public:
    infected() : unit("Infected", 50)
    {
        cout << "A Skeleton \033[1;32mSpawned\033[0m with \033[1;34m50 Health\033[0m.\n";
    }

    virtual void takeDamage(int damage) override
    {
        set_health(get_health() - damage);
        if (this->is_dead())
        {
            cout << "Infected came back from the dead as Zombie with 1 Health." << endl;
            set_health(1);
            name_ = "Zombie";
            _deathrattle = true;
        }
    }
};

