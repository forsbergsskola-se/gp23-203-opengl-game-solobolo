#pragma once
#include "unit.h"

class skeleton : virtual public unit
{
public:
    skeleton() : unit("Skeleton", 50)
    {
        cout << "An Infected \033[1;32mSpawned\033[0m with \033[1;34m50 Health\033[0m.\n";
    }

    virtual void takeDamage(int damage) override
    {
        cout << "The attack is very effective!" << endl;
        int value = 0;
        damage = damage * 2;
        if (leftHand != nullptr || rightHand != nullptr)
        {
            value = (leftHand->armor_ + rightHand->armor_);
            if (damage - value < 1)
            {
                set_health(get_health() - 1);
                return;
            }
            set_health(get_health() - (damage - value));
            return;
        }
        set_health(get_health() - damage);
    }
    
};
