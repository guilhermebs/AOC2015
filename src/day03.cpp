#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <array>
#include "helper.hpp"

void solve_pt1()
{
    std::ifstream file("inputs/day03");
    std::string line;
    getline(file, line);
    std::tuple<int, int> cur_pos{0, 0};
    std::unordered_set<std::tuple<int, int>> seen{cur_pos};
    for (auto &c : line)
    {
        switch (c)
        {
        case '^':
            std::get<1>(cur_pos)++;
            break;
        case 'v':
            std::get<1>(cur_pos)--;
            break;
        case '<':
            std::get<0>(cur_pos)--;
            break;
        case '>':
            std::get<0>(cur_pos)++;
            break;
        default:
            break;
        }
        seen.insert(std::tuple(cur_pos));
    }
    std::cout << "Part 1 solution: " << seen.size() << std::endl;
}
 
void solve_pt2()
{
    std::ifstream file("inputs/day03");
    std::string line;
    getline(file, line);
    std::array<std::tuple<int, int>, 2> cur_pos{std::tuple<int, int>({0, 0}), {0, 0}};
    std::unordered_set<std::tuple<int, int>> seen{cur_pos[0]};
    int i = 0;
    for (auto &c : line)
    {
        switch (c)
        {
        case '^':
            std::get<1>(cur_pos[i%2])++;
            break;
        case 'v':
            std::get<1>(cur_pos[i%2])--;
            break;
        case '<':
            std::get<0>(cur_pos[i%2])--;
            break;
        case '>':
            std::get<0>(cur_pos[i%2])++;
            break;
        default:
            break;
        }
        seen.insert(std::tuple(cur_pos[i%2]));
        i++;
    }
    std::cout << "Part 2 solution: " << seen.size() << std::endl;
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}