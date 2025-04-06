#ifndef SUBVECTOR_H
#define SUBVECTOR_H

#include <iostream>

class subvector {
protected:
    int* mas;
    unsigned int top;
    unsigned int capacity;

public:
    subvector() : mas(nullptr), top(0), capacity(0) {}

    ~subvector() {
        delete[] mas;
        mas = nullptr;
        top = 0;
        capacity = 0;
    }
    int size(){
      return top;
    }
    int capasity(){
      return capacity;
    }

    void push_back(int n) {
        if (capacity == 0) {
            capacity = 1;
            mas = new int[1];
        }
        if (top == capacity) {
            int* new_mas = new int[2 * capacity];
            for (unsigned int i = 0; i < top; i++) {
                new_mas[i] = mas[i];
            }
            delete[] mas;
            mas = new_mas;
            capacity *= 2;
        }
        mas[top++] = n;
    }

    int pop_back() {
        return (top == 0) ? 0 : mas[--top];
    }

    void resize(unsigned int new_capacity) {
        if (new_capacity < top) {
            top = new_capacity;
        }
        capacity = new_capacity;
        int* new_mas = new int[capacity];
        for (unsigned int i = 0; i < top; i++) {
            new_mas[i] = mas[i];
        }
        delete[] mas;
        mas = new_mas;
    }

    void clear() {
        top = 0;
    }

    void shrink_to_fit() {
        if (capacity > top) {
            resize(top);
        }
    }

    class iterator {
    public:
        int* ptr;
        iterator(int* p) : ptr(p) {}
        
        int& operator*() { return *ptr; }
        iterator& operator++() { ptr++; return *this; }
        iterator operator++(int) { iterator temp = *this; ++(*this); return temp; }
        bool operator!=(const iterator& t) const { return ptr != t.ptr; }
        iterator operator+(unsigned int n) const { return iterator(ptr + n); }
    };

    iterator begin() { return iterator(mas); }
    iterator end() { return iterator(mas + top); }

    void insert(iterator pos, int n) {
        unsigned int index = pos.ptr - mas;
        if (top == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        for (unsigned int i = top; i > index; --i) {
            mas[i] = mas[i - 1];
        }
        mas[index] = n;
        ++top;
    }

    void erase(iterator pos) {
        unsigned int index = pos.ptr - mas;
        for (unsigned int i = index; i < top - 1; ++i) {
            mas[i] = mas[i + 1];
        }
        --top;
    }
};

#endif // SUBVECTOR_H