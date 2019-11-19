//
// Created by sergio on 19.11.2019.
//
#include <gtest/gtest.h>
#include "../src/dynamic_array.h"
class DArray_Test : public ::testing::Test {
protected:
    sergio::DArray<int,int,size_t > *dArray;
protected:

    virtual void SetUp() {
        dArray = new sergio::DArray<int,int,size_t>();
    }

    virtual void TearDown() {
        if (dArray ) delete (dArray );
    }

};

TEST_F(DArray_Test,add_1_item){
    dArray->append(12,1);
    //std::cout<<dArray;

}

TEST_F(DArray_Test,add_2_item){
    dArray->append(12,5);
    //std::cout<<dArray;

    dArray->append(14,0);
    std::cout<<dArray;
}