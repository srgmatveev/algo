//
// Created by sergio on 15.11.2019.
//

#pragma once

#include <cstddef>

namespace sergio {
    template<typename T>
    struct item {
        int priority;
        T value;
        item *prev;
        item *next;
    };

    template<typename T>
    class p_queue {
        item<T> *array_priority;
        int max_priority, min_priority;
        int array_size = 0;
    public:
        p_queue() : max_priority(std::numeric_limits<int>::min()),
                    min_priority(std::numeric_limits<int>::min()), array_priority(nullptr) {}

        void enqueue(const int &priority, const T &item) { this->add_to_enq(priority, item); } // put element in queue
        T dequeue() const { return NULL; } // get element from queue
        int get_max_priority() {
            return max_priority;
        }

        int get_min_priority() {
            return min_priority;
        }

        ~p_queue() {
            if (array_priority) { free(array_priority); }
        }

    private:

        void add_to_enq(int priority, const T &item) {
            if (max_priority == min_priority && max_priority == std::numeric_limits<int>::min() && !array_priority) {
                array_priority = (sergio::item<T> *) malloc(sizeof(sergio::item<T>));
                if (!array_priority) {
                    perror("malloc");
                    return;
                }
                max_priority = min_priority = priority;
                array_priority[0].priority = priority;
                array_priority[0].value = item;
                array_priority[0].prev = nullptr;
                array_priority[0].next = nullptr;
                ++array_size;
            } else {
                auto cur = 0;
                bool found = false;
                auto n = array_size;
                for (auto i = 0; i < n; ++i) {
                    cur = n / 2;
                    if ((array_priority + cur)->priority == priority) {
                        found = true;
                        break;
                    } else if ((array_priority + cur)->priority < priority) {
                        i = cur;
                        continue;
                    } else {
                        i = 0;
                        n = n / 2 - 1;
                    }

                }
            }

        }
    };
}
