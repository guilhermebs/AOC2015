#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <utility>
#include <regex>
#include <deque>

std::unordered_set<std::string> descendents(const std::string &molecule, const std::vector<std::pair<std::string, std::string> > &reactions)
{
    std::unordered_set<std::string> seen;
    for (const auto &[k, v] : reactions)
    {
        for (size_t i = 0; i < molecule.size(); i++)
        {
            if (molecule.substr(i, k.size()) == k)
            {
                auto s = molecule.substr(0, i) + v + molecule.substr(i + k.size());
                seen.insert(s);
            }
        }
    } 
    return seen;
}

std::unordered_set<std::string> parents(const std::string &molecule, const std::vector<std::pair<std::string, std::string> > &reactions)
{
    std::unordered_set<std::string> seen;
    for (const auto &[v, k] : reactions)
    {
        if (v == "e" && molecule != k) continue;
        for (size_t i = 0; i < molecule.size(); i++)
        {
            if (molecule.substr(i, k.size()) == k)
            {
                auto s = molecule.substr(0, i) + v + molecule.substr(i + k.size());
                seen.insert(s);
            }
        }
    } 
    return seen;
}

std::pair<std::string, int> reduce(const std::string &molecule, const std::vector<std::pair<std::string, std::string> > &reactions)
{
    std::unordered_set<std::string> seen;
    std::deque<std::pair<int, std::string>> queue{{0, molecule}};
    //for (auto &[k, v] : reactions)
    //{
    //    if (k == "e"){
    //        queue.push_back({1, v});
    //        seen.insert(v);
    //    }
    //}
    int last_n;
    std::string last_m;
    while (queue.size())
    {
        auto [n, m] = queue.front();
        queue.pop_front();
        last_m = m;
        last_n = n;
        for (auto md: parents(m, reactions))
        {
            if (!seen.contains(md))
            {
                queue.push_back({n + 1, md});
                seen.insert(md);
            }
        }
    }
    return {last_m, last_n};
}


void solve()
{
    std::ifstream file("inputs/day19");
    std::string line;
    std::regex re("(\\w+) => (\\w+)");
    std::vector<std::pair<std::string, std::string> > reactions;
    std::smatch sm;
    std::string molecule;
    while (getline(file, line))
    {
        if (std::regex_search(line, sm, re))
        {
            reactions.push_back({sm[1], sm[2]});
        } else
        {
            molecule = line;
        }
    }

    std::cout << descendents(molecule, reactions).size() << std::endl;
    int sol_pt2 = 0;
    std::vector<std::string> submolecules;
    size_t pos = 0;
    size_t next_Ar;
    do {
        next_Ar = molecule.find("Ar", pos);
        submolecules.push_back(molecule.substr(pos, next_Ar - pos + 2));
        pos = next_Ar + 2;
    } while (next_Ar != std::string::npos);

    std::string reduced = "";
    for (auto &m : submolecules)
    {
        auto [r, n] = reduce(reduced + m, reactions);
        reduced = r;
        sol_pt2 += n;
    }
    std::cout << sol_pt2 << std::endl;
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}