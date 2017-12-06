
#include <vector>
#include <iostream>

void print_array(const std::vector<int>& arr)
{
    for (auto val : arr)
    {
        std::cout << val << ' ';
    }
    std::cout << std::endl;
}

using sort_method_ptr_t = std::vector<int> (*)(std::vector<int>);

std::vector<int> insert_sort(std::vector<int> arr)
{
    for (int i = 1; i < arr.size(); i++)
    {
        auto tmp = arr[i];
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j] > tmp)
            {
                arr[j+1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    return arr;
}

int main(int, char**)
{
    std::vector<int> arr {3, 8, 21, 6, 4, 79, 231, 1};
    print_array(arr);

    const std::vector<sort_method_ptr_t> sort_methods {insert_sort};
    for (auto sort_method : sort_methods)
    {
        auto sorted_array = sort_method(arr);
        print_array(sorted_array);
    }

    return 0;
}
