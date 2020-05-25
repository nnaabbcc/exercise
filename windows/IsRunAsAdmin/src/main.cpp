
#include <ShlObj.h>
#include <iostream>

int main(int argc, char**argv)
{
    auto admin = IsUserAnAdmin();
    if (admin)
    {
        std::cout << "IsUserAnAdmin return true" << std::endl;
        std::cout << "Program running as administrator" << std::endl;
    }
    else
    {
        std::cout << "IsUserAnAdmin return false" << std::endl;
        std::cout << "Program not running as adminstrator" << std::endl;
    }

    getchar();

    return 0;
}
