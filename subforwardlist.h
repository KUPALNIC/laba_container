#ifndef SUBFORWARDLIST_H
#define SUBFORWARDLIST_H

#include <iostream>

class Subforwardlist {
private:
    struct Node {
        int data;
        Node* next;
    };

    Node* head;

public:
    Subforwardlist() : head(nullptr) {}

    ~Subforwardlist() {
        clear();
    }

    void push_back(int d) {
        Node* new_node = new Node{d, nullptr};
        if (!head) {
            head = new_node;
        } else {
            Node* tmp = head;
            while (tmp->next) {
                tmp = tmp->next;
            }
            tmp->next = new_node;
        }
    }

    int pop_back() {
        if (!head) return 0;
        if (!head->next) {
            int data = head->data;
            delete head;
            head = nullptr;
            return data;
        }
        Node* tmp = head;
        while (tmp->next->next) {
            tmp = tmp->next;
        }
        int data = tmp->next->data;
        delete tmp->next;
        tmp->next = nullptr;
        return data;
    }

    void push_front(int d) {
        Node* new_node = new Node{d, head};
        head = new_node;
    }

    int pop_front() {
        if (!head) return 0;
        Node* tmp = head;
        int data = tmp->data;
        head = head->next;
        delete tmp;
        return data;
    }

    unsigned int size() const {
        unsigned int count = 0;
        Node* tmp = head;
        while (tmp) {
            ++count;
            tmp = tmp->next;
        }
        return count;
    }

    bool insert(unsigned int pos, int d) {
        if (pos == 0) {
            push_front(d);
            return true;
        }
        Node* new_node = new Node{d, nullptr};
        Node* tmp = head;
        for (unsigned int i = 1; i < pos; ++i) {
            if (!tmp) {
                std::cerr << "Error: position out of bounds" << std::endl;
                delete new_node;
                return false;
            }
            tmp = tmp->next;
        }
        new_node->next = tmp->next;
        tmp->next = new_node;
        return true;
    }

    int erase(unsigned int pos) {
        if (!head) return 0;
        if (pos == 0) {
            return pop_front();
        }
        Node* tmp = head;
        for (unsigned int i = 1; i < pos; ++i) {
            if (!tmp->next) {
                std::cerr << "Error: position out of bounds" << std::endl;
                return 0;
            }
            tmp = tmp->next;
        }
        if (!tmp->next) {
            std::cerr << "Error: position out of bounds" << std::endl;
            return 0;
        }
        int data = tmp->next->data;
        Node* to_delete = tmp->next;
        tmp->next = tmp->next->next;
        delete to_delete;
        return data;
    }

    void clear() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};

#endif // SUBFORWARDLIST_H