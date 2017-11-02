
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
    
    switch (std::string key="a"; get_value(key))
    {
    case 1:
        std::cout << "get_value return 1";
        break;
    case 10:
        std::cout << "get_value return 10";
        break;
    case 100:
        std::cout << "get_value return 100";
        break;
    default:
        std::cout << "get_value return an unknown value";
    }
    std::cout << std::endl;

    return 0;
}
