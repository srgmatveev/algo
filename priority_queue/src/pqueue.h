//
// Created by sergio on 15.11.2019.
//

#pragma once

#include <cstddef>
#include "dynamic_array.h"

namespace sergio {


    template<typename T, typename U, typename X, typename Y>
    class p_queue {
        DArray<T, U, X, Y> *dArray;
    public:
        p_queue() { dArray = new DArray<T, U, X, Y>(); }

        void enqueue(const U &priority, const T &item) { dArray->append(item, priority); } // put element in queue
        T *dequeue() const {
            T *t = dArray->top();
            if (t) {
                T *ret_t = new T();
                *ret_t = *t;
                dArray->pop();
                return ret_t;
            }
            return nullptr;
        } // get element from queue


        ~p_queue() {
            if (dArray) { delete (dArray); }
        }

    private:


    };
}
