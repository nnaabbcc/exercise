
#include <iostream>
#include <string>

int get_value(const std::string& key)
{
    if (key == "a")
        return 1;
    else if (key == "b")
        return 10;
    else
        return 100;
}

int main(int, char**)
{
    if (std::string key="a"; get_value(key) < 10)
    {
        std::cout << key << " smaller than 10" << std::endl;
    }
    // std::cout << key; // key is not available here
    return 0;
}
