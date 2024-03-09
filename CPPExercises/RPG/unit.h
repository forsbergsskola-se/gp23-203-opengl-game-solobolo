#pragma once
#include <algorithm>
#include <iostream>
#include <windows.h>

using namespace std;

class unit
{
public:
    explicit unit(const char* name, const int health) : name_{ name }
    {
        health_ = min(max(health, minHealth_), maxHealth_);
        cout << name << " \033[1;32mspawned\033[0m with \033[1;34m" << health << " Health\033[0m.\n";
    }

    virtual ~unit()
    {
        cout << name_ << " \033[1;31mdied\033[0m.\n";
    }

    virtual void attack(unit& other)
    {
        cout << name_ << " \033[1;31mattacks\033[0m " << other.name_ << ".\n";
        other.takeDamage(1);
    }

    virtual void takeDamage(int damage)
    {
        set_health(get_health() - damage);
    }

    bool is_dead() const { return health_ <= 0; }
    int get_health() const { return health_; }
    void set_health(const int value)
    {
        health_ = min(max(value, minHealth_), maxHealth_);
        cout << name_ << " now has \033[1;34m" << health_ << " Health\033[0m.\n";
    }

private:
    const char* name_;
    double health_;
    double minHealth_ = 0;
    double maxHealth_ = 100;
};

