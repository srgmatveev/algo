//
// Created by sergio on 13.12.2019.
//

#pragma once

template<typename T>
class AvlTree {
private:
    struct AvlNode {
        T element;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const T &ele, AvlNode *lt, AvlNode *rt, int h = 0)
                : element{ele}, left{lt}, right{rt}, height{h} {}

        AvlNode(T &&ele, AvlNode *lt, AvlNode *rt, int h = 0)
                : element{std::move(ele)}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode *head;
    static const int ALLOWED_IMBALANCE = 1;

    int height_r(AvlNode *t) const {
        return t == nullptr ? -1 : t->height;
    }

    void balance(AvlNode *&t) {
        if (!t) return;
        if (height_r(t->left) - height_r(t->right) > ALLOWED_IMBALANCE)
            if (height_r(t->left->left) >= height_r(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        else if (height_r(t->right) - height_r(t->left) > ALLOWED_IMBALANCE)
            if (height_r(t->right->right) >= height_r(t->right->left))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        t->height = std::max(height_r(t->left), height_r(t->right)) + 1;
    }

    void insert_p(const T &x, AvlNode *&t) {
        if (t == nullptr)
            t = new AvlNode{x, nullptr, nullptr};
        else if (x < t->element)
            insert_p(x, t->left);
        else if (t->element < x)
            insert_p(x, t->right);

        balance(t);
    }

    void rotateWithLeftChild(AvlNode *&k2) {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max(height_r(k2->left), height_r(k2->right)) + 1;
        k1->height = std::max(height_r(k1->left), k2->height) + 1;
        k2 = k1;
    }

    void rotateWithRightChild(AvlNode *&k1) {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = std::max(height_r(k1->left), height_r(k1->right)) + 1;
        k2->height = std::max(height_r(k2->right), k1->height) + 1;
        k1 = k2;
    }

    void doubleWithLeftChild(AvlNode *&k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(AvlNode *&k4) {
        rotateWithLeftChild(k4->right);
        rotateWithRightChild(k4);
    }


    void remove_p(const T &x, AvlNode *&t) {
        if (!t) return;
        if (x < t->element)
            remove_p(x, t->left);
        else if (t->element < x)
            remove_p(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) // Two children
        {
            t->element = findMin(t->right)->element;
            remove_p(t->element, t->right);
        } else {
            AvlNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }

        balance(t);
    }

    AvlNode *findMin(AvlNode *t) const {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

public:

    AvlTree(const T &ele) {
        head = new AvlNode(ele, nullptr, nullptr);
    }

    void insert(const T &ele) {
        this->insert_p(ele, head);
    }

    void remove(const T &ele) {
        this->remove_p(ele, head);
    }

    void rebalance() {
        balance(head);
    }

    int height() const {
        return height_r(head);
    }

    void clear() {
        while (head) {
            remove(head->element);
        }
    }

    ~AvlTree() {
        clear();
    }
};
