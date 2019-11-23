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
        std::cout<<"worked"<<std::endl;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const node &node_lnk) {
        out << node_lnk;
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
        for(auto i=0; i< full_size;++i){
            if(((size_t*)arr)[i]) {
                node<T>*t = (node<T>*) *((size_t*)arr+i);
                if(t) {
                    for(auto j=i+1;j<full_size;++j){
                        node<T>*t1 = (node<T>*) *((size_t*)arr+j);
                        if(t1 == t) {*((size_t*)arr+j)=NULL;}
                    }
                    delete(t);
                }
            }
        }
        if (arr) free(arr);
    }

    BaseArray &operator=(node<T> **r_node) {
        std::cout << "equal = " << (*r_node)->val << std::endl;

        size_t* tmp = (size_t*)*r_node;
        ((size_t*)arr)[tmp_index] = (size_t)std::addressof(**r_node);
        std::cout << "address=" << *r_node <<" "<<tmp<<std::endl;
        std::cout << "address=" << *r_node <<" "<<std::hex<<((size_t*)arr)[tmp_index]<<std::endl;
        return *this;
    }

    BaseArray &operator[](const X index) {
        if (index > full_size - 1) std::range_error("out of index");
        std::cout << "index = " << index << std::endl;
        this->tmp_index = index;

        return *this;
    }


    friend std::ostream &operator<<(std::ostream &out, const BaseArray &baseArray) {
        if(((size_t*)baseArray.arr)[baseArray.tmp_index]) {
            out<<std::dec<<((node<T>**)baseArray.arr)[baseArray.tmp_index]->val;
        }

         return out;
    }

};


