//
// Created by sergio on 22.11.2019.
//

#pragma once

#include <type_traits>
#include <cstdlib>
#include <new>
#include <cstring>

#define FULL_SIZE 10

template<typename T>
struct node {
    T val;

    node() = default;

    node(const T &val) : val(val) {};

    node &operator=(node *rht) {
        this->val = rht->val;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const node &node_lnk) {
        out << node_lnk.val;
        return out;
    }

    friend std::ostream &operator<<(std::ostream &out, const node *node_lnk) {
        out << node_lnk->val;
        return out;
    }
};

template<class T, class X, typename = std::enable_if_t<std::is_unsigned<X>::value>>
class BaseArray {
private:
    X full_size;
    X n;
    void *arr;
    X tmp_index;
    T val;

    void init(const X &x) {
        if (x == 0) throw std::invalid_argument("base array size must be great then zero");
        arr = malloc(sizeof(void *) * full_size);
        if (!arr) {
            throw std::bad_alloc();
        }
        memset(arr, '\0', sizeof(void *) * full_size);
    }

public:
    BaseArray(const X &x = FULL_SIZE) : full_size(x), n{0}, tmp_index{0} { init(full_size); }

    ~BaseArray() {
        for (auto i = 0; i < full_size; ++i) {
            if (((size_t *) arr)[i]) {
                node<T> *t = (node<T> *) *((size_t *) arr + i);
                if (t) {
                    delete (t);
                }
            }
        }
        if (arr) free(arr);
    }

    operator node<T> *() {
        return (node<T> *) *((size_t *) arr + tmp_index);
    }

    BaseArray &operator=(node<T> *r_node) {
        node<T> *t = (node<T> *) *((size_t *) arr + tmp_index);
        if (t) {
            delete (t);
            *((size_t *) arr + tmp_index) = 0;
        }
        ((size_t *) arr)[tmp_index] = (size_t) std::addressof(*r_node);
        return *this;
    }

    BaseArray &operator[](const X index) {
        if (index > full_size - 1) std::range_error("out of index");
        if (n < index) n = index + 1;
        this->tmp_index = index;
        return *this;
    }

    bool push_back(node<T> *t) {
        if ((n + 1) > full_size) {
            n = full_size - 1;
            return false;
        }
        ((size_t *) arr)[n] = (size_t) std::addressof(*t);
        n++;
        tmp_index = n - 1;
        return true;
    }

    void pop_back() {
        if (!n) return;
        node<T> *t = (node<T> *) *((size_t *) arr + n - 1);
        if (t) {
            delete (t);
            *((size_t *) arr + n - 1) = 0;
        }
        --n;
        tmp_index = n - 1;
    }

    node<T> *insert_before(node<T> *t, const X &index) {
        if (index > full_size - 1) std::range_error("out of index");
        if (index == n) {
            this->push_back(t);
            return nullptr;
        }
        if (index < n) {
            if ((index + 1) >= full_size) {
                node<T> *tt = (node<T> *) *((size_t *) arr + n - 1);
                *((size_t *) arr + tmp_index) = 0;
                ((size_t *) arr)[index] = (size_t) std::addressof(*t);
                return tt;
            } else {
                for (auto i = n; i > index; --i)
                    *((size_t *) arr + i) = *((size_t *) arr + i - 1);
                n++;
                tmp_index = n - 1;
                ((size_t *) arr)[index] = (size_t) std::addressof(*t);
                return nullptr;
            }
        }
        return nullptr;
    }

    bool empty(){
        if(!n) return true;
        return false;
    }

    X get_size(){
        return n;
    }

    X get_full_size(){
        return this->full_size;
    }
    friend std::ostream &operator<<(std::ostream &out, const BaseArray &baseArray) {
        if (((size_t *) baseArray.arr)[baseArray.tmp_index]) {
            out << ((node<T> **) baseArray.arr)[baseArray.tmp_index]->val;
        }

        return out;
    }
};


