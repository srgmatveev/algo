//
// Created by sergio on 01.12.2019.
//

#pragma once

template<typename T, typename X>
void shellSort(T t[], const X &n) {
    for (auto gap = n / 2; gap > 0; gap /= 2) {
        for (auto i = gap; i < n; ++i) {
            auto temp = t[i];
            auto j = 0;
            for (j = i; j >= gap and t[j - gap] > temp; j -= gap)
                t[j] = t[j - gap];
            t[j] = temp;
        }
    }
}


template<typename T>
void shellSort(T &t) {
    auto n = t.size();
    for (auto gap = n / 2; gap > 0; gap /= 2) {
        for (auto i = gap; i < n; ++i) {
            auto temp = t[i];
            auto j = 0;
            for (j = i; j >= gap and t[j - gap] > temp; j -= gap)
                t[j] = t[j - gap];
            t[j] = temp;
        }
    }
}