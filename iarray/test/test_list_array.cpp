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
    int a = 18;
    listArray->at(0,18);
    listArray->at(1,28);
    listArray->at(2,128);
    listArray->at(3,108);
    listArray->at(3,14);
}