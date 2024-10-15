#include <chrono>
#include <iostream>
#include <string>

void increment(std::string &password)
{
    for (auto p = password.rbegin(); p != password.rend(); p++)
    {
        if (*p != 'z')
        {
            (*p)++;
            break;
        }
        else
        {
            *p = 'a';
        }
    }
    

}

std::string next_valid(const std::string &password)
{
    std::string result = password;
    bool has_consecutive = false;
    size_t doubles = 0;
    bool has_forbidden = false;
    do
    {
        increment(result);
        has_consecutive = false;
        doubles = 0;
        has_forbidden = false;
        for (auto p = result.begin(); p != result.end(); p++)
        {
            if ((p < result.end() - 2) && (*(p+1) == *p + 1) && (*(p+2) == *p + 2)) 
                has_consecutive = true;
            if ((p < result.end() - 1) && (*(p+1) == *p) && (p >= result.end() - 2 || *(p + 2) != *p)) 
                doubles++;
            if (*p == 'i' || *p == 'o' || *p == 'l')
                has_forbidden = true;
        }
        
    } while ((doubles < 2) || !has_consecutive || has_forbidden);
    return result;
}


void solve()
{

    std::string password("hepxcrrq");
    password = next_valid(password);
    std::cout << password << std::endl;
    std::cout << next_valid(password) << std::endl;


}



int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    //solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}