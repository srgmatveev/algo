//
// Created by sergio on 24.11.2019.
//

#pragma once

#include "base_array.h"

template<class T, class X>
class Node {
public:
    BaseArray<T, X> *data;
    Node *next;
    Node *prev;
    ~Node(){
        if(data) delete(data);
    }
};

template<typename T, typename X>
class List_Array {
private:
    Node<T, X> *head;
    X full_size_base_array;

    Node<T, X> *create_Node(const BaseArray<T, X> &new_data) {
        struct Node<T, X> *new_node;
        new_node = new Node<T, X>();
        if (!new_node) throw std::bad_alloc();
        new_node->prev = nullptr;
        new_node->next = nullptr;
        new_node->data = const_cast<BaseArray<T, X> *>(&new_data);
        return new_node;
    }

public:
    List_Array() : head(nullptr) {}

    ~List_Array() {
        if (head != nullptr) {
            Node<T, X> *tmp = head->next;
            if (!tmp) delete (head);
            while (tmp != nullptr) {
                if (tmp->prev)
                    delete (tmp->prev);
                if (!tmp->next) {
                    if (tmp)
                        delete(tmp);
                    break;
                }
                tmp = tmp->next;
            }
        }
    }

    void at(const X &index, const T &data) {
        node<T> *node1 = new node<T>(data);
        if (!head) {
            BaseArray<T, X> *baseArray = new BaseArray<T, X>(3);
            baseArray->push_back(node1);
            push_front(*baseArray);
            return;
        }
        Node<T, X> *tmp = head;
        X cur = 0;
        X tmp_size = 0;
        while (tmp) {
            tmp_size = tmp->data->get_size();
            if (cur + tmp_size >= index) {
                node<T> *tmp_node = tmp->data->insert_before(node1, index - cur -1);
                if (tmp_node) {
                    BaseArray<T, X> *baseArray = new BaseArray<T, X>(3);
                    baseArray->push_back(tmp_node);
                    insertAfter(tmp, *baseArray);
                }
                break;
            } else {
                cur += tmp_size;
                if (!tmp->next) {
                    BaseArray<T, X> *baseArray = new BaseArray<T, X>(3);
                    if (cur + tmp_size >= index) {
                        baseArray->push_back(node1);
                        push_back(*baseArray);
                        break;
                    }
                    push_back(*baseArray);
                }
            }
            tmp = tmp->next;
        }
    }

    void push_front(const BaseArray<T, X> &data) {
        struct Node<T, X> *new_node = create_Node(data);
        struct Node<T, X> **head_ref = &head;
        new_node->next = (*head_ref);
        new_node->prev = nullptr;
        if ((*head_ref) != nullptr)
            (*head_ref)->prev = new_node;
        (*head_ref) = new_node;
        if (new_node && new_node->next == new_node->prev && new_node->next == new_node) {
            new_node->next = nullptr;
            new_node->prev = nullptr;
        }
    }

    void insertAfter(Node<T, X> *prev_node, const BaseArray<T, X> &data) {
        if (prev_node == nullptr) {
            return;
        }
        struct Node<T, X> *new_node;
        new_node = create_Node(data);
        new_node->next = prev_node->next;
        new_node->prev = prev_node;
        prev_node->next = new_node;
        if (new_node->next != nullptr)
            new_node->next->prev = new_node;
    }

    void push_back(const BaseArray<T, X> &data) {
        struct Node<T, X> **head_ref = &head;
        struct Node<T, X> *new_node;
        new_node = create_Node(data);
        if (*head_ref == nullptr) {
            *head_ref = new_node;
            if (new_node->next == new_node->prev && new_node->next == new_node) {
                new_node->next = nullptr;
                new_node->prev = nullptr;
            }
            return;
        }
        Node<T, X> *last = *head_ref;
        while (last->next) {
            last = last->next;
        }
        last->next = new_node;
        new_node->prev = last;
        return;
    }

    std::size_t size() const {
        std::size_t count{0};
        Node<T, X> *tmp = head;
        while (tmp) {
            ++count;
            tmp = tmp->next;
        }
        return count;
    }

    void pop_front() {
        if (!head) return;
        if (!head->next) {
            free(head);
            head = nullptr;
            return;
        }
        Node<T, X> *new_head = head->next;
        new_head->prev = nullptr;
        if (head)
            delete (head);
        head = new_head;
    }

    bool not_empty() const {
        return head ? true : false;
    }

    bool empty() const {
        return !this->not_empty();
    }

};
