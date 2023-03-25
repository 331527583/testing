//
// Created by apple on 2023/3/24.
//

#ifndef PANGUTEST_MULTI_BASE_H
#define PANGUTEST_MULTI_BASE_H

#include <string>
#include <iostream>

class  BaseA {
public:
    void print() const {
        std::cout << "BaseA" << "\n";
    }
public:
    const static int a;
};

class BaseB {
public:
    BaseB():a(20){}
public:
    const int a;
};

class SubC : public BaseA,public BaseB {
public:
    void print() const {
        std::cout << a << "\n";
    }

private:
    int a;
};
class multi_base {

};


#endif //PANGUTEST_MULTI_BASE_H
