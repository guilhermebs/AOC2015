#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>

const size_t SIZE = 100;

void solve_pt1()
{
    std::ifstream file("inputs/day18");
    std::string line;
    std::string lights;
    while (getline(file, line))
        lights.append(line);
    
    for (size_t t = 0; t < 100; t++)
    {
        auto new_lights = lights;
        for (size_t i = 0; i < SIZE * SIZE; i++)
        {
            int x = i % SIZE;
            int y = i / SIZE;
            int neighbours_on = 0;
            for (int xx = std::max(x-1, 0); xx < std::min(x + 2, (int) SIZE); xx++)
            {
                for (int yy = std::max(y-1, 0); yy < std::min(y + 2, (int) SIZE); yy++)
                {
                    size_t j = xx + SIZE * yy;
                    neighbours_on += (lights[j] == '#') && (i != j);
                }
            }
            if ((lights[i] == '#') && (neighbours_on != 2) && (neighbours_on != 3))    
                new_lights[i] = '.';
            else if ((lights[i] == '.') && (neighbours_on == 3))    
                new_lights[i] = '#';
        }
        lights = new_lights;
    }

    std::cout << "Part 1 solution: " << std::count(lights.begin(), lights.end(), '#')  << std::endl;
    
}

void solve_pt2()
{
    std::ifstream file("inputs/day18");
    std::string line;
    std::string lights;
    while (getline(file, line))
        lights.append(line);
    
    auto new_lights = lights;
    for (size_t t = 0; t < 100; t++)
    {
        for (size_t i = 0; i < SIZE * SIZE; i++)
        {
            int x = i % SIZE;
            int y = i / SIZE;
            int neighbours_on = 0;
            for (int yy = std::max(y-1, 0); yy < std::min(y + 2, (int) SIZE); yy++)
            {
                for (int xx = std::max(x-1, 0); xx < std::min(x + 2, (int) SIZE); xx++)
                {
                    size_t j = xx + SIZE * yy;
                    neighbours_on += (lights[j] == '#') && (i != j);
                }
            }
            if ((lights[i] == '#') && (neighbours_on != 2) && (neighbours_on != 3))    
                new_lights[i] = '.';
            else if ((lights[i] == '.') && (neighbours_on == 3))    
                new_lights[i] = '#';
        }
        lights = new_lights;
        lights[0] = '#';
        lights[SIZE - 1] = '#';
        lights[SIZE * (SIZE - 1)] = '#';
        lights[(SIZE * SIZE) - 1] = '#';
    }

    std::cout << "Part 2 solution: " << std::count(lights.begin(), lights.end(), '#')  << std::endl;
    
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    //solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}
