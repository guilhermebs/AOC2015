#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
void solve_pt1()
{
    std::ifstream file("inputs/day08");
    std::string line;
    size_t count_code = 0;
    size_t count_chars = 0;
    while (getline(file, line))
    {
        count_code += line.size();
        for (auto p = line.begin(); p < line.end(); p++)
        {

            if (*p == '\\' && (*(p+1) == '\\' || *(p+1) == '"'))
            {
                count_chars++;
                p++;
            }
            else if (*p == '\\' && *(p+1) == 'x')
            {
                count_chars++;
                p += 3;
            }
            else if (*p != '"')
            {
                count_chars++;
            }
        }
    }
    std::cout << "Part 1 solution: " << count_code - count_chars << std::endl;
}

void solve_pt2()
{
    std::ifstream file("inputs/day08");
    std::string line;
    size_t count_code = 0;
    size_t count_encoded = 0;
    while (getline(file, line))
    {
        count_code += line.size();
        count_encoded += line.size() + 2;
        for (auto p = line.begin(); p < line.end(); p++)
        {

            if (*p == '\\' && (*(p+1) == '\\' || *(p+1) == '"'))
            {
                count_encoded += 2;
                p++;
            }
            else if (*p == '\\' && *(p+1) == 'x')
            {
                count_encoded += 1;
                p += 3;
            }
            else if (*p == '"')
            {
                count_encoded++;
            }
        }
    }
    std::cout << "Part 2 solution: " << count_encoded - count_code << std::endl;
}
 
int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}

