#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <regex>
#include <algorithm>

void solve()
{
    std::ifstream file("inputs/day16");
    std::string line;
    std::regex re("Sue \\d+: (\\w+): (\\d+), (\\w+): (\\d+), (\\w+): (\\d+)");
    std::vector<std::unordered_map<std::string, int>> sue_info;
    std::smatch sm;
    while (getline(file, line))
    {
        if (std::regex_search(line, sm, re))
        {
            sue_info.push_back(
                {{sm[1], std::stoi(sm[2])}, {sm[3], std::stoi(sm[4])}, {sm[5], std::stoi(sm[6])}}
            );

        } else
        {
            std::cout << line << std::endl;
        }
    }
    std::unordered_map<std::string, int> target_sue{{"children", 3}, {"cats", 7}, {"samoyeds", 2}, {"pomeranians", 3}, {"akitas", 0}, {"vizslas", 0}, {"goldfish", 5}, {"trees", 3}, {"cars", 2}, {"perfumes", 1}};
    for (size_t i = 0; i < sue_info.size(); i++)
    {
        if (std::all_of(sue_info[i].begin(), sue_info[i].end(), [&target_sue](auto &s){ return target_sue[s.first] == s.second; }))
        {
            std::cout << "Part 1 solution:" << i+1 << std::endl;
            break;
        }
    }

    for (size_t i = 0; i < sue_info.size(); i++)
    {
        bool is_sue = true;
        for (const auto &[k, v]: sue_info[i])
        {
            if (k == "cats" || k == "trees")
                is_sue &= (target_sue[k] < v);
            else if (k == "pomeranians" || k == "goldfish")
                is_sue &= (target_sue[k] > v);
            else
                is_sue &= (target_sue[k] == v);
        }
        
        if (is_sue)
        {
            std::cout << "Part 2 solution:" << i+1 << std::endl;
            break;
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





