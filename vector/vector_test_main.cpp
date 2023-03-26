//
// Created by apple on 2023/3/26.
//
#include "util/base.h"
#include "util/comm.h"


int main(){
    std::cout << "vector print testing.\n";
    std::vector<int> vec;
    vec.reserve(10);
    std::cout << "vec initializer size(10) and capacity(10) " << vec.size() << " " <<vec.capacity() << endl;
    std::cout << "vector erase then gc the memory testing.\n";
    for(int i=0;i<10;i++){
       vec.push_back(i);
    }
    std::cout << "vector delete the last 9 items\n";
    vec.erase(vec.begin()+1,vec.end());
    vec.push_back(9999);
    std::cout << "vec size(2) and capacity(10) " << vec.size() << " " << vec.capacity() << endl;
    util::print(vec);

    std::cout << "===================testing get back vector memory ===============\n";
    vector<int> vec2(1000,9);
    util::print(vec2);
    vector<int> vec3;
    vec3.swap(vec2);
    std::cout << "swap vector with an empty vector,then vec2 size(0) and capacity(0) " << vec2.size() << " " << vec2.capacity()<<endl;


    return 0;
}
