#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

struct Raindeer
{
    int speed;
    int fly_time;
    int rest_time;

    int distance_traveled(int time)
    {
        int dist_per_cycle = speed * fly_time;
        int time_per_cycle = fly_time + rest_time;
        int cycles = time / time_per_cycle;
        int rem = time % time_per_cycle;
        return cycles * dist_per_cycle + std::min(rem * speed, dist_per_cycle);
    }
};


void solve()
{
    std::vector<Raindeer> flock{
        Raindeer{8, 8, 53},
        Raindeer{13, 4, 49},
        Raindeer{20, 7, 132},
        Raindeer{12, 4, 43},
        Raindeer{9, 5, 38},
        Raindeer{10, 4, 37},
        Raindeer{3, 37, 76},
        Raindeer{9, 12, 97},
        Raindeer{37, 1, 36},
    };
    int sol_pt1 = 0;
    const int time = 2503;
    for (auto &&r : flock)
        sol_pt1 = std::max(sol_pt1, r.distance_traveled(time));
    std::cout << "Part 1 solution: " << sol_pt1 << std::endl;

    std::vector<int> scores(flock.size(), 0);
    for (int t=1; t<= time; t++)
    {
        int iahead = -1;
        int dahead = 0;
        for (size_t i = 0; i < flock.size(); i++)
        {
            int d = flock[i].distance_traveled(t);
            if (d > dahead)
            {
                dahead = d;
                iahead = i;
            }
        }
        scores[iahead]++;
    }
    std::cout << "Part 2 solution: " << *(std::max_element(scores.begin(), scores.end())) << std::endl;

}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}