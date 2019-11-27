//
// Created by sergio on 27.11.2019.
//
#include "gtest/gtest.h"
#include "../src/iarray.h"


class Test_IArray:public ::testing::Test{
protected:
 IArray<int, size_t > iArray;

};

TEST_F(Test_IArray,test){
    iArray[0]=19;
    node<int>* result =  iArray[0];
    ASSERT_EQ(result->val, 19);
    if(result) delete(result);
    iArray.remove(0);
}