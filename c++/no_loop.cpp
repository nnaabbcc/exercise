#include <vector>
#include <algorithm>
#include <experimental/random>
#include <iostream>
#include <iterator>

int main(int, char*[])
{
    const size_t size = 10;
    const int range_min = 0;
    const int range_max = 1000;

    std::vector<int> v(size);
    std::generate(v.begin(), v.end(), [](){return std::experimental::randint(range_min, range_max);});

    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, "\n"));

    return 0;
}
