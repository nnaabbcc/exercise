#include <vector>
#include <algorithm>
#include <experimental/random>
#include <iostream>
#include <iterator>

int main(int, char*[])
{
    std::vector<int> v(10);
    std::generate(v.begin(), v.end(), [](){return std::experimental::randint(0, 1000);});

    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, "\n"));

    return 0;
}
