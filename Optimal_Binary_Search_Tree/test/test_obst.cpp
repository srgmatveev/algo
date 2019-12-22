//
// Created by sergio on 21.12.2019.
//

#include "./gtest/gtest.h"
#include "../src/optimal_bst.h"

class OBST_TEST : public ::testing::Test {
protected:
    OptimalBinarySearchTree<int, uint> *tree;

    virtual void SetUp() {
        tree = new OptimalBinarySearchTree<int, uint>();
    }

    virtual void TearDown() {
        if (tree) delete tree;
    }
};

TEST_F(OBST_TEST, exist){
    ASSERT_TRUE(tree);
}

TEST_F(OBST_TEST, insert_remove){
    tree->insert(10,34);
    ASSERT_EQ(*tree->findMax(),10);
    ASSERT_EQ(*tree->findMin(),10);
    tree->remove(10);
    ASSERT_FALSE(tree->findMax());
    tree->remove(10);
    tree->remove(5);

}

TEST_F(OBST_TEST, findMin){
    auto val = tree->findMin();
    ASSERT_FALSE(val);
}

TEST_F(OBST_TEST, printTree){
    ASSERT_EQ(tree->get_size(),0);
    tree->insert(10,34);
    ASSERT_EQ(tree->get_size(),1);
    tree->insert(12,8);
    ASSERT_EQ(tree->get_size(),2);

     tree->insert(20,50);
     ASSERT_EQ(tree->get_size(),3);

    tree->remove(20);
    tree->insert(20,50);
    ASSERT_EQ(tree->get_size(),3);
    ASSERT_EQ(tree->get_cost(), 142);
}
