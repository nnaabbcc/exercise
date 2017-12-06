
#include <map>
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

std::vector<int> bubble_sort(std::vector<int> arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = i + 1; j < arr.size(); j++)
        {
            if (arr[i] > arr[j])
            {
                auto tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    return arr;
}

int main(int, char**)
{
    std::vector<int> arr {3, 8, 21, 6, 4, 79, 231, 1};
    std::cout << "array to be sorted : ";
    print_array(arr);

    const std::map<std::string, sort_method_ptr_t> sort_methods {
        {"insert_sort", insert_sort},
        {"bubble_sort", bubble_sort}
    };
    for (auto& item: sort_methods)
    {
        std::cout << item.first.c_str() << " : ";
        auto sorted_array = item.second(arr);
        print_array(sorted_array);
    }

    return 0;
}

