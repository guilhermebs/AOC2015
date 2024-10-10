#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <regex>

void solve_pt1()
{
    std::ifstream file("inputs/day05");
    std::string line;
    const std::unordered_set<std::string> forbiden{"ab", "cd", "pq", "xy"};
    const std::unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};
    int sol_pt1 = 0;
    while (getline(file, line))
    {
        char prev = '.';
        int vcount = 0;
        int rcount = 0;
        bool has_forbidden = false;
        for (auto &&c : line)
        {
            vcount += vowels.contains(c);
            rcount += prev == c;
            if (forbiden.contains(std::string{prev, c}))
            {
                has_forbidden = true;
                break;
            }
            prev = c;
        }
        sol_pt1 += (vcount >= 3) && (rcount >= 1) && !has_forbidden;
    }
    std::cout << "Part 1 solution: " << sol_pt1 << std::endl;
}


void solve_pt2()
{
    std::ifstream file("inputs/day05");
    std::string line;
    static std::regex rule1("(\\w)(\\w)\\w*\\1\\2");
    static std::regex rule2("(\\w)\\w\\1");
    int sol_pt2 = 0;
    while (getline(file, line))
    {
        sol_pt2 += std::regex_search(line, rule1) && std::regex_search(line, rule2);
    }
    std::cout << "Part 2 solution: " << sol_pt2 << std::endl;

}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}
