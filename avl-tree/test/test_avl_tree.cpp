//
// Created by sergio on 13.12.2019.
//
#include "gtest/gtest.h"
#include "../src/avl_tree.h"

class TEST_Avl : public ::testing::Test {
protected:
    AvlTree<int> *tree;

    virtual void SetUp() {
        tree = new AvlTree<int>(15);
    }

    virtual void TearDown() {
        if (tree) delete (tree);
    }
};

TEST_F(TEST_Avl, test_not_null){
    ASSERT_TRUE(tree);
}

TEST_F(TEST_Avl, test_insert){
    ASSERT_EQ(tree->height(),0);
    tree->insert(28);
    ASSERT_EQ(tree->height(),1);
    tree->insert(28);
    ASSERT_EQ(tree->height(),1);
    tree->remove(28);
    ASSERT_EQ(tree->height(),0);
}

TEST_F(TEST_Avl, test_insert1){

    ASSERT_EQ(tree->height(),0);
    tree->insert(28);
    ASSERT_EQ(tree->height(),1);
    tree->insert(15);
    ASSERT_EQ(tree->height(),1);
    tree->insert(14);
    ASSERT_EQ(tree->height(),1);
    tree->insert(13);
    ASSERT_EQ(tree->height(),2);
}