//
// Created by sergio on 18.11.2019.
//

#pragma once

#include <cstdlib>
#include <new>
#include <ostream>
#include <mutex>


namespace sergio {
/* Node of a doubly linked list */
    template<typename T>
    struct Node {
        T data;
        Node *next;
        Node *prev;
    };

    template<typename T>
    class LinkedList {
    private:
        Node<T> *head;
        std::mutex mutex;
    public:
        LinkedList() : head(nullptr) {};

        ~LinkedList() {
            std::lock_guard<std::mutex> lock(mutex);
            if (head != nullptr) {
                Node<T> *tmp = head->next;
                if (!tmp) free(head);
                while (tmp != nullptr) {
                    if (tmp->prev)
                        free(tmp->prev);
                    if (!tmp->next) {
                        if (tmp)
                            free(tmp);
                        break;
                    }
                    tmp = tmp->next;
                }
            }
        }

        void push_front(const T &new_data) {
            std::lock_guard<std::mutex> lock(mutex);
            struct Node<T> **head_ref = &head;
            struct Node<T> *new_node;
            new_node = create_Node(new_data);
            new_node->next = (*head_ref);
            new_node->prev = nullptr;
            if ((*head_ref) != nullptr)
                (*head_ref)->prev = new_node;
            (*head_ref) = new_node;
        }

        void insertAfter(Node<T> *prev_node, const T &new_data) {
            std::lock_guard<std::mutex> lock(mutex);
            if (prev_node == nullptr) {
                return;
            }
            struct Node<T> *new_node;
            new_node = create_Node(new_data);
            new_node->next = prev_node->next;
            new_node->prev = prev_node;
            prev_node->next = new_node;
            if (new_node->next != nullptr)
                new_node->next->prev = new_node;
        }

        void push_back(const T &new_data) {
            std::lock_guard<std::mutex> lock(mutex);
            struct Node<T> **head_ref = &head;
            struct Node<T> *new_node;
            new_node = create_Node(new_data);
            if (*head_ref == nullptr) {
                *head_ref = new_node;
                return;
            }
            Node<T> *last = *head_ref;
            while (last->next) {
                last = last->next;
            }
            last->next = new_node;
            new_node->prev = last;
            return;
        }

        std::size_t size() {
            std::lock_guard<std::mutex> lock(mutex);
            std::size_t count{0};
            Node<T> *tmp = head;
            while (tmp) {
                ++count;
                tmp = tmp->next;
            }
            return count;
        }

        void pop_front() {
            std::lock_guard<std::mutex> lock(mutex);
            if (!head) return;
            if (!head->next) {
                free(head);
                head = nullptr;
                return;
            }
            Node<T> *new_head = head->next;
            new_head->prev = nullptr;
            if (head)
                free(head);
            head = new_head;
        }

        T get_front_value() {
            if (!head) throw std::out_of_range("null size of linked list");
            return head->data;
        }

        friend std::ostream &operator<<(std::ostream &out, const LinkedList<T> &linkedList) {
            if (linkedList.head) {
                out << linkedList.head->data;
                if (linkedList.head->next)
                    out << " ";

                Node<T> *last = linkedList.head->next;
                while (last) {
                    out << last->data;
                    last = last->next;
                    if (last) out << " ";
                }
            }
            return out;
        }

        friend std::ostream &operator<<(std::ostream &out, const LinkedList<T> *linkedList) {
            if (linkedList->head) {
                out << linkedList->head->data;
                if (linkedList->head->next)
                    out << " ";

                Node<T> *last = linkedList->head->next;
                while (last) {
                    out << last->data;
                    last = last->next;
                    if (last) out << " ";
                }
            }
            return out;
        }

    private:
        Node<T> *create_Node(const T &new_data) {
            struct Node<T> *new_node;
            new_node = (struct Node<T> *) malloc(sizeof(struct Node<T>));
            if (!new_node) throw std::bad_alloc();
            new_node->prev = nullptr;
            new_node->next = nullptr;
            new_node->data = new_data;
            return new_node;
        }
    };

}

