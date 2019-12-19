//
// Created by sergio on 17.12.2019.
//

#include "./gtest/gtest.h"
#include "../src/rb_tree.h"

class TEST_RB_Tree : public ::testing::Test {
protected:
    RedBlackTree<int> *rb_tree;

    virtual void SetUp() {
        rb_tree = new RedBlackTree<int>(13);
    }

    virtual void TearDown() {
        if (rb_tree) delete (rb_tree);
    }

};

TEST_F(TEST_RB_Tree, exist) {
    std::string output;
    std::string test{
            "(13)\n"
            "(nil)\n"
            "(nil)\n"
    };
    ASSERT_TRUE(rb_tree);
    testing::internal::CaptureStdout();
    rb_tree->printTree();
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, test);

}


TEST_F(TEST_RB_Tree, insert) {
    std::string output;
    std::string test{
            "(13)\n"
            "(nil)\n"
            "(nil)\n"
    };
    ASSERT_TRUE(rb_tree);
    testing::internal::CaptureStdout();
    rb_tree->printTree();
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, test);

    rb_tree->insert(17);
    test = {
            "(13)\n"
            "(nil)\n"
            "((17))\n"
            "(nil)\n"
            "(nil)\n"
    };
    testing::internal::CaptureStdout();
    rb_tree->printTree();
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, test);

    rb_tree->insert(8);
    test = {
            "(13)\n"
            "((8))\n"
            "(nil)\n"
            "(nil)\n"
            "((17))\n"
            "(nil)\n"
            "(nil)\n"
    };
    testing::internal::CaptureStdout();
    rb_tree->printTree();
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, test);

    rb_tree->insert(1);
    test = {
            "(13)\n"
            "(8)\n"
            "((1))\n"
            "(nil)\n"
            "(nil)\n"
            "(nil)\n"
            "(17)\n"
            "(nil)\n"
            "(nil)\n"
    };
    testing::internal::CaptureStdout();
    rb_tree->printTree();
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, test);

    rb_tree->insert(11);
    rb_tree->insert(12);
    test = {
            "(13)\n"
            "((8))\n"
            "(1)\n"
            "(nil)\n"
            "(nil)\n"
            "(11)\n"
            "(nil)\n"
            "((12))\n"
            "(nil)\n"
            "(nil)\n"
            "(17)\n"
            "(nil)\n"
            "(nil)\n"
    };

    testing::internal::CaptureStdout();
    rb_tree->printTree();
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, test);
    rb_tree->deleteByVal(8);
    rb_tree->deleteByVal(1);
    rb_tree->deleteByVal(13);
    rb_tree->deleteByVal(11);
    rb_tree->deleteByVal(12);
    rb_tree->deleteByVal(17);;
    test = {".Empty tree\n"};
    testing::internal::CaptureStdout();
    rb_tree->printTree();
    output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(rb_tree->isEmpty());
}
