//
// Created by sergio on 11.12.2019.
//
#pragma once

template<typename T>
struct item {
    T key, prior;
    item *l, *r;

    item() {}

    item(const T &key, const T &prior) : key(key), prior(prior), l(NULL), r(NULL) {}

    item(T &&key, T &&prior) : key(key), prior(prior), l(NULL), r(NULL) {}
};

template<typename T>
class Treap {
private:
    item<T> *head;

    void split_r(item<T> *t, T key, item<T> *&l, item<T> *&r) {
        if (!t)
            l = r = NULL;
        else if (key < t->key) {
            split_r(t->l, key, l, t->l);
            r = t;
        } else {
            split_r(t->r, key, t->r, r);
            l = t;
        }
    }

    void merge_r(item<T> *&t, item<T> *l, item<T> *r) {
        if (!l || !r) {
            if (t && !l && !r) delete t;
            t = l ? l : r;
        } else if (l->prior > r->prior)
            merge_r(l->r, l->r, r), t = l;
        else
            merge_r(r->l, l, r->l), t = r;
    }

    void insert_r(item<T> *&t, item<T> *it) {
        if (!t) {
            t = it;
        } else if (it->prior > t->prior) {
            split_r(t, it->key, it->l, it->r);
            t = it;
        } else
            insert_r(it->key < t->key ? t->l : t->r, it);
    }


    void erase_p(item<T> *&t, T key) {
        if(!t) return;
        if (t->key == key)
            merge_r(t, t->l, t->r);
        else
            erase_p(key < t->key ? t->l : t->r, key);
    }

public:
    Treap() : head(nullptr) {};

    Treap(item<T> &head) : head(head) {};

    Treap(const T &key, const T &pair) {
        head = new item<T>(key, pair);
    }

    Treap(T &&key, T &&pair) {
        head = new item<T>(std::move(key), std::move(pair));
    }

    T *get_key() {
        if (!head) return nullptr;
        return &head->key;
    }

    T *get_prior() {
        if (!head) return nullptr;
        return &head->prior;
    }

    void insert(const T &key, const T &pair) {
        item<T> *it = new item(key, pair);
        this->insert_r(this->head, it);
    }

    void merge(item<T> *l, item<T> *r) {
        merge_r(this->head, l, r);
    }

    void erase(T key) {
        erase_p(this->head, key);
    }

    void clear() {
        while (head) {
            item<T> *tmp = head;
            erase_p(this->head, this->head->key);
            if (head) delete tmp;
        }
    }

    ~Treap() {
        clear();
    }
};

