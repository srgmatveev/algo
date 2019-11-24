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
    (*baseArray)[2] = node3;
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
    ASSERT_EQ(output, "18");


    testing::internal::CaptureStdout();
    (*baseArray)[2] = node5;
    std::cout << (*baseArray)[2];
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "28");
}

TEST_F(BaseArray_Test, as_push_element) {
    std::string output;
    node<int> *node1 = new node<int>(88);
    node<int> *node2 = new node<int>(88);
    node<int> *node3 = new node<int>(88);
    node<int> *node4 = new node<int>(88);
    node<int> *node5 = new node<int>(18);
    baseArray->push_back(node1);
    baseArray->push_back(node2);
    baseArray->push_back(node3);
    baseArray->push_back(node4);
    for(auto i = 0; i< 4; ++i) {
        testing::internal::CaptureStdout();
        std::cout<<(*baseArray)[i];
        output = testing::internal::GetCapturedStdout();
        ASSERT_EQ(output, "88");
    }

    (*baseArray)[1] = node5;
    testing::internal::CaptureStdout();
    std::cout<<(*baseArray)[1];
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "18");
}

TEST_F(BaseArray_Test, as_pop_element) {
    std::string output;
    node<int> *node1 = new node<int>(88);
    node<int> *node2 = new node<int>(28);
    node<int> *node3 = new node<int>(18);
    node<int> *node4 = new node<int>(18);
    node<int> *node5 = new node<int>(18);
    node<int> *node6 = new node<int>(18);
    node<int> *node7 = new node<int>(18);
    node<int> *node8 = new node<int>(18);
    node<int> *node9 = new node<int>(18);
    node<int> *node10 = new node<int>(108);
    node<int> *node11 = new node<int>(18);
    node<int> *node111 = new node<int>(188);
    baseArray->push_back(node1);
    baseArray->push_back(node2);
    baseArray->push_back(node3);
    baseArray->push_back(node4);
    baseArray->push_back(node5);
    baseArray->push_back(node6);
    baseArray->push_back(node7);
    baseArray->push_back(node8);
    baseArray->push_back(node9);
    ASSERT_TRUE(baseArray->push_back(node10));
    node<int> *test_node = baseArray->insert_before(node111,9);
    testing::internal::CaptureStdout();
    std::cout<<test_node;
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "108");
    ASSERT_FALSE(baseArray->push_back(node11));
    baseArray->pop_back();
    baseArray->pop_back();
    baseArray->pop_back();
    node<int> *node123 = new node<int>(1111);
    ASSERT_FALSE(baseArray->insert_before(node123,2));
    if(node11) delete(node11);
    if(test_node) delete(test_node);
}