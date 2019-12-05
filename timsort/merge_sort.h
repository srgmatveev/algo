//
// Created by sergio on 05.12.2019.
//

#pragma once

#include <thread>

template<class T, class X>
void merge(T *t, const X &left, const X &mid, const X &right) {
    X n = right - left + 1;
    X *tmp = (X *) malloc((n) * sizeof(X));
    X step = 0;
    X fst = left;
    X scnd = mid;
    while (step < n) {
        if ((scnd > right) or (t[fst] < t[scnd] and fst < mid)) {
            tmp[step] = t[fst];
            ++fst;
        } else {
            tmp[step] = t[scnd];
            ++scnd;
        }
        ++step;
    }
    for (auto i = 0; i < n; ++i) {
        t[left + i] = tmp[i];
    }
    if (tmp) free(tmp);

}

template<class T, class X>
void merge_sort(T &t, const X &left, const X &right) {
    if (right - left > 0) {
        const auto mid = (left + right) / 2;
        merge_sort(t, left, mid);
        merge_sort(t, mid + 1, right);
        merge(&t, left, mid + 1, right);
    }
}
