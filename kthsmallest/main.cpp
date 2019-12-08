#include <iostream>
#include "kth_smallest.h"

int main() {
    int arr[] = {1, 12, 0, 5, 7, 4, 19, 26};
    int sz = sizeof(arr) / sizeof(*arr);
    int k = 3;
    int elem = kthSmallest<int>(arr, 0, sz - 1, k);
    std::cout << elem << std::endl;
    return 0;
}
