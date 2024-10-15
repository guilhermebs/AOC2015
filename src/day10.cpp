#include <chrono>
#include <iostream>
#include <vector>

std::vector<int> look_and_say(const std::vector<int> &v)
{
    std::vector<int> result;
    int prev = -1;
    int count = 0;
    for (auto p = v.rbegin(); p != v.rend(); p++)
    {
        if (*p == prev)
            count++;
        else
        {
            if (prev != -1)
            {
                result.push_back(prev);
                result.push_back(count);
            }
            prev = *p;
            count = 1;
        }
    }
    result.push_back(prev);
    result.push_back(count);
    std::reverse(result.begin(), result.end());
    return result;
}

void solve_pt1()
{
    //std::vector<int> v{2,1};
    std::vector<int> v{1,1,1,3,2,2,2,1,1,3};
    for (size_t i = 0; i < 50; i++)
    {
        v = look_and_say(v);
        std::cout << v.size() << std::endl;
    }
    std::cout << "Part 1 solution: " <<  v.size() << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    //solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}