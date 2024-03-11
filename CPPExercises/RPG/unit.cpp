#include "unit.h"
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

/*int randomInt()
{
    random_device rd;

    mt19937 gen(rd());

    uniform_real_distribution<int> dis(0, 5);
    
    return dis(gen);
}*/

const string itemNames[] = {"Dagger", "Spear", "Sword", "Axe", "Shield"};

item::item(const char* name, int value) : name_{ name }
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

item::item(const item& other) : name_(other.name_), armor_(other.armor_), damage_(other.damage_)
{
    cout << "Copy constructor invoked for item " << name_ << endl;
}

item::~item()
{
    cout << name_ << " \033[1;31mdestroyed\033[0m.\n";
    name_ = nullptr;
}

item::item(item&& other) noexcept : armor_(other.armor_), damage_(other.damage_), name_(other.name_) {
    cout << "You've just used the move constructor" << endl;
    
    other.armor_ = 0;
    other.damage_ = 0;
}

unit::unit(const char* name, const int health) : name_{ name }
{
    float randomRoll = randomFloat();
    cout << "item roll: " << randomRoll << endl;
    health_ = min(max(health, minHealth_), maxHealth_);
    cout << name << " \033[1;32mspawned\033[0m with \033[1;34m" << health << " Health\033[0m.\n";
    if (randomRoll > 0.6f)
    {
        int randomIndex = randomFloat() * 5;
        cout << "index: " << randomIndex << "\n";
        if (randomRoll > 0.8f)
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

/*item droppedItem = *leftHand; // Using copy constructor
delete leftHand; // Remove the item from leftHand
leftHand = nullptr;*/

item unit::itemDrop() noexcept
{
    if (leftHand != nullptr)
    {
        item droppedItem = *leftHand; // Using copy constructor
        return droppedItem; // Using copy constructor
    }
    else if (rightHand != nullptr)
    {
        item droppedItem = *rightHand; // Using copy constructor
        return droppedItem; // Using copy constructor
    }
    else
    {
        // Return a special "null" item to indicate no item was dropped
        return item{"No item", 0};
    }
}

void unit::Drop(item&& drop)
{
    if (strcmp(drop.name_, "No item") == 0)
    {
        return;
    }
    
    cout << "A " << drop.name_ << " has dropped.\n" << "Currently equipped:\nLeft Hand: "
    << (leftHand != nullptr ? leftHand->name_ : "empty") << "\nRight Hand: "
    << (rightHand != nullptr ? rightHand->name_ : "empty") << endl;
    
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
        cout << drop.name_ << " was dropped." << endl;
    }
}

unit::~unit()
{
    cout << name_ << " \033[1;31mdied\033[0m.\n";
    if(leftHand) delete[] leftHand;
    if(rightHand) delete[] rightHand;
}

void unit::attack(unit& other)
{
    if (leftHand != nullptr && rightHand != nullptr)
    {
        cout << name_ << " \033[1;31mattacks\033[0m " << other.name_ << " with " << leftHand->name_ << " and " << rightHand->name_ << ".\n";
    }
    else if (leftHand != nullptr || rightHand != nullptr)
    {
        cout << name_ << " \033[1;31mattacks\033[0m " << other.name_ << " with " << (leftHand != nullptr ? leftHand->name_ : rightHand->name_) << ".\n";
        int damage = (leftHand != nullptr ? leftHand->damage_ : 0) + (rightHand != nullptr ? rightHand->damage_ : 0) + 1;
        other.takeDamage(damage);
    }
    else
    {
        cout << name_ << " \033[1;31mattacks\033[0m " << other.name_ << " with their hands.\n";
        other.takeDamage(1);
    }
}

void unit::takeDamage(int damage)
{
    int value = 0;
    if (leftHand != nullptr || rightHand != nullptr)
    {
        value = (leftHand != nullptr ? leftHand->armor_ : 0) + (rightHand != nullptr ? rightHand->armor_ : 0);
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

bool unit::is_equipped() const
{
    if (leftHand == NULL && rightHand == NULL)
    {
        return false;
    }
    return true;
}

bool unit::is_dead() const { return health_ <= 0; }

int unit::get_health() const { return health_; }

void unit::set_health(const int value)
{
    health_ = min(max(value, minHealth_), maxHealth_);
    cout << name_ << " now has \033[1;34m" << health_ << " Health\033[0m.\n";
}

skeleton::skeleton() : unit("Skeleton", (randomFloat() * 2) + 3)
{
    cout << "\n";
}

void skeleton::takeDamage(int damage)
{
    cout << "The attack is very effective!" << endl;
    unit::takeDamage(damage * 2);
}

infected::infected() : unit("Infected", 3)
{
    cout << "\n";
}

void infected::takeDamage(int damage)
{
    unit::takeDamage(damage);
    if (this->is_dead() && !_deathrattle)
    {
        cout << "Infected came back from the dead as Zombie with 1 Health." << endl;
        set_health(1);
        name_ = "Zombie";
        _deathrattle = true;
    }
}