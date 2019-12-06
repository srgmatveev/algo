#include <iostream>
#include "merge_sort.h"
#include "tim_sort.h"
void print(int* a, size_t n){
    for(auto i = 0 ; i < n; ++i)
        i!=n-1? std::cout<<a[i]<<", ":std::cout<<a[i]<<std::endl;
}

int main() {
    unsigned rand_value = 12334;
    srand(rand_value);
    int n  = 50000;
    int a[n];
    for (int i = 0; i<n; i++)
    {
        a[i] = (rand() % 100);
    }
    print(a,n);
    tim_sort<int,size_t >(a,  n);
    print(a,n);
    return 0;
}
