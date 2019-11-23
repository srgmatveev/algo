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

TEST_F(BaseArray_Test, as_array_element) {
    std::string output;
    node<int> *node1 = new node<int>(4);
    node<int> *node2 = new node<int>(26);
    node<int> *node3 = new node<int>(18);
    node<int> *node5 = new node<int>(28);
    (*baseArray)[0] = node1;
    (*baseArray)[1] = node2;
    (*baseArray)[2] = node2;
    testing::internal::CaptureStdout();
    std::cout << (*baseArray)[0];
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "4");
    testing::internal::CaptureStdout();
    std::cout << (*baseArray)[1];
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "26");
    testing::internal::CaptureStdout();
    std::cout << (*baseArray)[5];
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "");
    node<int> *node4 = (*baseArray)[2];
    testing::internal::CaptureStdout();
    std::cout << node4;
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "26");

    testing::internal::CaptureStdout();
    (*baseArray)[2] = node3;
    std::cout << (*baseArray)[2];
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "18");

    testing::internal::CaptureStdout();
    (*baseArray)[2] = node5;
    std::cout << (*baseArray)[2];
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "28");


}

TEST_F(BaseArray_Test, as_push_pop_element) {
    std::string output;
    node<int> *node1 = new node<int>(88);
    node<int> *node2 = new node<int>(18);
    baseArray->push_back(node1);
    baseArray->push_back(node1);
    baseArray->push_back(node1);
    baseArray->push_back(node1);
    for(auto i = 0; i< 4; ++i) {
        testing::internal::CaptureStdout();
        std::cout<<(*baseArray)[i];
        output = testing::internal::GetCapturedStdout();
        ASSERT_EQ(output, "88");
    }

    (*baseArray)[1] = node2;
    testing::internal::CaptureStdout();
    std::cout<<(*baseArray)[1];
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "18");
}