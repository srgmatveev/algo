#include <iostream>
#include "utils.h"
#include  "counting_sort.h"
#include "radix_sort.h"
int main() {
    int a[ ]= {10, 45, 56, 900, 507, 24, 2, 66, 1000};
    size_t size = sizeof(a)/ sizeof(*a);
    print(a, size);
    radix_sort(a, size);
    //count_sort<int, size_t >(a, size, 4);
    print(a, size);
    return 0;
}
