//
// Created by sergio on 15.11.2019.
//

#include <gtest/gtest.h>
#include "../src/pqueue.h"

TEST(Create_PQueue, PQUEUE_EMPTY_CREATE) {
    sergio::p_queue<int> *pQueue = new sergio::p_queue<int>();
    ASSERT_TRUE(pQueue);
    if (pQueue) delete (pQueue);
}

class PQueue_Test : public ::testing::Test {
protected:
    sergio::p_queue<int> *pQueue;
protected:

    virtual void SetUp() {
        pQueue = new sergio::p_queue<int>();
    }

    virtual void TearDown() {
        if (pQueue) delete (pQueue);
    }

};

TEST_F(PQueue_Test, add_1_item){
    pQueue->enqueue(2,15);
    ASSERT_EQ(pQueue->get_max_priority(),2);
    ASSERT_EQ(pQueue->get_min_priority(),2);
};

TEST_F(PQueue_Test, add_2_item){
    pQueue->enqueue(2,15);
    pQueue->enqueue(1,11);
    //ASSERT_EQ(pQueue->get_max_priority(),2);
    //ASSERT_EQ(pQueue->get_min_priority(),2);
};