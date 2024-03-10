#pragma once

#include <string>

float randomFloat();

extern const std::string itemNames[];

class item
{
protected:
public:
    const char* name_;
    int armor_ = 0;
    int damage_ = 0;

    explicit item(const char* name, int value);
    item(const item& other); // Copy constructor
    virtual ~item();
    item(item&& other) noexcept;
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
    explicit unit(const char* name, const int health);
    virtual item itemDrop() noexcept;
    virtual void Drop(item&& drop);
    virtual ~unit();
    virtual void attack(unit& other);
    virtual void takeDamage(int damage);
    bool is_equipped() const;
    bool is_dead() const;
    int get_health() const;
    virtual void set_health(const int value);
};

class skeleton : virtual public unit
{
public:
    skeleton();
    virtual void takeDamage(int damage) override;
};

class infected : virtual public unit
{
    bool _deathrattle = false;
public:
    infected();
    virtual void takeDamage(int damage) override;
};


