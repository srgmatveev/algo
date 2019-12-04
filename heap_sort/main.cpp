#include <iostream>
#include "heap_sort.h"

void print(int a[], size_t n){
    for(auto i = 0 ; i < n; ++i)
        i!=n-1? std::cout<<a[i]<<", ":std::cout<<a[i]<<std::endl;
}

int main() {
    unsigned rand_value = 123;
    srand(rand_value);
    int a[10];
    int n =sizeof(a)/sizeof(*a);
    for (int i = 0; i<n; ++i)
        a[i] = rand() % 20 - 10;
    print(a,n);
    heap_sort(a,n);
    print(a, n);
    return 0;
}
