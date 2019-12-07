//
// Created by sergio on 07.12.2019.
//

#pragma once

#include "utils.h"

template<class T, class X>
T *get_max(const T *const t, const X &sz) {
    if (!sz) return nullptr;
    T *max = const_cast<T *>(t);
    if (sz < 2) return max;
    for (auto i = 1; i < sz; ++i) {
        if (*max < t[i]) max = const_cast<T *>(t + i);
    }
    return max;
}

template<class T, class X>
void countSort(T *const t, const X &sz, const X &exp, size_t base) {
    if (sz < 2) return;
    int output[sz];
    int count[base];
    std::memset(count, 0, sizeof(count));

    for (auto i = 0; i < sz; ++i) {
        ++count[(t[i] / exp) % base];
    }

    for (auto i = 1; i < base; ++i) {
        count[i] += count[i - 1];
    }

    for (auto i = sz - 1; i + 1 > 0; i--) {
        output[count[(t[i] / exp) % base] - 1] = t[i];
        count[(t[i] / exp) % base]--;
    }

    for (auto i = 0; i < sz; ++i)
        t[i] = output[i];
}

template<class T, class X>
void radix_sort(const T *t, const X &sz, size_t base = 10) {
    T *max_ref = get_max(t, sz);
    if (sz < 2) return;
    if (!max_ref) return;
    T max = *max_ref;

    for (auto exp = 1; max / exp > 0; exp *= base)
        countSort<T, X>(const_cast<T *>(t), sz, exp, base);

}