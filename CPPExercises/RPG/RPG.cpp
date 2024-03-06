#include <algorithm>
#include <iostream>
#include <windows.h>

using namespace std;

class unit
{
public:
    explicit unit(const char* name, const int health) : name_{ name }
    {
        double minHealth = 0;
        double maxHealth = 100;
        health_ = min(std::max(health, minHealth), maxHealth));
        cout << name << " \033[1;32mspawned\033[0m with \033[1;34m" << health << " Health\033[0m.\n";
    }

    ~unit()
    {
        cout << name_ << " \033[1;31mdied\033[0m.\n";
    }

    void attack(unit& other)
    {
        cout << name_ << " \033[1;31mattacks\033[0m " << other.name_ << ".\n";
        other.set_health(other.get_health() - 1);
    }

    bool is_dead() const { return health_ <= 0; }
    int get_health() const { return health_; }
    void set_health(const int value)
    {
        health_ = min(std::max(value, min), max));
        cout << name_ << " now has \033[1;34m" << health_ << " Health\033[0m.\n";
    }

private:
    const char* name_;
    int health_;
};

unit* create_hero()
{
    return new unit("\033[1;33mHero\033[0m", 100);
}

unit* create_enemy()
{
    return new unit("Enemy", 3);
}

int main()
{
    // initialization
    unit* hero = create_hero();
    unit* enemy = create_enemy();
    int killed_monster_count{};
    char should_continue;

    // game loop
    do
    {
        // hero's turn
        Sleep(400);
        hero->attack(*enemy);
        Sleep(800);

        if (enemy->is_dead())
        {
            // spawn new enemy
            delete enemy;
            cout << "\033[1;36mYou killed a total of " << ++killed_monster_count << " Monsters!\033[0m\n";
            cout << "\n";
            enemy = create_enemy();
        }
        else // (if !enemy->is_dead())
        {
            // enemy's turn
            cout << "\n";
            enemy->attack(*hero);
        }

        // choice to continue
        Sleep(800);
        cout << "\n";
        cout << "Do you want to continue? y/n\n";
        cin >> should_continue
    } while (should_continue == 'y');

        // good game
        cout << "Thanks for playing!" << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
