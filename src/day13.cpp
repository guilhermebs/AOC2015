#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>
#include <vector>
#include <algorithm>

void solve_pt1()
{
    std::ifstream file("inputs/day13");
    std::string line;
    std::regex re("(\\w+) would (\\w+) (\\d+) happiness units by sitting next to (\\w+)");
    std::smatch sm;
    std::unordered_map<std::string, int> dhappyness;
    std::vector<std::string> people;
    while (getline(file, line))
    {
        if (std::regex_search(line, sm, re))
        {
            if (std::find(people.begin(), people.end(), sm[1]) == people.end()) people.push_back(sm[1]);
            dhappyness[sm[1].str() + sm[4].str()] = (sm[2] == "gain")? std::stoi(sm[3]) : -std::stoi(sm[3]);
        } else
        {
            std::cout << line << std::endl;
        }
    }
    std::sort(people.begin(), people.end());
    int sol_pt1 = INT_MIN;
    do
    {
        int h = 0;
        for (size_t i = 0; i < people.size() - 1; i++)
            h += dhappyness[people[i] + people[i + 1]];
        for (size_t i = people.size() - 1; i > 0; i--)
            h += dhappyness[people[i] + people[i - 1]];
        h += dhappyness[people[0] + people.back()];
        h += dhappyness[people.back() + people[0]];
        sol_pt1 = std::max(h, sol_pt1);
    } while (std::next_permutation(people.begin(), people.end()));
    std::cout << "Part 1 solution: " << sol_pt1 << std::endl;
    
    for (const auto &p: people)
    {
        dhappyness["me" + p] = 0;
        dhappyness[p + "me"] = 0;
    }
    people.push_back("me");
    std::sort(people.begin(), people.end());
    int sol_pt2 = INT_MIN;
    do
    {
        int h = 0;
        for (size_t i = 0; i < people.size() - 1; i++)
            h += dhappyness[people[i] + people[i + 1]];
        for (size_t i = people.size() - 1; i > 0; i--)
            h += dhappyness[people[i] + people[i - 1]];
        h += dhappyness[people[0] + people.back()];
        h += dhappyness[people.back() + people[0]];
        sol_pt2 = std::max(h, sol_pt2);
    } while (std::next_permutation(people.begin(), people.end()));
    std::cout << "Part 2 solution: " << sol_pt2 << std::endl;
 
}
int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}