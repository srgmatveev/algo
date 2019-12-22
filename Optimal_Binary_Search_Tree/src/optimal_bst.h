//
// Created by sergio on 21.12.2019.
//
#include <iostream>
#include <ostream>

#pragma once

template<typename Comparable, typename V>
class OptimalBinarySearchTree {
public:
    OptimalBinarySearchTree() : root{nullptr} {}

    OptimalBinarySearchTree(const OptimalBinarySearchTree &rhs) : root{nullptr} {
        root = clone(rhs.root);
    }

    OptimalBinarySearchTree(OptimalBinarySearchTree &&rhs) : root{rhs.root} {
        rhs.root = nullptr;
    }

    ~OptimalBinarySearchTree() {
        makeEmpty();
    }

    const Comparable *findMin() const {
        BinaryNode *node = findMin(root);
        return !node ? nullptr : &node->element.first;
    }

    const Comparable *findMax() const {
        BinaryNode *node = findMax(root);
        return !node ? nullptr : &node->element.first;
    }

    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    bool isEmpty() const {
        return !root;
    }

    void printTree(std::ostream &out = std::cout) const {
        DISPLAY(this->root, 0, out);
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    const V& get_cost() const{
        return this->cost;
    }

    float Av_Weight(){
        return this->average_weight;
    }

    void insert(const Comparable &key, const V &freq) {
        insert(key, freq, root);
    }


    void remove(const Comparable &key) {
        remove(key, root);
    }

    size_t get_size() {
        return get_size(root);
    }

    OptimalBinarySearchTree &operator=(const OptimalBinarySearchTree &rhs) {
        if (this != &rhs) {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }

    OptimalBinarySearchTree &operator=(OptimalBinarySearchTree &&rhs) {
        if (this != &rhs)
            std::swap(root, rhs.root);
        return *this;
    }

private:
    float average_weight{0};
    V cost{0};

    struct BinaryNode {
        std::pair<Comparable, V> element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode(const Comparable &theElement, const V &freq, BinaryNode *lt, BinaryNode *rt)
                : left{lt}, right{rt} {
            element = std::make_pair(theElement, freq);
        }

        BinaryNode(Comparable &&theElement, V &&freq, BinaryNode *lt, BinaryNode *rt)
                : left{lt}, right{rt} {
            element = std::make_pair(std::move(theElement), std::move(freq));
        }

        ~BinaryNode() = default;

    };

    BinaryNode *root;

    size_t get_size(BinaryNode *&t) {
        size_t size = 0;
        if (t == nullptr) return size;
        ++size;
        if (t->left)
            size += get_size(t->left);
        if (t->right)
            size += get_size(t->right);
        return size;
    }

    void fill_node(std::map<Comparable, V> &keys, BinaryNode *&t) {
        if (t == nullptr) return;
        keys.insert(std::pair<Comparable, V>(t->element.first, t->element.second));
        if (t->left) fill_node(keys, t->left);
        if (t->right) fill_node(keys, t->right);
    }

    //Construct the optimal binary search tree
    BinaryNode *CONSTRUCT_OBST(V i, V j, Comparable **R, std::vector<Comparable> &keys, std::vector<V> &freqs) {
        BinaryNode *p;

        if (i == j)
            p = NULL;
        else {
            Comparable key = keys[R[i][j]];
            V freq = freqs[R[i][j]];
            p = new BinaryNode{key, freq, nullptr, nullptr};
            p->left = CONSTRUCT_OBST(i, R[i][j] - 1, R, keys, freqs); //left subtree
            p->right = CONSTRUCT_OBST(R[i][j], j, R, keys, freqs); //right subtree
        }
        return p;
    }

    void insert(const Comparable &key, const V &freq, BinaryNode *&t) {
        if (t == nullptr)
            t = new BinaryNode{key, freq, nullptr, nullptr};
        else {
            std::map<Comparable, V> keys;
            fill_node(keys, t);
            keys.insert(std::pair<Comparable, V>(key, freq));
            std::vector<V> p;
            p.reserve(keys.size() + 1);
            p.push_back(0);
            for (auto &item: keys) {
                p.push_back(item.second);
            }
            std::vector<Comparable> kkeys;
            kkeys.reserve(keys.size() + 1);
            kkeys.push_back(0);
            for (auto &item: keys) {
                kkeys.push_back(item.first);
            }
            makeEmpty(t);
            size_t n = keys.size();
            //Comparable **R = new Comparable *[n + 1];
            Comparable **R = new Comparable *[n + 1];
            V **W = new V *[n + 1], **C = new V *[n + 1];
            for (auto i = 0; i <= n; ++i) {
                W[i] = new V[n + 1];
                C[i] = new V[n + 1];
                R[i] = new Comparable[n + 1];
            }

            for (auto i = 0; i <= n; ++i)
                for (auto j = 0; j <= n; j++) {
                    R[i][j] = 0;
                }
            //Construct weight matrix W
            for (auto i = 0; i <= n; ++i) {
                W[i][i] = 0;
                for (auto j = i + 1; j <= n; j++) {
                    W[i][j] = W[i][j - 1] + p[j] + 0;
                }
            }

            //Construct cost matrix C and root matrix R
            for (auto i = 0; i <= n; ++i)
                C[i][i] = W[i][i];
            for (auto i = 0; i <= n - 1; ++i) {
                C[i][i + 1] = C[i][i] + C[i + 1][i + 1] + W[i][i + 1];
                R[i][i + 1] = i + 1;
            }

            V j, min, x;
            Comparable m;
            for (auto h = 2; h <= n; h++)
                for (auto i = 0; i <= n - h; i++) {
                    j = i + h;
                    m = R[i][j - 1];
                    min = C[i][m - 1] + C[m][j];
                    for (auto k = m + 1; k <= R[i + 1][j]; k++) {
                        x = C[i][k - 1] + C[k][j];
                        if (x < min) {
                            m = k;
                            min = x;
                        }
                    }
                    C[i][j] = W[i][j] + min;
                    R[i][j] = m;
                }

/*
            //Display weight matrix W
            printf("\nThe weight matrix W:\n");
            for (auto i = 0; i <= n; ++i) {
                for (auto j = i; j <= n; ++j)
                    printf("%d ", W[i][j]);
                printf("\n");
            }

            //Display Cost matrix C
            printf("\nThe cost matrix C:\n");
            for (auto i = 0; i <= n; i++) {
                for (auto j = i; j <= n; j++)
                    printf("%d ", C[i][j]);
                printf("\n");
            }

            //Display Root matrix
            printf("\nThe root matrix R:\n");
            for (auto i = 0; i <= n; ++i) {
                for (auto j = i; j <= n; ++j)
                    printf("%d ", R[i][j]);
                printf("\n");
            }

            auto average_cost_per_weight = C[0][n] / (float) W[0][n];
            printf("The cost per weight ratio is: %f\n", average_cost_per_weight);

            printf("C[0] = %d W[0] = %d\n", C[0][n], W[0][n]);
*/
            this->average_weight = W[0][n];
            this->cost = C[0][n];
            root = CONSTRUCT_OBST(0, n, R, kkeys, p);

            for (auto i = 0; i <= n; ++i) {
                delete[] C[i];
                delete[] W[i];
                delete[] R[i];
            }
            delete[] C;
            delete[] W;
            delete[] R;
        }
    }



    void remove(const Comparable &x, BinaryNode *&t) {
        if (t == nullptr)
            return;        // Item not found; do nothing
        if (x < t->element.first)
            remove(x, t->left);
        else if (t->element.first < x)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) // Two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element.first, t->right);
        } else {
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }

    }

    BinaryNode *findMin(BinaryNode *t) const {
        if (t != nullptr)
            while (t->left != nullptr)
                t = t->left;
        return t;

    }

    BinaryNode *findMax(BinaryNode *t) const {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }

    bool contains(const Comparable &x, BinaryNode *t) const {
        if (t == nullptr)
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true;
    }

    void makeEmpty(BinaryNode *&t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }


    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr)
            return nullptr;
        else
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }


    //Display the optimal binary search tree
    void DISPLAY(BinaryNode *t, V nivel, std::ostream &out) const {
        if (t != nullptr) {
            DISPLAY(t->right, nivel + 1, out);
            for (auto i = 0; i <= nivel; ++i)
                out << "                       ";
            out << t->element.first << " level = " << nivel << std::endl;
            DISPLAY(t->left, nivel + 1, out);
        }
    }

};
