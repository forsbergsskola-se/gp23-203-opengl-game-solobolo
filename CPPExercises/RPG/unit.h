#pragma once
#include <algorithm>
#include <iostream>
#include <windows.h>
#include <string>
#include <random>

using namespace std;

float randomFloat() {
    // Create random device to seed the RNG
    random_device rd;
    
    // Create RNG
    mt19937 gen(rd());
    
    // Create uniform distribution between 0 and 1
    uniform_real_distribution<float> dis(0.0f, 1.0f);
    
    // Return random float between 0 and 1
    return dis(gen);
}

const string itemNames[] = {"Dagger", "Spear", "Sword", "Axe", "Shield"};
//int arraySize = itemNames->capacity();

class item
{

protected:
    
public:
    const char* name_;
    int armor_ = 0;
    int damage_ = 0;
    
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

class unit
{
protected:
    const char* name_;
    item* leftHand;
    item* rightHand;

private:
    int health_;
    int minHealth_ = 0;
    int maxHealth_ = 100;
public:
    explicit unit(const char* name, const int health) : name_{ name }
    {
        float randomRoll = randomFloat();
        cout << "item roll: " << randomRoll << endl;
        health_ = min(max(health, minHealth_), maxHealth_);
        cout << name << " \033[1;32mspawned\033[0m with \033[1;34m" << health << " Health\033[0m.\n";
        if (randomRoll > 0.7f)
        {
            int randomIndex = rand() % 5;
            if (randomRoll > 0.85f)
            {
                rightHand = new item{(itemNames[randomIndex].c_str()), 2};
                cout << name << " \033[1;32mspawned\033[0m with a \033[1;34m" << rightHand->name_ << " in their right hand\033[0m.\n";
            }
            else
            {
                leftHand = new item{(itemNames[randomIndex].c_str()), 2};
                cout << name << " \033[1;32mspawned\033[0m with a \033[1;34m" << leftHand->name_ << " in their left hand\033[0m.\n";
            }
        }
    }

    virtual item itemDrop() noexcept
    {
        if (rand() % 2 == 0 && leftHand != nullptr)
        {
            item droppedItem = std::move(*leftHand);
            leftHand = nullptr; // Remove the item from leftHand
            return droppedItem;
        }
        else if (rightHand != nullptr)
        {
            item droppedItem = std::move(*rightHand);
            rightHand = nullptr; // Remove the item from rightHand
            return droppedItem;
        }
        else
        {
            // Return a special "null" item to indicate no item was dropped
            return item{"No item", 0};
        }
    }

    virtual void Drop(item&& drop)
    {
        cout << "A " << drop.name_ << " has dropped.\n" << "Currently equipped:\nLeft Hand: " << leftHand->name_ << "\nRight Hand: " << rightHand->name_ << endl;
        cout << "Equip to (L)eft Hand, (R)ight Hand or (D)rop?\n";
        char input;
        bool validInput = false;
        while (!validInput) {
            cin >> input;
            if (input == 'L' || input == 'R' || input == 'D') {
                validInput = true;
            } else {
                cout << "Invalid input. Please enter 'L', 'R', or 'D'." << endl;
            }
        }
        if (input == 'L')
        {
            leftHand = new item{std::move(drop)};
            cout << "Equipped " << leftHand->name_ << " to Left Hand." << endl;
        }
        if (input == 'R')
        {
            rightHand = new item{std::move(drop)};
            cout << "Equipped " << rightHand->name_ << " to Right Hand." << endl;
        }
        if (input == 'D')
        {
            cout << drop.name_ << "was dropped." << endl;
        }
    }

    virtual ~unit()
    {
        cout << name_ << " \033[1;31mdied\033[0m.\n";
        if (true)
        {
            
        }
    }

    virtual void attack(unit& other)
    {
        if (leftHand != nullptr && rightHand != nullptr)
        {
            cout << name_ << " \033[1;31mattacks\033[0m " << other.name_ << " with " << leftHand->name_ << " and " << rightHand->name_ << ".\n";
        }
        if (leftHand != nullptr || rightHand != nullptr)
        {
            cout << name_ << " \033[1;31mattacks\033[0m " << other.name_ << " with " << (leftHand != nullptr ? leftHand->name_ : rightHand->name_) << ".\n";
            int damage = leftHand->damage_;
            other.takeDamage(leftHand->damage_ + rightHand->damage_ + 1);
        }
        else
        {
            cout << name_ << " \033[1;31mattacks\033[0m " << other.name_ << " with their hands.\n";
            other.takeDamage(1);
        }
    }

    virtual void takeDamage(int damage)
    {
        int value = 0;
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

    bool is_equipped() const
    {
        if (leftHand != nullptr && rightHand != nullptr)
        {
            return false;
        }
        return true;
    }
    bool is_dead() const { return health_ <= 0; }
    int get_health() const { return health_; }
    virtual void set_health(const int value)
    {
        health_ = min(max(value, minHealth_), maxHealth_);
        cout << name_ << " now has \033[1;34m" << health_ << " Health\033[0m.\n";
    }   
};

class skeleton : virtual public unit
{
public:
    skeleton() : unit("Skeleton", 3)
    {
        cout << "An Infected \033[1;32mSpawned\033[0m with \033[1;34m3 Health\033[0m.\n";
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

class infected : virtual public unit
{
    bool _deathrattle = true;
public:
    infected() : unit("Infected", 3)
    {
        cout << "A Skeleton \033[1;32mSpawned\033[0m with \033[1;34m3 Health\033[0m.\n";
    }

    virtual void takeDamage(int damage) override
    {
        int value = 0;
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
        if (this->is_dead() && !_deathrattle)
        {
            cout << "Infected came back from the dead as Zombie with 1 Health." << endl;
            set_health(1);
            name_ = "Zombie";
            _deathrattle = true;
        }
    }
};



