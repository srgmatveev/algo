//
// Created by sergio on 05.12.2019.
//


#include "merge_sort.h"

#pragma once

template<typename T>
int get_min_run(T n) {
    T r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

template<typename T, typename X>
void insertion_sort(T *arr, const X &left, const X &right) {
    for (X i = left + 1; i <= right; i++) {
        T temp = arr[i];
        X j = i - 1;
        bool minus = false;
        while (arr[j] > temp && j >= left) {
            arr[j + 1] = arr[j];
             if(j==0) {minus =  true; break;}
             j--;
        }

            if(minus == true)
                arr[0] = temp;
            else
                arr[j + 1] = temp;
    }
}

template<class T, class X>
void tim_sort(T *t, const X &n) {
    if (n < 2) return;
    const X RUN = get_min_run<X>(n);
    for (X i = 0; i < n; i += RUN) {
        insertion_sort(t, i, std::min((i + RUN - 1), (n - 1)));
    }

    for (int size = RUN; size < n; size = 2 * size) {
        for (X left = 0; left < n; left += 2 * size) {
            X mid = left + size - 1;
            X right = std::min((left + 2 * size - 1), (n - 1));
            merge(t, left, mid + 1, right);
        }
    }
}