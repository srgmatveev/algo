//
// Created by sergio on 18.11.2019.
//

#pragma once

#include "linked_list.h"

namespace sergio {

#define POS_NPOS -1

    template<typename T, typename U, typename X, typename Y>
    class DArray {
    private:
        X n = 0; //array size
        LinkedList<T, U> *arr;
    private:
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

        Y find_pos(LinkedList<T, U> *node) {
            if (!arr || !node) return POS_NPOS;
            X left = 0;
            X right = n;
            if (right > 0) --right;
            X search = 0;
            while (left <= right) {
                X mid = (left + right) / 2;
                if (node->get_priority() == arr[mid].get_priority()) {
                    search = mid;
                    return search;
                }
                if (node->get_priority() > arr[mid].get_priority()) {
                    if (mid == 0) break;
                    right = mid - 1;
                } else
                    left = mid + 1;
            }
            return POS_NPOS;
        }
        void delete_node(LinkedList<T, U> *node) {
            if (!node) return;
            Y pos = find_pos(node);
            if (pos != POS_NPOS) {
                if(pos == n-1){
                    arr[n-1].clear();
                    --n;
                    arr = (LinkedList<T, U> *) realloc(arr, sizeof(LinkedList<T, U>) * (n));
                } else {
                    for(auto i = pos; i < n-1; ++i){
                        arr[i] = arr[i+1];
                    }
                    arr[n-1].clear();
                    --n;
                    arr = (LinkedList<T, U> *) realloc(arr, sizeof(LinkedList<T, U>) * (n));
                }
            }
        }

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

        friend std::ostream &operator<<(std::ostream &out, const DArray<T, U, X, Y> *dArray) {
            for (auto i = 0; i < dArray->n; ++i) {
                out << dArray->arr[i] << std::endl;
            }
            return out;
        }
        T* top(){
            if(!arr) return nullptr;
            return arr->top();
        }

        void pop(){
            if(arr) pop(arr->get_priority());
        }

        T *top(const U &u)  {
            LinkedList<T, U> *node = this->find(u);
            if (node)
                return node->top();
            else
                return nullptr;
        }


        void pop(const U &u) {
            LinkedList<T, U> *node = this->find(u);
            if (!node) return;
            else if (node->not_empty()) {
                node->pop_front();
                if (node->empty()) delete_node(node);
            } else delete_node(node);
        }
        X size() const{
            return this->n;
        }

        ~DArray() {
            for (auto i = 0; i < n; ++i)
                arr[i].clear();
            if (arr)
                free(arr);


        }
    };
}