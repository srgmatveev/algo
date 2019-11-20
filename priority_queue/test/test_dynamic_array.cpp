//
// Created by sergio on 19.11.2019.
//
#include <gtest/gtest.h>
#include "../src/dynamic_array.h"

class DArray_Test : public ::testing::Test {
protected:
    sergio::DArray<int, int, size_t, long> *dArray;
protected:

    virtual void SetUp() {
        dArray = new sergio::DArray<int, int, size_t, long>();
    }

    virtual void TearDown() {
        if (dArray) delete (dArray);
    }

};

TEST_F(DArray_Test, add_1_item) {
    dArray->append(12, 1);
    testing::internal::CaptureStdout();
    std::cout << dArray;
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "priority = 1, list = {12}\n");
}

TEST_F(DArray_Test, add_2_item) {
    std::string output;
    dArray->append(12, 5);
    testing::internal::CaptureStdout();
    std::cout << dArray;
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "priority = 5, list = {12}\n");

    std::string test_string{
            "priority = 6, list = {18, 14}\n"
            "priority = 5, list = {12}\n"
    };
    dArray->append(14, 6);
    dArray->append(18, 6);
    testing::internal::CaptureStdout();
    std::cout << dArray;
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, test_string);
}

TEST_F(DArray_Test, add_3_item) {
    std::string output;
    std::string test_string{"priority = 5, list = {12}\n"};
    dArray->append(12, 5);
    testing::internal::CaptureStdout();
    std::cout << dArray;
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, test_string);

    test_string = {"priority = 6, list = {18, 14}\n"
                   "priority = 5, list = {12}\n"};
    dArray->append(14, 6);
    dArray->append(18, 6);
    testing::internal::CaptureStdout();
    std::cout << dArray;
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, test_string);

    test_string = {"priority = 6, list = {18, 14}\n"
                   "priority = 5, list = {12}\n"
                   "priority = 4, list = {1, 189}\n"};
    testing::internal::CaptureStdout();
    dArray->append(189, 4);
    dArray->append(1, 4);
    std::cout << dArray;
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, test_string);
}

TEST_F(DArray_Test, del_items) {
    dArray->append(14, 6);
    ASSERT_EQ(dArray->size(),1);
    int* val = dArray->top(6);
    ASSERT_EQ(*val,14);
    dArray->pop(6);
    ASSERT_EQ(dArray->size(),0);
    dArray->append(14, 6);
    ASSERT_EQ(dArray->size(),1);
    dArray->append(11, 5);
    ASSERT_EQ(dArray->size(),2);
    dArray->append(128, 5);
    val = dArray->top(5);
    ASSERT_EQ(*val,128);
    ASSERT_EQ(dArray->size(),2);
    dArray->pop(6);
    ASSERT_EQ(dArray->size(),1);
    dArray->pop(5);
    ASSERT_EQ(dArray->size(),1);
    dArray->pop(5);
    ASSERT_EQ(dArray->size(),0);
    dArray->pop(5);
    ASSERT_EQ(dArray->size(),0);

}