//
// Created by apple on 2023/3/26.
//

#ifndef TESTING_COMM_H
#define TESTING_COMM_H
#include <string>
#include <iostream>
#include <map>
namespace util{
    template<typename Container>
    static void print(Container container)  {
        for(const auto & item : container) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    void print(std::map<int,std::string> & m){
        for(auto it : m){
            std::cout << it.first << ":" << it.second<< "\n";
        }
    }

}
#endif //TESTING_COMM_H
