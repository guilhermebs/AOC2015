#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <bitset>
#include <regex>
#include <array>
#include <numeric>

const size_t SIZE = 1000;

void solve_pt1()
{
    std::ifstream file("inputs/day06");
    std::string line;
    static std::regex turn_on("turn on (\\d+),(\\d+) through (\\d+),(\\d+)");
    static std::regex turn_off("turn off (\\d+),(\\d+) through (\\d+),(\\d+)");
    static std::regex toggle("toggle (\\d+),(\\d+) through (\\d+),(\\d+)");
    std::smatch sm;
    std::bitset<SIZE * SIZE> lamps;
    while (getline(file, line))
    {
        std::array<int, 4> coords;
        int op = 0;
        if (std::regex_match(line, sm, turn_on))
            op = 1;
        else if (std::regex_match(line, sm, turn_off))
            op = 2;
        else if (std::regex_match(line, sm, toggle))
            op = 3;
        else
            std::cout << line << std::endl;
        for (size_t i = 0; i < 4; i++)
        {
            coords[i] = std::stoi(sm[i+1]);
        }
        for (int y=coords[1]; y <= coords[3]; y++)
        {
            for (int x=coords[0]; x <= coords[2]; x++)
            {
                switch (op)
                {
                case 1:
                    lamps.set(x + SIZE * y, true);
                    break;
                case 2:
                    lamps.set(x + SIZE * y, false);
                    break;
                case 3:
                    lamps.flip(x + SIZE * y);
                    break;
                default:
                    std::cout << op << std::endl;
                    break;
                }
            }
        }
    }
    std::cout << "Part 1 solution: " << lamps.count() << std::endl;
}

void solve_pt2()
{
    std::ifstream file("inputs/day06");
    std::string line;
    static std::regex turn_on("turn on (\\d+),(\\d+) through (\\d+),(\\d+)");
    static std::regex turn_off("turn off (\\d+),(\\d+) through (\\d+),(\\d+)");
    static std::regex toggle("toggle (\\d+),(\\d+) through (\\d+),(\\d+)");
    std::smatch sm;
    std::vector<int> lamps(SIZE * SIZE, 0);
    while (getline(file, line))
    {
        std::array<int, 4> coords;
        int op = 0;
        if (std::regex_match(line, sm, turn_on))
            op = 1;
        else if (std::regex_match(line, sm, turn_off))
            op = 2;
        else if (std::regex_match(line, sm, toggle))
            op = 3;
        else
            std::cout << line << std::endl;
        for (size_t i = 0; i < 4; i++)
        {
            coords[i] = std::stoi(sm[i+1]);
        }
        for (int y=coords[1]; y <= coords[3]; y++)
        {
            for (int x=coords[0]; x <= coords[2]; x++)
            {
                switch (op)
                {
                case 1:
                    lamps[x + SIZE * y]++;
                    break;
                case 2:
                    lamps[x + SIZE * y] = std::max(lamps[x + SIZE * y] - 1, 0);
                    break;
                case 3:
                    lamps[x + SIZE * y] += 2;
                    break;
                default:
                    std::cout << op << std::endl;
                    break;
                }
            }
        }
    }
    std::cout << "Part 2 solution: " << std::reduce(lamps.begin(), lamps.end()) << std::endl;
}
 

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}

