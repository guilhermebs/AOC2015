#include <chrono>
#include <string>
#include <iostream>
#include <numeric>
#include <cmath>

int count_presents(int house_nr)
//https://math.stackexchange.com/questions/22721/is-there-a-formula-to-calculate-the-sum-of-all-proper-divisors-of-a-number
{
    int result = 1;
    int exp = 1;
    int m = 1;
    while (house_nr%2 == 0)
    {
        m += std::pow(2, exp);
        house_nr /= 2;
        exp++;
    }
    result *= m;
    
    for (int i = 3; i <= std::sqrt(house_nr); i+=2)
    {
        m = 1;
        exp = 1;
        while (house_nr%i == 0)
        {
            m += std::pow(i, exp);
            house_nr /= i;
            exp++;
        }
        result *= m;
    }
    if (house_nr > 1)
        result *= (1 + house_nr);
    return result * 10;
}


int count_presents_pt2(int house_nr)
{
    int result = 0;
    for (size_t i = 1; i <=50; i++)
    {
        if (house_nr%i == 0)
            result += 11*(house_nr/i);
    }

    return result; 
}


void solve()
{
    int n = 1;
    int target = 34000000;
    while (count_presents(n) < target)
    {
        n++;
    }
    std::cout << n << std::endl;

    while (count_presents_pt2(n) < target)
    {
        n++;
    }
    std::cout << n << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}