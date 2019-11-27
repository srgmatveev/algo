//
// Created by sergio on 25.11.2019.
//

#include "gtest/gtest.h"
#include "../src/list_array.h"

class Test_List_Array : public ::testing::Test {
protected:
    List_Array<int, size_t> *listArray;

    virtual void SetUp() {
        listArray = new List_Array<int, size_t>();
    }

    virtual void TearDown() {
        if (listArray) delete (listArray);
    }
};

TEST_F(Test_List_Array,add_list_array){
    node<int>* result = nullptr;
    ASSERT_EQ(listArray->size(),0);
    int a = 18;
    listArray->at(0,18);
    result = listArray->get(0);
    ASSERT_EQ(result->val, 18);
    ASSERT_EQ(listArray->full_size(),1);

    listArray->at(1,28);
    result = listArray->get(1);
    ASSERT_EQ(result->val, 28);
    ASSERT_EQ(listArray->full_size(),2);

    listArray->at(2,128);
    ASSERT_EQ(listArray->size(),1);
    result = listArray->get(2);
    ASSERT_EQ(result->val, 128);
    ASSERT_EQ(listArray->full_size(),3);

    listArray->at(3,108);
    ASSERT_EQ(listArray->size(),2);
    result = listArray->get(3);
    ASSERT_EQ(result->val, 108);
    ASSERT_EQ(listArray->full_size(),4);

    listArray->at(4,14);
    ASSERT_EQ(listArray->size(),2);
    result = listArray->get(4);
    ASSERT_EQ(result->val, 14);
    ASSERT_EQ(listArray->full_size(),5);

    listArray->at(4,28);
    ASSERT_EQ(listArray->size(),2);
    result = listArray->get(4);
    ASSERT_EQ(result->val, 28);
    ASSERT_EQ(listArray->full_size(),5);

    listArray->at(2,11);
    ASSERT_EQ(listArray->size(),2);
    result = listArray->get(2);
    ASSERT_EQ(result->val, 11);

    result = listArray->get(25);
    ASSERT_FALSE(result);


    ASSERT_EQ(listArray->full_size(),5);

    listArray->remove(2);
    result = listArray->get(2);
    ASSERT_EQ(result->val, 108);
    ASSERT_EQ(listArray->full_size(),4);

}