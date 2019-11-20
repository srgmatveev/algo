//
// Created by sergio on 18.11.2019.
//


#include <gtest/gtest.h>
#include "../src/linked_list.h"

class LinkedList_Test : public ::testing::Test {
protected:
    sergio::LinkedList<int, int> *linkedList;
protected:

    virtual void SetUp() {
       linkedList = new sergio::LinkedList<int, int>(5);
    }

    virtual void TearDown() {
        if ( linkedList) delete(linkedList);
    }

};

TEST_F(LinkedList_Test, add_1_item){
    ASSERT_EQ(linkedList->size(),0);
    linkedList->push_front(15);
    ASSERT_EQ(linkedList->size(),1);
    linkedList->pop_front();
    ASSERT_EQ(linkedList->size(),0);

}

TEST_F(LinkedList_Test, add_2_item){
    ASSERT_EQ(linkedList->size(),0);
    linkedList->push_front(15);
    ASSERT_EQ(linkedList->size(),1);
    linkedList->push_front(22);
    ASSERT_EQ(linkedList->size(),2);
    linkedList->pop_front();
    ASSERT_EQ(linkedList->size(),1);
    linkedList->pop_front();
    ASSERT_EQ(linkedList->size(),0);
}

TEST_F(LinkedList_Test, add_3_item){
    ASSERT_EQ(linkedList->size(),0);
    linkedList->push_front(15);
    ASSERT_EQ(linkedList->size(),1);
    linkedList->push_front(22);
    ASSERT_EQ(linkedList->size(),2);
    linkedList->push_front(44);
    ASSERT_EQ(linkedList->size(),3);
    testing::internal::CaptureStdout();
    std::cout << linkedList;
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output,"priority = 5, list = {44, 22, 15}");
    linkedList->pop_front();
    testing::internal::CaptureStdout();
    std::cout << linkedList;
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output,"priority = 5, list = {22, 15}");
    ASSERT_EQ(linkedList->size(),2);
    linkedList->pop_front();
    testing::internal::CaptureStdout();
    std::cout << linkedList;
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output,"priority = 5, list = {15}");
    ASSERT_EQ(linkedList->size(),1);
    linkedList->pop_front();
    testing::internal::CaptureStdout();
    std::cout << linkedList;
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output,"priority = 5");
    ASSERT_EQ(linkedList->size(),0);
}


TEST_F(LinkedList_Test, get_data) {
    ASSERT_EQ(linkedList->size(), 0);
    linkedList->push_front(15);
    ASSERT_EQ(linkedList->size(), 1);
    linkedList->push_front(22);
}
