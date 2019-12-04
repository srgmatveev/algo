//
// Created by sergio on 04.12.2019.
//

#pragma once

void Drown(int *a, int i, int sz) {
    if (i >= sz)
        return;
    Drown(a, 2 * i + 2, sz);
    Drown(a, 2 * i + 1, sz);

    if (2 * i + 2 < sz and a[i] < a[2 * i + 2]) {
        std::swap(a[i], a[2 * i + 2]);

    }

    if (2 * i + 1 < sz and a[i] < a[2 * i + 1]) {
        std::swap(a[i], a[2 * i + 1]);

    }
}

void heap_sort(int a[], int n) {
    if (n < 2) return;
    Drown(a, 0, n);
    for (int i = n - 1; i >= 1; i--) {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        Drown(a, 0, i);
    }
}