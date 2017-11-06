#include <array>
#include <iostream>

class Thing
{
    public: 
        Thing() : x(0) {}
        int x;
};
int main()
{
    std::array<Thing, 100> arr;
    for (auto& it : arr)
        std::cout << it.x << " ";
}
