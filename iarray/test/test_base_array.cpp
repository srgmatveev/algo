//
// Created by sergio on 21.11.2019.
//

#include "gtest/gtest.h"
#include "../src/base_array.h"

class BaseArray_Test : public ::testing::Test {
protected:
    BaseArray<int, size_t> *baseArray;

    virtual void SetUp() {
        baseArray = new BaseArray<int, size_t>();
    }

    virtual void TearDown() {
        if (baseArray) delete (baseArray);
    }
};

TEST_F(BaseArray_Test, one_element) {
    node<int> *node1 = new node<int>(4);
    node<int> *node2 = new node<int>(26);
    (*baseArray)[0] = &node1;
    (*baseArray)[1] = &node2;
    (*baseArray)[2] = &node2;
    std::cout << (*baseArray)[0] << std::endl;
    std::cout << (*baseArray)[1] << std::endl;
    std::cout << (*baseArray)[5] << std::endl;

    //delete (node1);
    //delete (node2);
}