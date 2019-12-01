#include <iostream>
#include <vector>
#include "insertion_sort.h"
#include "shell_sort.h"

int main() {
    int a[15] = {2, 3, 1, 4, 5, 6, 9, 8, 10, 11, 12, 13, 14, 15, 7};
    insertion_sort<int, size_t>(a, 15);
    for (auto i = 0; i < 14; ++i)
        std::cout << a[i] << ", ";
    std::cout << a[14] << std::endl;

    std::vector<int> vec = {2, 3, 1, 4, 5, 6, 9, 8, 10, 11, 12, 13, 14, 15, 7};
    using int_vec_t = std::vector<int>;
    insertion_sort<int_vec_t>(vec);
    for (auto iter = vec.cbegin(); iter != vec.cend(); ++iter) {
        std::cout << *iter;
        iter + 1 != vec.cend() ? std::cout << ", " : std::cout << std::endl;
    }

    int b[15] = {2, 3, 1, 4, 5, 6, 9, 8, 10, 11, 12, 13, 14, 15, 7};
    shellSort<int, size_t>(b, 15);
    for (auto i = 0; i < 14; ++i)
        std::cout << b[i] << ", ";
    std::cout << b[14] << std::endl;


    std::vector<int> vec1 = {2, 3, 1, 4, 5, 6, 9, 8, 10, 11, 12, 13, 14, 15, 7};
    shellSort<int_vec_t>(vec1);
    for (auto iter = vec1.cbegin(); iter != vec1.cend(); ++iter) {
        std::cout << *iter;
        iter + 1 != vec1.cend() ? std::cout << ", " : std::cout << std::endl;
    }

    return 0;
}
