//
// Created by sergio on 01.12.2019.
//

#pragma once

#include <type_traits>

template<typename T, typename X, typename = std::enable_if_t<std::is_literal_type<T>::value>>
void insertion_sort(T t[], const X &n) {
    if (n < 2) return;
    for (auto i = 1; i < n; ++i)
        for (auto j = i; j > 0 and t[j - 1] > t[j]; --j)
            std::swap(t[j - 1], t[j]);
}

template<typename T>
void insertion_sort(T& t) {
    std::size_t  n = t.size();
    if (n < 2) return;
    for (auto i = 1; i < n; ++i)
        for (auto j = i; j > 0 and t[j - 1] > t[j]; --j)
            std::swap(t[j - 1], t[j]);
}