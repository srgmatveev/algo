//
// Created by sergio on 07.12.2019.
//

#pragma once

#include <cstring>

template<class T, class X>
void count_sort(T *t, const X &sz, const X &base) {
    if (sz < 2) return;
    X count[base];
    T tmp[sz];
    std::memset(count, '\0', sizeof(count));
    for (auto i = 0; i < sz; ++i)
        ++count[t[i]];

    for (auto i = 1; i < base; ++i)
        count[t[i]] += count[t[i - 1]];

    for (auto i = 0; i < sz; ++i) {
        tmp[count[t[i]] - 1] = t[i];
        count[t[i]]--;
    }
    for (auto i = 0; i < sz; ++i)
        t[i] = tmp[i];
}

