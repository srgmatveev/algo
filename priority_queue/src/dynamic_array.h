//
// Created by sergio on 18.11.2019.
//

#pragma once

#include "linked_list.h"

namespace sergio {
    template<typename T, typename U, typename X>
    class DArray {
    private:
        X n = 0; //array size
        LinkedList<T, U> *arr;
    public:
        void append(T t, const U &u) {
            LinkedList<T, U> *node = this->find(u);
            if (node) { node->push_front(t); }
            else {
                ++n;
                arr = (LinkedList<T, U> *) realloc(arr, sizeof(LinkedList<T, U>) * (n));
                memset(arr + n - 1, '\0', sizeof(LinkedList<T, U>));
                if (!arr) {
                    --n;
                    throw std::bad_alloc();
                }
                arr[n - 1].stand_alone = false;
                arr[n - 1].set_priority(u);
                arr[n - 1].push_front(t);
                this->merge_sort();
            }
        }

        void merge_sort() {
            X BlockSizeIterator;
            X BlockIterator;
            X LeftBlockIterator;
            X RightBlockIterator;
            X MergeIterator;

            X LeftBorder;
            X MidBorder;
            X RightBorder;
            for (BlockSizeIterator = 1; BlockSizeIterator < n; BlockSizeIterator *= 2) {
                for (BlockIterator = 0; BlockIterator < n - BlockSizeIterator; BlockIterator += 2 * BlockSizeIterator) {
                    LeftBlockIterator = 0;
                    RightBlockIterator = 0;
                    LeftBorder = BlockIterator;
                    MidBorder = BlockIterator + BlockSizeIterator;
                    RightBorder = BlockIterator + 2 * BlockSizeIterator;
                    RightBorder = (RightBorder < n) ? RightBorder : n;
                    LinkedList<T, U> *SortedBlock = new LinkedList<T, U>[RightBorder - LeftBorder];

                    while (LeftBorder + LeftBlockIterator < MidBorder && MidBorder + RightBlockIterator < RightBorder) {
                        if (arr[LeftBorder + LeftBlockIterator].get_priority() >
                            arr[MidBorder + RightBlockIterator].get_priority()) {
                            SortedBlock[LeftBlockIterator + RightBlockIterator] = arr[LeftBorder + LeftBlockIterator];
                            LeftBlockIterator += 1;
                        } else {
                            SortedBlock[LeftBlockIterator + RightBlockIterator] = arr[MidBorder + RightBlockIterator];
                            RightBlockIterator += 1;
                        }
                    }
                    while (LeftBorder + LeftBlockIterator < MidBorder) {
                        SortedBlock[LeftBlockIterator + RightBlockIterator] = arr[LeftBorder + LeftBlockIterator];
                        LeftBlockIterator += 1;
                    }
                    while (MidBorder + RightBlockIterator < RightBorder) {
                        SortedBlock[LeftBlockIterator + RightBlockIterator] = arr[MidBorder + RightBlockIterator];
                        RightBlockIterator += 1;
                    }

                    for (MergeIterator = 0; MergeIterator < LeftBlockIterator + RightBlockIterator; MergeIterator++) {
                        arr[LeftBorder + MergeIterator] = SortedBlock[MergeIterator];
                    }
                    delete[] SortedBlock;
                }
            }
        }


        LinkedList<T, U> *find(const U &u) {
            if (!arr) return nullptr;
            X left = 0;
            X right = n;
            if (right > 0) --right;
            bool search = false;
            X searcher = 0;
            while (left <= right) {
                X mid = (left + right) / 2;
                if (u == arr[mid].get_priority()) {
                    search = true;
                    searcher = mid;
                    break;
                }
                if (u > arr[mid].get_priority()) {
                    if (mid == 0) break;
                    right = mid - 1;
                } else
                    left = mid + 1;
            }
            if (!search) return nullptr;
            else return arr + searcher;
        }

        friend std::ostream &operator<<(std::ostream &out, const DArray<T, U, X> *dArray) {
            for (auto i = 0; i < dArray->n; ++i) {
                out << dArray->arr[i] << std::endl;
            }
            return out;
        }

        ~DArray() {
            for (auto i = 0; i < n; ++i)
                arr[i].clear();
            if (arr)
                free(arr);


        }
    };
}