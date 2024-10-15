#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <regex>
#include <array>
#include <unordered_map>
#include <bit>


const size_t N_LOC = 8;

bool next_with_n_ones(size_t &m, const size_t n)
{
    const size_t END = 1 << N_LOC;
    do
    {
        m++;
    } while (((size_t) std::popcount(m) != n) && (m < END));
    return (m != END);
}

void solve_pt1()
{
    std::ifstream file("inputs/day09");
    std::string line;
    std::regex re("(\\w+) to (\\w+) = (\\d+)");
    std::smatch sm;
    std::vector<int> distances(N_LOC * N_LOC);
    std::vector<std::string> seen;
    while (getline(file, line))
    {
        if (std::regex_match(line, sm, re))
        {
            std::array<int, 2> loc;
            auto dist = std::stoi(sm[3]);
            for (size_t i = 0; i < 2; i++)
            {
                if (auto p = std::find(seen.begin(), seen.end(), sm[i+1]); p != seen.end())
                {
                    loc[i] = p - seen.begin();
                } else
                {
                    loc[i] = seen.size();
                    seen.push_back(sm[i+1]);
                }
            }
            distances[loc[0] + N_LOC * loc[1]] = dist;
            distances[loc[1] + N_LOC * loc[0]] = dist;
        } else
        {
            std::cout << line << std::endl;
        }
    }
    std::unordered_map<size_t, size_t> partials;
    for (size_t i = 0; i < N_LOC; i++)
    {
        for (size_t j = 0; j < N_LOC; j++)
        {
            if (i != j)
            {
                size_t visited = (1 << i) + (1 << j);
                partials[visited + (j << N_LOC)] = distances[i + N_LOC * j];
            }
        }
    }
    for (size_t s = 3; s <= N_LOC; s++)
    {
        size_t mask = 0;
        while (next_with_n_ones(mask, s))
        {
            for (size_t k = 0; k < N_LOC; k++)
            {
                if( (mask>>k) & 1)
                {
                    auto prev_visits = mask - (1 << k);
                    size_t min_dist = SIZE_T_MAX;
                    for (size_t m = 0; m < N_LOC; m++)
                    {
                        if ((m != k) && ((prev_visits) >> m & 1))
                            min_dist = std::min(partials.at(prev_visits + (m << N_LOC)) + distances[k + m * N_LOC], min_dist);
                    }
                    partials[mask + (k << N_LOC)] = min_dist;
                }
            }
        }
    }
    size_t sol_pt1 = SIZE_T_MAX;
    size_t final_mask = (1 << N_LOC) - 1;
    for (size_t i = 0; i < N_LOC; i++)
    {
        sol_pt1 = std::min(sol_pt1, partials.at(final_mask + (i << N_LOC)));
    }
    std::cout << "Part 1 solution: " << sol_pt1 << std::endl; 
}

void solve_pt2()
{
    std::ifstream file("inputs/day09");
    std::string line;
    std::regex re("(\\w+) to (\\w+) = (\\d+)");
    std::smatch sm;
    std::vector<int> distances(N_LOC * N_LOC);
    std::vector<std::string> seen;
    while (getline(file, line))
    {
        if (std::regex_match(line, sm, re))
        {
            std::array<int, 2> loc;
            auto dist = std::stoi(sm[3]);
            for (size_t i = 0; i < 2; i++)
            {
                if (auto p = std::find(seen.begin(), seen.end(), sm[i+1]); p != seen.end())
                {
                    loc[i] = p - seen.begin();
                } else
                {
                    loc[i] = seen.size();
                    seen.push_back(sm[i+1]);
                }
            }
            distances[loc[0] + N_LOC * loc[1]] = dist;
            distances[loc[1] + N_LOC * loc[0]] = dist;
        } else
        {
            std::cout << line << std::endl;
        }
    }
    std::unordered_map<size_t, size_t> partials;
    for (size_t i = 0; i < N_LOC; i++)
    {
        for (size_t j = 0; j < N_LOC; j++)
        {
            if (i != j)
            {
                size_t visited = (1 << i) + (1 << j);
                partials[visited + (j << N_LOC)] = distances[i + N_LOC * j];
            }
        }
    }
    for (size_t s = 3; s <= N_LOC; s++)
    {
        size_t mask = 0;
        while (next_with_n_ones(mask, s))
        {
            for (size_t k = 0; k < N_LOC; k++)
            {
                if( (mask>>k) & 1)
                {
                    auto prev_visits = mask - (1 << k);
                    size_t max_dist = 0;
                    for (size_t m = 0; m < N_LOC; m++)
                    {
                        if ((m != k) && ((prev_visits) >> m & 1))
                            max_dist = std::max(partials.at(prev_visits + (m << N_LOC)) + distances[k + m * N_LOC], max_dist);
                    }
                    partials[mask + (k << N_LOC)] = max_dist;
                }
            }
        }
    }
    size_t sol_pt2 = 0;
    size_t final_mask = (1 << N_LOC) - 1;
    for (size_t i = 0; i < N_LOC; i++)
    {
        sol_pt2 = std::max(sol_pt2, partials.at(final_mask + (i << N_LOC)));
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

