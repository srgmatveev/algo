//
// Created by sergio on 27.11.2019.
//

#include <type_traits>
#include <stdexcept>
#include <iostream>
#include "list_array.h"

#pragma once

template<typename T, typename X, typename = std::enable_if_t<std::is_unsigned<X>::value>>
class IArray {
private:
    X chunk_size;
    List_Array<T, X> *listArray;
    X tmp_index;
    bool enable{false};
public:
    IArray(const X &chunk_size = FULL_SIZE) : chunk_size(chunk_size) {
        if (!chunk_size) throw std::invalid_argument("chunk_size can't be a zero");
        listArray = new List_Array<T, X>(chunk_size);
    }

    ~IArray() {
        if (listArray) delete (listArray);
    }

    IArray &operator=(const T &data) {
        if (enable)
            listArray->at(tmp_index, data);
        enable = false;
        return *this;
    }

    IArray &operator[](const X &index) {
        tmp_index = index;
        enable = true;
        return *this;
    }


    operator node<T> *() {
        if (this->enable) {
            this->enable = false;
            node<T> *tmp = listArray->get(tmp_index);
            if (tmp) {
                node<T> *ret = new node<T>();
                ret->val = tmp->val;
                return ret;
            } else return nullptr;

        }
        return nullptr;
    }

    void remove(const X& x) {
        listArray->remove(x);
    }
};
