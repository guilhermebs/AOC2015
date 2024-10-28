#include <chrono>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>

std::pair<u_int64_t, uint64_t> find_group1(const std::vector<int>::iterator &begin, const std::vector<int>::iterator &end, int remain, uint64_t count, uint64_t entanglement)
{
    if (remain == 0)
    {
        return {count, entanglement};
    }
    else if (remain < 0 || begin == end)
    {
        return {INT_MAX, INT_MAX};
    } else
    {
        return std::min(
            find_group1(begin+1, end, remain, count, entanglement),
            find_group1(begin+1, end, remain - *begin, count + 1, entanglement * (*begin))
        );
    }
    
}


void solve()
{
    std::ifstream file("inputs/day24");
    std::string line;
    std::vector<int> weights;
    while (getline(file, line))
    {
        weights.push_back(std::stoi(line));
    }
    int tot_weight = std::reduce(weights.begin(), weights.end());
    int group_weight = tot_weight/3;
    // create all possubilities to fit the weights
    auto g1 = find_group1(weights.begin(), weights.end(), group_weight, 0, 1);
    std::cout << "Part 1 solution: " << g1.second << std::endl;
    auto g2 = find_group1(weights.begin(), weights.end(), tot_weight/4, 0, 1);
    std::cout << "Part 2 solution: " << g2.second << std::endl;
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}