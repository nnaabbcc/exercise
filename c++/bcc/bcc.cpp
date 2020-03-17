#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

static uint8_t bcc(uint8_t* data, uint8_t seed, size_t size)
{
    uint8_t sum = seed;
    for (size_t i = 0; i < size; i++)
    {
        sum ^= data[i];
    }
    return sum;
}

static void bcc_file(const char* file)
{
    if (!fs::exists(file))
    {
        std::cout << file << " is not exists" << std::endl;
        return;
    }

    const size_t size = 100;
    uint8_t data[size];
    uint8_t seed = 0;

    std::ifstream in(file, std::ios::binary | std::ios::in);
    while (true)
    {
        in.read(reinterpret_cast<char*>(data), size);
        auto read = in.gcount();
        if (read > 0)
        {
            seed = bcc(data, seed, read);
        }
        if (in.eof())
        {
            break;
        }
    }

    std::cout << file << ": 0x" << std::hex
        << std::setfill('0') << std::setw(2)<< +seed << std::endl;
}

static void print_help(const char* bin)
{
    std::cout << "Usage:" << std::endl;
    std::cout << bin << " <file> [file] [file] ..." << std::endl;
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    if (argc <= 0)
    {
        std::cout << "Unknown Error" << std::endl;
        return -1;
    }
    else if (argc == 1)
    {
        print_help(argv[0]);
        return -2;
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            bcc_file(argv[i]);
        }
    }
    return 0;
}
