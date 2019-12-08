//
// Created by sergio on 08.12.2019.
//

#pragma once

template<typename T, typename X>
inline void print(const T * const a, const X &n) {
    for (auto i = 0; i < n; ++i)
        i != n - 1 ? std::cout << a[i] << ", " : std::cout << a[i] << std::endl;
}
