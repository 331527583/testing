//
// Created by apple on 2023/3/25.
//

#ifndef PANGUTEST_VECTOR_TEST_H
#define PANGUTEST_VECTOR_TEST_H

#include <vector>
#include <iostream>

using std::vector;

class vector_test {
public:
    static std::vector<int> vec;
    static void vector_resize(){
        std::vector<int> vec(2,9);
        vec.push_back(1);
        vec.push_back(2);

        std::cout << "vector initializer size: " << vec.size() << "\n";
        std::cout << "vector initializer capacity: " << vec.capacity() << "\n";
        for( int i: vec){
            std::cout << i << " ";
        }
        std::cout << std::endl;
        vec.resize(2,10);
        std::cout << "new size:" << vec.size() << std::endl;
        std::cout << "new capacity:" << vec.capacity() << std::endl;


        vec.resize(5,10);
        std::cout << "new size:" << vec.size() << std::endl;
        std::cout << "new capacity:" << vec.capacity() << std::endl;

        vec.reserve(4);
        std::cout << "new size:" << vec.size() << std::endl; // 4-error
        std::cout << "new capacity:" << vec.capacity() << std::endl; // 4-error

        vec.resize(4);
        std::cout << "new size:" << vec.size() << std::endl; // 4
        std::cout << "new capacity:" << vec.capacity() << std::endl; // 4-error

        vec.reserve(2);
        std::cout << "new size:" << vec.size() << std::endl; // 4
        std::cout << "new capacity:" << vec.capacity() << std::endl; // 4-error
    }

    static void delete_test(){
        std::vector<int>::iterator it= vec.erase(vec.begin());
        for (;it != vec.end();it++){
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
};


#endif //PANGUTEST_VECTOR_TEST_H
