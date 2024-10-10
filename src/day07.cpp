#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <memory>
#include <list>

std::optional<int> get_number(const std::string &str, const std::unordered_map<std::string, int> &wires)
{
    if (std::all_of(str.begin(), str.end(), isdigit)) return std::stoi(str);
    else if (wires.contains(str)) return wires.at(str);
    return {};
};

struct Operation
{
    virtual bool execute(std::unordered_map<std::string, int> &wires) = 0;
    virtual ~Operation() {};
};

struct AndOperation : Operation
{
    std::string input1;
    std::string input2;
    std::string output;
    AndOperation (std::string input1, std::string input2, std::string output): input1{input1}, input2{input2}, output{output} {};
    bool execute(std::unordered_map<std::string, int> &wires) override
    {
        if (wires.contains(output)) return false;
        auto i1 = get_number(input1, wires);
        auto i2 = get_number(input2, wires);
        if (i1 && i2)
        {
            wires[output] = (*i1) & (*i2);
            return true;
        }
        return false;
    };
};

struct OrOperation : Operation
{
    std::string input1;
    std::string input2;
    std::string output;
    OrOperation (std::string input1, std::string input2, std::string output): input1{input1}, input2{input2}, output{output} {};
    bool execute(std::unordered_map<std::string, int> &wires) override
    {
        if (wires.contains(output)) return false;
        auto i1 = get_number(input1, wires);
        auto i2 = get_number(input2, wires);
        if (i1 && i2)
        {
            wires[output] = (*i1) | (*i2);
            return true;
        }
        return false;
    };
};

struct IdOperation : Operation
{
    std::string input1;
    std::string output;
    IdOperation (std::string input1, std::string output): input1{input1}, output{output} {};
    bool execute(std::unordered_map<std::string, int> &wires) override
    {
        if (wires.contains(output)) return false;
        auto i1 = get_number(input1, wires);
        if (i1)
        {
            wires[output] = (*i1);
            return true;
        }
        return false;
    };
    virtual ~IdOperation() = default;
};

struct NotOperation : Operation
{
    std::string input1;
    std::string output;
    NotOperation (std::string input1, std::string output): input1{input1}, output{output} {};
    bool execute(std::unordered_map<std::string, int> &wires) override
    {
        if (wires.contains(output)) return false;
        auto i1 = get_number(input1, wires);
        if (i1)
        {
            wires[output] = ~(*i1);
            return true;
        }
        return false;
    };
};

struct LShiftOperation : Operation
{
    std::string input1;
    std::string input2;
    std::string output;
    LShiftOperation (std::string input1, std::string input2, std::string output): input1{input1}, input2{input2}, output{output} {};
    bool execute(std::unordered_map<std::string, int> &wires) override
    {
        if (wires.contains(output)) return false;
        auto i1 = get_number(input1, wires);
        auto i2 = get_number(input2, wires);
        if (i1 && i2)
        {
            wires[output] = (*i1) << (*i2);
            return true;
        }
        return false;
    };
};

struct RShiftOperation : Operation
{
    std::string input1;
    std::string input2;
    std::string output;
    RShiftOperation (std::string input1, std::string input2, std::string output): input1{input1}, input2{input2}, output{output} {};
    bool execute(std::unordered_map<std::string, int> &wires) override
    {
        if (wires.contains(output)) return false;
        auto i1 = get_number(input1, wires);
        auto i2 = get_number(input2, wires);
        if (i1 && i2)
        {
            wires[output] = (*i1) >> (*i2);
            return true;
        }
        return false;
    };
};

void solve_pt1()
{
    std::ifstream file("inputs/day07");
    std::string line;
    static std::regex re_id("(\\w+) -> (\\w+)");
    static std::regex re_lshift("(\\w+) LSHIFT (\\w+) -> (\\w+)");
    static std::regex re_rshift("(\\w+) RSHIFT (\\w+) -> (\\w+)");
    static std::regex re_and("(\\w+) AND (\\w+) -> (\\w+)");
    static std::regex re_or("(\\w+) OR (\\w+) -> (\\w+)");
    static std::regex re_not("NOT (\\w+) -> (\\w+)");
    std::smatch sm;
    std::vector<std::unique_ptr<Operation>> operations;
    std::unordered_map<std::string, int> wires;
    while (getline(file, line))
    {
        if (std::regex_match(line, sm, re_id))
            operations.push_back(std::make_unique<IdOperation>(sm[1], sm[2]));
        else if (std::regex_match(line, sm, re_lshift))
            operations.push_back(std::make_unique<LShiftOperation>(sm[1], sm[2], sm[3]));
        else if (std::regex_match(line, sm, re_rshift))
            operations.push_back(std::make_unique<RShiftOperation>(sm[1], sm[2], sm[3]));
        else if (std::regex_match(line, sm, re_and))
            operations.push_back(std::make_unique<AndOperation>(sm[1], sm[2], sm[3]));
        else if (std::regex_match(line, sm, re_or))
            operations.push_back(std::make_unique<OrOperation>(sm[1], sm[2], sm[3]));
        else if (std::regex_match(line, sm, re_not))
            operations.push_back(std::make_unique<NotOperation>(sm[1], sm[2]));
        else
            std::cout << line << std::endl;
    }

    while (! wires.contains("a"))
    {
        for (auto &&op : operations)
            op->execute(wires);
    }
    std::cout << "Part 1 solution: " << wires["a"] << std::endl;

    std::unordered_map<std::string, int> new_wires;
    new_wires["b"] = wires["a"];
    while (!new_wires.contains("a"))
    {
        for (auto &&op : operations)
            op->execute(new_wires);
    }
    std::cout << "Part 2 solution: " << new_wires["a"] << std::endl;
}
 
int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    //solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}
