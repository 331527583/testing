//
// Created by apple on 2023/3/25.
//
#include <vector>
#include <iostream>
using std::cout;
using std::endl;

int main(){
    std::vector<int> vec{1,2,3,4,5,6,7};

    std::cout << "初始vector大小（size）和容量(capacity)分别是：" << vec.size() << " " << vec.capacity() << endl;
    if(vec.size() != 7 )
        std::cout << "expect size is 7 ,but actual size is " << vec.size() << "\n";
    if(vec.capacity() != 7 )
        std::cout << "capacity is not 7" << endl;

    vec.resize(10);
    std::cout << "(scale-out)vector大小（size）和容量(capacity)分别是：" << vec.size() << " " << vec.capacity() << endl;
    if(vec.size() != 10 || vec.capacity() != 10){
        std::cout << "expect2 error" << std::endl;
    }
    vec.resize(7);
    std::cout << "(scale-out)vector大小（size）和容量(capacity)分别是：" << vec.size() << " " << vec.capacity() << endl;
    if(vec.size() != 7 || vec.capacity() <= 7)
        std::cout << "expect3 error" << std::endl;
    std::cout << "shrink vector memory testing=========================\n";
    vec.clear();
    std::cout << "clear vector .And new size(0) and capacity(>7) is " << vec.size() << " " << vec.capacity() << endl;
    vec.shrink_to_fit();
    std::cout << "shrink vector .And new size(0) and capacity(0) is " << vec.size() << " " << vec.capacity() << endl;

    return 0;
}