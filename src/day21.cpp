#include <chrono>
#include <string>
#include <iostream>
#include <vector>
#include <numeric>
#include <array>

struct  Item
{
    int cost;
    int damage;
    int armor;
};

const int BOSS_INIT_HP = 109;
const int BOSS_DMG = 8;
const int BOSS_AMOR = 2;

bool player_wins(const std::array<Item, 4> &items)
{
    int player_dmg = std::accumulate(items.begin(), items.end(), 0, [](const auto &v, const auto &i) { return v + i.damage; });
    int player_armor = std::accumulate(items.begin(), items.end(), 0, [](const auto &v, const auto &i) { return v + i.armor; });
    int boss_hp = BOSS_INIT_HP;
    int player_hp = 100;
    while (player_hp > 0)
    {
        boss_hp -= std::max(player_dmg - BOSS_AMOR, 1);
        if (boss_hp <= 0) return true;
        player_hp -= std::max(BOSS_DMG - player_armor, 1);
    }
    return false; 
}

void solve()
{
    std::vector<Item> weapons{
        {8, 4, 0},
        {10, 5, 0},
        {25, 6, 0},
        {40, 7, 0},
        {74, 8, 0},
    };
    std::vector<Item> armor{
        {13, 0, 1},
        {31, 0, 2},
        {53, 0, 3},
        {75, 0, 4},
        {102, 0, 5},
        {0, 0, 0}
    };
    std::vector<Item> rings{
        {25, 1, 0},
        {50, 2, 0},
        {100, 3, 0},
        {20, 0, 1},
        {40, 0 ,2},
        {80, 0, 3},
        {0, 0, 0},
        {0, 0, 0},
    };


    int min_cost = INT_MAX;
    int max_cost = INT_MIN;
    for (const auto &w: weapons)
    {
        for (const auto &a: armor)
        {
            for (size_t i = 0; i < rings.size() - 1; i++)
            {
                for (size_t j = i + 1; j < rings.size(); j++)
                {
                    const std::array<Item, 4> items = {w, a, rings[i], rings[j]};
                    int cost = std::accumulate(items.begin(), items.end(), 0, [](const auto &v, const auto &i) { return v + i.cost; });
                    if (player_wins(items))
                    {
                        min_cost = std::min(min_cost, cost);
                    } else
                    {
                        max_cost = std::max(max_cost, cost);
                    }
                }
            }
        }
    }
    std::cout << "Part 1 solution: " << min_cost << std::endl;
    std::cout << "Part 2 solution: " << max_cost << std::endl;
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}