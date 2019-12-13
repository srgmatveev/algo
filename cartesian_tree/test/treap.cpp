//
// Created by sergio on 11.12.2019.
//
#include "gtest/gtest.h"
#include "../src/cartesian_tree.h"

class Test_Treap : public ::testing::Test {
protected:
    Treap<int> *treap;
    Treap<int> *treap1;

    virtual void SetUp() {
        treap = new Treap<int>();
        treap1 = new Treap(4, 6);
    }

    virtual void TearDown() {
        if (treap) delete (treap);
        if (treap1) delete (treap1);
    }
};
/*
TEST_F(Test_Treap, Exist_Treap_Tree) {
    ASSERT_TRUE(treap);
}

TEST_F(Test_Treap, Treap_get_key_and_prior) {
    ASSERT_EQ(treap->get_key(), nullptr);
    ASSERT_EQ(treap->get_prior(), nullptr);
}

TEST_F(Test_Treap, Treap_get_key_and_prior_1) {

    ASSERT_EQ(*treap1->get_key(), 4);
    ASSERT_EQ(*treap1->get_prior(), 6);

}
*/
TEST_F(Test_Treap, Treap_insert) {
    ASSERT_EQ(*treap1->get_key(), 4);
    ASSERT_EQ(*treap1->get_prior(), 6);
    treap1->insert(7, 10);
    ASSERT_EQ(*treap1->get_key(), 7);
    ASSERT_EQ(*treap1->get_prior(), 10);
    treap1->insert(13, 8);
    ASSERT_EQ(*treap1->get_key(), 7);
    ASSERT_EQ(*treap1->get_prior(), 10);

    treap1->erase(13);

    treap->insert(7, 10);
    ASSERT_EQ(*treap->get_key(), 7);
    ASSERT_EQ(*treap->get_prior(), 10);
    treap->erase(10);
    treap->erase(7);
    treap->erase(7);
}
