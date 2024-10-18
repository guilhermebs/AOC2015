#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>

int count_combinations(const std::vector<int>::iterator &iter_begin, const std::vector<int>::iterator &iter_end, int remaining, int n, std::vector<int> &n_used)
{
    if (remaining == 0) {
        n_used.push_back(n);
        return 1;
    }
    if (iter_begin == iter_end || remaining < 0 || std::reduce(iter_begin, iter_end) < remaining) return 0;
    return count_combinations(iter_begin+1, iter_end, remaining, n, n_used) +
           count_combinations(iter_begin+1, iter_end, remaining - *iter_begin, n + 1, n_used);
}

void solve()
{
    std::ifstream file("inputs/day17");
    std::string line;
    std::vector<int> containers;
    while (getline(file, line))
    {
        containers.push_back(std::stoi(line));
    }
    //containers = {20, 15, 10, 5, 5};
    std::sort(containers.begin(), containers.end(), std::greater<int>());

    std::vector<int> n_used;
    auto sol_pt1 = count_combinations(containers.begin(), containers.end(), 150, 0, n_used);
    std::cout << "Part 1 solution: " << sol_pt1 << std::endl;

    std::sort(n_used.begin(), n_used.end());
    int sol_pt2 = 0;
    for (auto i = n_used.begin(); *i == n_used.front(); i++)
        sol_pt2++;
    
    std::cout << "Part 2 solution: " << sol_pt2 << std::endl;
    
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}