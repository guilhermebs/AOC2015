#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>

void solve()
{
    std::ifstream file("inputs/day02");
    std::string line;
    static std::regex re("(\\d+)x(\\d+)x(\\d+)");
    std::smatch sm;
    int sol_pt1 = 0;
    int sol_pt2 = 0;
    while (getline(file, line))
    {
        if (std::regex_match(line, sm, re))
        {
            int l = std::stoi(sm[1]); 
            int w = std::stoi(sm[2]); 
            int h = std::stoi(sm[3]); 
            sol_pt1 += 2*l*w + 2*w*h + 2*h*l + std::min({l*w, w*h, h*l});
            sol_pt2 += l*w*h + std::min({2*(l+w), 2*(w + h), 2*(h+l)});
        } else
        {
            std::cout << line << std::endl;
        }
    }
    std::cout << "Part 1 solution: " << sol_pt1 << std::endl;
    std::cout << "Part 2 solution: " << sol_pt2 << std::endl;
    
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}