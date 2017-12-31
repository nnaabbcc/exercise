#include <vector>
#include <algorithm>
#include <experimental/random>
#include <iostream>
#include <iterator>
#include <functional>

int main(int, char*[])
{
    const size_t size = 10;
    const int range_min = 0;
    const int range_max = 1000;

    std::vector<int> v(size);
    // lamda function
    std::generate(v.begin(), v.end(), [](){return std::experimental::randint(range_min, range_max);});
    // bind 
    std::generate(v.begin(), v.end(), std::bind(std::experimental::randint<int>, range_min, range_max));

    std::srand(time(0));
    std::generate(v.begin(), v.end(), [](){
        return static_cast<int>(range_min + std::rand() * 1.0 / RAND_MAX * (range_max - range_min));
        });

    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, "\n"));


    return 0;
}
