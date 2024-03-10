#include <algorithm>
#include <iostream>
#include <windows.h>
#include "unit.h"

using namespace std;

unit* create_hero()
{
    return new unit("\033[1;33mHero\033[0m", 100);
}

unit* create_enemy()
{
    //srand( (unsigned)time( NULL ) );
    float randomRoll = randomFloat();
    cout << randomRoll << endl;
    if (randomRoll < 0.2f)
    {
        return new skeleton();
    }
    else if (randomRoll > 0.5f)
    {
        return new infected();
    }
    else
    {
        return new unit("Enemy", 3);
    }
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
            float randomRoll = randomFloat();
            if (enemy->is_equipped() && randomRoll > 0.5f)
            {
                hero->Drop(enemy->itemDrop());
            }
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
        cin >> should_continue;
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
