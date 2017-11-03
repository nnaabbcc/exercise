
#include <tuple>
#include <iostream>

int main(int, char**)
{
    auto t = std::make_tuple(1, "test", false);
    auto [a, b, c] = t;

    std::cout << a << " " << b  << " " << (c ? "true" : "false") << std::endl;

    return 0;
}
