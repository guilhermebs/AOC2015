#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

const int N_ATTRS = 5;
const int N_SPOONS = 100;

void solve()
{
    std::vector<int> ingredients{
        4, -2, 0, 0, 5,
        0, 5, -1, 0, 8,
        -1, 0, 5, 0, 6,
        0, 0, -2, 2, 1
    };
    int sol_pt1 = 0;
    int sol_pt2 = 0;
    for (int i = 0; i <= N_SPOONS; i++)
    {
        for (int j = 0; j <= N_SPOONS - i; j++)
        {
            for (int k = 0; k <= N_SPOONS - (i + j); k++)
            {
                int l = N_SPOONS - (i + j + k);
                int score = (
                    std::max((i * ingredients[0] + j * ingredients[N_ATTRS] + k * ingredients[2 * N_ATTRS] + l * ingredients[3 * N_ATTRS]), 0) * 
                    std::max((i * ingredients[1] + j * ingredients[N_ATTRS + 1] + k * ingredients[2 * N_ATTRS + 1] + l * ingredients[3 * N_ATTRS + 1]), 0) * 
                    std::max((i * ingredients[2] + j * ingredients[N_ATTRS + 2] + k * ingredients[2 * N_ATTRS + 2] + l * ingredients[3 * N_ATTRS + 2]), 0) * 
                    std::max((i * ingredients[3] + j * ingredients[N_ATTRS + 3] + k * ingredients[2 * N_ATTRS + 3] + l * ingredients[3 * N_ATTRS + 3]), 0)
                );
                sol_pt1 = std::max(sol_pt1, score);
                int cal = i * ingredients[4] + j * ingredients[N_ATTRS + 4] + k * ingredients[2 * N_ATTRS + 4] + l * ingredients[3 * N_ATTRS + 4];
                sol_pt2 = std::max(sol_pt2, score * (cal == 500));
            }
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
