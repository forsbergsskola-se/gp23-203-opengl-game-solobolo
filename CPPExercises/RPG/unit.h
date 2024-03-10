#pragma once
#include <algorithm>
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

class item
{

protected:
    
public:
    const char* name_;
    int armor_;
    int damage_;
    
    explicit item(const char* name, int value) : name_{ name }
    {
        if (strcmp(name, "Shield") != 0)
        {
            damage_ = value;
        }
        else
        {
            armor_ = value;
        }
    }

    virtual ~item()
    {
        cout << name_ << " \033[1;31mdied\033[0m.\n";
    }

    item(item&& other) noexcept : armor_(other.armor_), damage_(other.damage_), name_(other.name_) {
        cout << "You've just used the move constructor" << endl;

        other.name_ = nullptr;
        other.armor_ = 0;
        other.damage_ = 0;
    }
};

const string itemNames[] = {"Dagger", "Spear", "Sword", "Axe", "Shield"};
int arraySize = itemNames->capacity();

class unit
{
protected:
    const char* name_;
    const item* leftHand;
    const item* rightHand;

private:
    double health_;
    double minHealth_ = 0;
    double maxHealth_ = 100;
public:
    explicit unit(const char* name, const int health) : name_{ name }
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        float randomRoll;
        randomRoll = (float)rand() / RAND_MAX;
        health_ = min(max(health, minHealth_), maxHealth_);
        if (randomRoll > 0.7f)
        {
            int randomIndex = rand() % arraySize;
            if (randomRoll > 0.85f)
            {
                rightHand = new item{(itemNames[randomIndex].c_str()), 2};
            }
            else
            {
                leftHand = new item{(itemNames[randomIndex].c_str()), 2};
            }
        }
        cout << name << " \033[1;32mspawned\033[0m with \033[1;34m" << health << " Health\033[0m.\n";
    }

    virtual ~unit()
    {
        cout << name_ << " \033[1;31mdied\033[0m.\n";
    }

    virtual void attack(unit& other)
    {
        if (leftHand != nullptr && rightHand != nullptr)
        {
            cout << name_ << " \033[1;31mattacks\033[0m " << other.name_ << "with " << leftHand->name_ << " and " << rightHand->name_ << ".\n";
        }
        if (leftHand != nullptr || rightHand != nullptr)
        {
            cout << name_ << " \033[1;31mattacks\033[0m " << other.name_ << "with " << (leftHand != nullptr ? leftHand->name_ : rightHand->name_) << ".\n";
            int damage = leftHand->damage_;
            other.takeDamage(leftHand->damage_ + rightHand->damage_ + 1);
        }
        else
        {
            cout << name_ << " \033[1;31mattacks\033[0m " << other.name_ << "with their hands.\n";
            other.takeDamage(1);
        }
    }

    virtual void takeDamage(int damage)
    {
        int value;
        if (leftHand != nullptr || rightHand != nullptr)
        {
        value = (leftHand->armor_ + rightHand->armor_ + 1);
        }
        set_health(get_health() - damage);
    }

    bool is_dead() const { return health_ <= 0; }
    int get_health() const { return health_; }
    virtual void set_health(const int value)
    {
        health_ = min(max(value, minHealth_), maxHealth_);
        cout << name_ << " now has \033[1;34m" << health_ << " Health\033[0m.\n";
    }
};



