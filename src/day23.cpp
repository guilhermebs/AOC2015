#include <chrono>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "helper.hpp"

void solve()
{
    std::ifstream file("inputs/day23");
    std::string line;
    std::vector<std::vector<std::string>> instructions; 
    while (getline(file, line))
    {
        instructions.push_back(tokenize(line, " "));
    }
    size_t i = 0;
    std::unordered_map<std::string, long long> registers{{"a", 1}, {"b", 0}};
    while (i < instructions.size())
    {
        std::cout << i + 1 << ": " << registers["a"] << ", " << registers["b"] << std::endl;
        auto instr = instructions[i][0];
        if (instr == "hlf")
        {
            registers[instructions[i][1]] /= 2;
            i++;
        } else if (instr == "tpl")
        {
            registers[instructions[i][1]] *= 3;
            i++;
        } else if (instr == "inc")
        {
            registers[instructions[i][1]]++;
            i++;
        } else if (instr == "jmp")
        {
            i += std::stoi(instructions[i][1]);
        } else if (instr == "jie")
        {
            i += (registers[instructions[i][1]]%2 == 0)? std::stoi(instructions[i][2]) : 1;
        } else if (instr == "jio")
        {
            i += (registers[instructions[i][1]] == 1)? std::stoi(instructions[i][2]) : 1;
        }
    }
    std::cout << registers["b"] << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}