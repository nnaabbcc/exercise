
#include <iostream>
#include <cuda_device_runtime_api.h>

int main(int argc, char**argv)
{
    int count = 0;
    auto ec = cudaGetDeviceCount(&count);
    if (ec != cudaSuccess)
    {
        std::cout << "Failed get cuda device count, error code is "
            << ec << std::endl;
    }
    else
    {
        std::cout << "Got " << count << " cuda devices" << std::endl;
    }

    return 0;
}
