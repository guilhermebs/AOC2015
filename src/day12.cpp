#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>



void solve_pt1()
{
    std::ifstream file("inputs/day12");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string contents = buffer.str();
    std::regex re("-?\\d+");
    int sol_pt1 = 0;
    for (std::smatch sm; std::regex_search(contents, sm, re);)
    {
        sol_pt1 += std::stoi(sm[0]);
        contents = sm.suffix();
    }
    std::cout << sol_pt1 << std::endl;
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}