#include <chrono>
#include <string>
#include <iostream>
#include <vector>
#include <numeric>
#include <array>
#include <queue>

const int BOSS_HP = 55;
const int BOSS_DMG = 8;

class GameState
{
    public:
        int player_hp;
        int player_mana;
        int boss_hp;
        int mana_spent;
        GameState(int player_hp, int player_mana, int boss_hp): player_hp(player_hp), player_mana(player_mana), boss_hp(boss_hp) {
            shield_turns = 0;
            poison_turns = 0;
            recharge_turns = 0;
            mana_spent = 0;
            is_player_turn = true;
        }
        inline bool is_victory()  const
        {
            return (player_hp > 0) && (boss_hp <= 0);
        }
        std::vector<GameState> descendents(bool is_pt2) const
        {
            std::vector<GameState> result;
            int boss_hp_eot = boss_hp;
            int player_mana_eot = player_mana;
            int shied_eot = std::max(shield_turns - 1, 0);
            int poison_eot = std::max(poison_turns - 1, 0);
            int recharge_eot = std::max(recharge_turns - 1, 0);
            if (poison_turns > 0) boss_hp_eot -= 3; 
            if (recharge_turns > 0) player_mana_eot += 101;
            if (is_player_turn)
            {
                int player_hp_eot = player_hp - is_pt2;
                if (player_hp_eot <= 0) return result;
                if (player_mana_eot >= 53) 
                    result.push_back(GameState(
                        player_hp_eot, player_mana_eot - 53, boss_hp_eot - 4, shied_eot,
                        poison_eot, recharge_eot, mana_spent + 53, false));
                if (player_mana_eot >= 73) 
                    result.push_back(GameState(
                        player_hp_eot + 2, player_mana_eot - 73, boss_hp_eot - 2, shied_eot,
                        poison_eot, recharge_eot, mana_spent + 73, false));
                if (player_mana_eot >= 113 && (shied_eot == 0)) 
                    result.push_back(GameState(
                        player_hp_eot, player_mana_eot - 113, boss_hp_eot, 6,
                        poison_eot, recharge_eot, mana_spent + 113, false));
                if (player_mana_eot >= 173 && (poison_eot == 0)) 
                    result.push_back(GameState(
                        player_hp_eot, player_mana_eot - 173, boss_hp_eot, shied_eot,
                        6, recharge_eot, mana_spent + 173, false));
                if (player_mana_eot >= 229 && (recharge_eot == 0)) 
                    result.push_back(GameState(
                        player_hp_eot, player_mana_eot - 229, boss_hp_eot, shied_eot,
                        poison_eot, 5, mana_spent + 229, false));
            }
            else if (boss_hp_eot <= 0)
            {
                result.push_back(GameState(
                    player_hp, player_mana_eot, boss_hp_eot, shied_eot,
                    poison_eot, recharge_eot, mana_spent, true));
            }
            else
            {
                int player_hp_eot = player_hp - ((shield_turns > 0)? BOSS_DMG - 7 : BOSS_DMG);
                if (player_hp_eot <= 0) return result;
                result.push_back(GameState(
                    player_hp_eot, player_mana_eot, boss_hp_eot, shied_eot,
                    poison_eot, recharge_eot, mana_spent, true));
            }
            return result;
        }
        bool operator<(const GameState &other) const
        {
            return mana_spent > other.mana_spent;
        }
        void print_state() const
        {
            std::cout << "Player hp: " << player_hp << " mana: " << player_mana << " spent: " << mana_spent << std::endl;;
            std::cout << "Boss hp: " << boss_hp << std::endl;
            std::cout << "Shield: " << shield_turns << " Poison: " << poison_turns << " Recharge: " << recharge_turns << std::endl;
            std::cout << "==============================================" << std::endl;
        }

    private:
        int shield_turns;
        int poison_turns;
        int recharge_turns;
        bool is_player_turn;
        GameState(int player_hp, int player_mana, int boss_hp, int shield_turns, int poison_turns, int recharge_turns, int mana_spent, bool is_player_turn):
            player_hp(player_hp), player_mana(player_mana), boss_hp(boss_hp), mana_spent(mana_spent), shield_turns(shield_turns),
            poison_turns(poison_turns), recharge_turns(recharge_turns), is_player_turn(is_player_turn) {}
};

void solve()
{
    GameState init_state(50, 500, BOSS_HP);
    //GameState init_state(10, 250, 14);
    std::priority_queue<GameState> queue;
    queue.push(init_state);
    int sol_pt1 = INT_MAX;
    while (queue.size())
    {
        auto state = queue.top();
        //state.print_state();
        queue.pop();
        if (state.mana_spent > sol_pt1)
        {
            std::cout << "Part 1 solution: " << sol_pt1 << std::endl;
            break;
        }
        if (state.is_victory())
            sol_pt1 = std::min(sol_pt1, state.mana_spent);
        else
        {
            for (auto &&s : state.descendents(true))
                queue.push(s);
        }
    }
    
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}