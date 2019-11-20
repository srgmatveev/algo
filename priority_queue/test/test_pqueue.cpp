//
// Created by sergio on 15.11.2019.
//

#include <gtest/gtest.h>
#include "../src/pqueue.h"

TEST(Create_PQueue, PQUEUE_EMPTY_CREATE) {
    sergio::p_queue<int, int, size_t, long> *pQueue = new sergio::p_queue<int, int, size_t, long>();
    ASSERT_TRUE(pQueue);
    if (pQueue) delete (pQueue);
}

class PQueue_Test : public ::testing::Test {
protected:
    sergio::p_queue<int, int, size_t, long> *pQueue;
protected:

    virtual void SetUp() {
        pQueue = new sergio::p_queue<int, int, size_t, long>();
    }

    virtual void TearDown() {
        if (pQueue) delete (pQueue);
    }

};

TEST_F(PQueue_Test, add_1_item) {
    pQueue->enqueue(2, 15);
    int* val = pQueue->dequeue();
    ASSERT_EQ(*val,15);
    delete(val);
};

TEST_F(PQueue_Test, add_2_item) {
    pQueue->enqueue(2, 15);
    pQueue->enqueue(1, 11);
    int* val = pQueue->dequeue();
    ASSERT_EQ(*val,15);
    delete(val);
    val = pQueue->dequeue();
    ASSERT_EQ(*val,11);
    delete(val);
    val = pQueue->dequeue();
    ASSERT_EQ(val, nullptr);
};