#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

void solve()
{
    std::ifstream file("inputs/day01");
    std::string contents;
    getline(file, contents);
    int floor = std::count(contents.begin(), contents.end(), '(') - std::count(contents.begin(), contents.end(), ')');
    std::cout << "Part 1 solution: " << floor << std::endl;
    int cur_floor = 0;
    for (size_t i = 0; i < contents.size(); i++)
    {
        if (contents[i] == '(') cur_floor++;
        else if (contents[i] == ')') cur_floor--;
        if (cur_floor == -1)
        {
            std::cout << "Part 2 solution:" <<i + 1 << std::endl;
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