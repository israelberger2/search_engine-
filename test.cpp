#include <iostream>

class A {
public:
    A(int value) : data(value) {
        // Additional initialization for class A, if needed
    }

    void print() const {
        std::cout << "A's data: " << data << std::endl;
    }

private:
    int data;
};

class B {
public:
    B(A& aValue) : a(aValue) {
        // Additional initialization for class B, if needed
    }

    void print() {
        std::cout << "B contains:" ;
        a.print();
    }

private:
    A a;
};

class C {
public:
    C(int aValue) : a(aValue) {
        // Additional initialization for class B, if needed
    }

    void print() const {
        std::cout << "c contains:" << std::endl;
        a.print();
    }

private:
    A a;
};

int main() {
    A a(2);
    B b(a);
    b.print();
    C c(4);
    c.print();
    return 0;
}
