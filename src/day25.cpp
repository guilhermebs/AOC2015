#include <chrono>
#include <string>
#include <iostream>

void solve()
{
    uint64_t v = 20151125;
    uint64_t mult = 252533; 
    uint64_t mod = 33554393;
    size_t ti = 2981;
    size_t tj = 3075;

    for (size_t s = 3; s <= ti + tj; s++)
    {
        for (size_t i = s - 1; i > 0; i--)
        {
            v = (v * mult) % mod;
            //std::cout << i << ", " << s - i << ": " << v << std::endl;
            if ((i == ti) && (s - i == tj))
                std::cout << v << std::endl;
        }
    }
    
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}