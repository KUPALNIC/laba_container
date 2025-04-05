#include <iostream>
using namespace std;

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

    void show_parameters() {
        cout << "Parameters:" << endl;
        cout << "top: " << top << endl;
        cout << "capacity: " << capacity << endl;
    }

    class iterator {
    private:
        int* ptr;
    public:
        iterator(int* p) : ptr(p) {}
        
        int& operator*() { return *ptr; }
        iterator& operator++() { ptr++; return *this; }
        iterator operator++(int) { iterator temp = *this; ++(*this); return temp; }
        bool operator!=(const iterator& t) const { return ptr != t.ptr; }
    };

    iterator begin() { return iterator(mas); }
    iterator end() { return iterator(mas + top); }
};

int main() {
    subvector sv;
    for (int i = 0; i < 5; i++) {
        sv.push_back(i + 1);
    }

    cout << "Elements in subvector using iterator: ";
    for (auto it = sv.begin(); it != sv.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "pop_back: " << sv.pop_back() << endl;
    cout << "Testing resize()" << endl;
    sv.resize(5);
    sv.show_parameters();
    cout << "Testing shrink_to_fit()" << endl;
    sv.shrink_to_fit();
    sv.show_parameters();
    return 0;
}
