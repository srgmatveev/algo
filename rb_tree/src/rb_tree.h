//
// Created by sergio on 17.12.2019.
//
#include <iostream>

#pragma once

template<typename T>
class RedBlackTree {
public:
    explicit RedBlackTree(const T &negInf) {
        nullNode = new RedBlackNode;
        nullNode->left = nullNode->right = nullNode;
        header = new RedBlackNode{negInf};
        header->left = header->right = nullNode;

    };

    RedBlackTree(const RedBlackTree &rhs) {
        nullNode = new RedBlackNode;
        nullNode->left = nullNode->right = nullNode;
        header = new RedBlackNode{rhs.header->element};
        header->left = nullNode;
        header->right = clone(rhs.header->right);
    }

    RedBlackTree(RedBlackTree &&rhs);

    ~RedBlackTree() {
        reclaimMemory(header);
        if (nullNode) delete (nullNode);
    };

    T *findMin() const {
        if (isEmpty()) return nullptr;
        RedBlackNode *itr = header;
        while (itr->left != nullNode) itr = itr->left;
        return itr->element;
    }

    T *findMax() const {
        if (isEmpty()) return nullptr;
        RedBlackNode *itr = header;
        while (itr->right != nullNode) itr = itr->right;
        return itr->element;
    }

    T *find(const T &x) const {
        nullNode->element = x;
        RedBlackNode *curr = header;

        for (;;) {
            if (x < *curr->element) curr = curr->left;
            else if (*curr->element < x) curr = curr->right;
            else if (curr != nullNode) {
                nullNode->element = nullptr;
                return curr->element;
            } else {
                nullNode->element = nullptr;
                return nullptr;
            }
        }
    }

    bool contains(const T &x) const {
        return find(x);
    }

    bool isEmpty() const {
        return header->element;
    }

    void printTree() const {
        if (header->element == nullptr)
            std::cout << "Empty tree" << std::endl;
        else

            printTree(header);

    }

    void makeEmpty() {
        if (header->element) {
            reclaimMemory(header);
            header = nullNode;
        }
    }

    void insert(const T &x) {
        current = parent = grand = header;
        auto tmp = new T(x);
        nullNode->element = tmp;
        while (*current->element != x) {
            great = grand;
            grand = parent;
            parent = current;
            current = x < *current->element ? current->left : current->right;

            // Check if two red children; fix if so
            if (current->left->color == RED && current->right->color == RED)
                handleReorient(x);
        }
        // Insertion fails if already present
        if (current != nullNode) {
            nullNode->element = nullptr;
            delete tmp;
            return;
        }
        nullNode->element = nullptr;
        delete tmp;
        current = new RedBlackNode{x, nullNode, nullNode};
        // Attach to parent
        if (x < *parent->element)
            parent->left = current;
        else
            parent->right = current;
        handleReorient(x);

    }

    void remove(const T &x);

    enum {
        RED, BLACK
    };

    RedBlackTree &operator=(const RedBlackTree &rhs) {
        if (this != &rhs) {
            makeEmpty();
            header = clone(rhs.header);
            if (nullNode) delete nullNode;
            nullNode = rhs.nullNode;
        }
        return *this;
    }

    RedBlackTree &operator=(RedBlackTree &&rhs) {
        if (this != &rhs) {
            makeEmpty();
            if (nullNode) delete nullNode;
            header = rhs.header;
            nullNode = rhs.nullNode;
            rhs.header = nullptr;
            rhs.nullNode = nullptr;
        }
        return *this;
    }

private:
    struct RedBlackNode {
        T *element;
        RedBlackNode *left;
        RedBlackNode *right;
        int color;

        RedBlackNode()
                : element{nullptr}, left{nullptr}, right{nullptr}, color{BLACK} {}

        RedBlackNode(const T &theElement,
                     RedBlackNode *lt = nullptr, RedBlackNode *rt = nullptr,
                     int c = BLACK)
                : left{lt}, right{rt}, color{c} {
            this->element = new T(theElement);
        }

        RedBlackNode(T &&theElement, RedBlackNode *lt = nullptr,
                     RedBlackNode *rt = nullptr, int c = BLACK)
                : element{std::move(theElement)}, left{lt}, right{rt}, color{c} {}

        ~RedBlackNode() {
            if (element)
                delete (element);

        }
    };

    RedBlackNode *header;     // The tree header (contains negInf)
    RedBlackNode *nullNode;
    // Used in insert routine and its helpers (logically static)
    RedBlackNode *current;
    RedBlackNode *parent;
    RedBlackNode *grand;
    RedBlackNode *great;

    // Usual recursive stuff
    void reclaimMemory(RedBlackNode *t) {
        if (t->element) {
            reclaimMemory(t->left);
            reclaimMemory(t->right);
            delete t;
        }
    }

    void printTree(RedBlackNode *t) const {
        if (t->element) {
            if (t->color == BLACK)
                std::cout << "(" << *t->element << ")" << std::endl;
            else
                std::cout << "((" << *t->element << "))" << std::endl;
            printTree(t->left);
            printTree(t->right);
        } else {
            std::cout << "(" << "nil" << ")" << std::endl;
        }
    }


    RedBlackNode *clone(RedBlackNode *t) const {
        if (t == t->left) // Cannot test against nullNode!!!
            return nullNode;
        else
            return new RedBlackNode{t->element, clone(t->left),
                                    clone(t->right), t->color};

    };

    // Red-black tree manipulations
    void handleReorient(const T &item) {
        // Do the color flip
        current->color = RED;
        current->left->color = BLACK;
        current->right->color = BLACK;
        if (parent->color == RED)
            // Have to rotate
        {
            grand->color = RED;
            if (item < *grand->element != item < *parent->element)
                parent = rotate(item, grand); // Start dbl rotate
            current = rotate(item, great);
            current->color = BLACK;
        }
        header->color = BLACK; // Make root black

    }

    RedBlackNode *rotate(const T &item, RedBlackNode *theParent) {
        if (item < *theParent->element) {
            item < *theParent->left->element ?
            rotateWithLeftChild(theParent->left) : // LL
            rotateWithRightChild(theParent->left); // LR
            return theParent->left;
        } else {
            item < *theParent->right->element ?
            rotateWithLeftChild(theParent->right) : // RL
            rotateWithRightChild(theParent->right); // RR
            return theParent->right;
        }

    }

    void rotateWithLeftChild(RedBlackNode *&k2) {
        RedBlackNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2 = k1;
    }

    void rotateWithRightChild(RedBlackNode *&k1) {
        RedBlackNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1 = k2;
    }
};
