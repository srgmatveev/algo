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
        Node *next{nullptr};
        Node *prev{nullptr};
    };

    template<typename T, typename U>
    class LinkedList {
    private:
        Node<T> *head ;
        U priority;
    public:
        LinkedList() : head(nullptr), priority(0) {};

        LinkedList(U priority) : head(nullptr), priority(priority) {};

        ~LinkedList() {
            return;
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
            struct Node<T> *new_node;
            new_node = create_Node(new_data);
            struct Node<T> **head_ref = &head;
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

        void insertAfter(Node<T> *prev_node, const T &new_data) {
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
            struct Node<T> **head_ref = &head;
            struct Node<T> *new_node;
            new_node = create_Node(new_data);
            if (*head_ref == nullptr) {
                *head_ref = new_node;
                if (new_node->next == new_node->prev && new_node->next == new_node) {
                    new_node->next = nullptr;
                    new_node->prev = nullptr;
                }
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

        std::size_t size() const {
            std::size_t count{0};
            Node<T> *tmp = head;
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
            Node<T> *new_head = head->next;
            new_head->prev = nullptr;
            if (head)
                free(head);
            head = new_head;
        }

        void clear() {
            if (!head) return;
            Node<T> *cur_node = head;
            Node<T> *tmp_node = nullptr;
            while (cur_node) {
                if (cur_node->next != nullptr) {
                    tmp_node = cur_node;
                    cur_node = cur_node->next;
                    if(tmp_node)
                        free(tmp_node);
                } else {
                    free(cur_node);
                    break;
                }
            }
        }

        bool not_empty() const {
            return head ? true : false;
        }

        bool empty() const {
            return !this->non_empty();
        }

        T *top() {
            if (!head) return nullptr;
            return &head->data;
        }

        U &get_priority() {
            return priority;
        }

        void set_priority(U priority) {
            this->priority = priority;
        }

        friend std::ostream &operator<<(std::ostream &out, const LinkedList<T, U> &linkedList) {
            out << "priority = " << linkedList.priority;
            if (linkedList.not_empty()) out << ",";
            if (linkedList.head) {
                out << " list = {";
                out << linkedList.head->data;
                if (linkedList.head->next)
                    out << ", ";

                Node<T> *last = linkedList.head->next;
                while (last) {
                    out << last->data;
                    last = last->next;
                    if (last) out << ", ";
                }
                out << "}";
            }
            return out;
        }

        friend std::ostream &operator<<(std::ostream &out, const LinkedList<T, U> *linkedList) {
            out << "priority = " << linkedList->priority;
            if (linkedList->not_empty()) out << ",";
            if (linkedList->head) {
                out << " list = {";
                out << linkedList->head->data;
                if (linkedList->head->next)
                    out << ", ";

                Node<T> *last = linkedList->head->next;
                while (last) {
                    out << last->data;
                    last = last->next;
                    if (last) out << ", ";
                }
                out << "}";
            }
            return out;
        }


        LinkedList<T, U> &operator=(LinkedList &right) {

            if (this == &right) {
                return *this;
            }
            head = right.head;
            priority = right.priority;
            right.head = nullptr;
            return *this;
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

