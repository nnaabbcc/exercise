
#include <memory>
#include <iostream>

class A
{
};

void test(std::shared_ptr<A> a)
{
    std::cout << "reference count = " << a.use_count() << std::endl;
}

int main(int,char**)
{
    auto a = std::make_shared<A>();
    std::cout << "reference count = " << a.use_count() << std::endl;
    auto aa = a.get();
    std::cout << "reference count = " << a.use_count() << std::endl;
    test(a);
    return 0;
}
