//
// Created by apple on 2023/3/26.
//

#include <list>
#include <iostream>
using std::list;
using std::cout;
using std::endl;

template <typename Container>
static void print(Container container);

int main(){
    list<int> lst{1,2,3,4,5};
    std::cout << "push_back : 6\n";
    lst.push_back(6);
    auto lastElem = lst.back();
    std::cout << "back() called ,and item value is " << lastElem << "\n";
    lst.pop_back();

    std::cout << "push_front testing :\n";
    lst.push_front(7);
    if(lst.front() != 7 ){
        std::cerr << "lst.front() is not 7 " << std::endl;
    }
    auto len = lst.size();
    std::cout << "pop_front testing :\n";
    lst.pop_front();
    if(lst.size() != (len - 1)){
      std::cerr << "lst.size() is not 5\n";
    }

    list<int> lst2{3,3,1,7,9,4,4,3,5,2,0};
    std::cout << "unique the continue same value" << std::endl;
    lst2.unique();
    std::cout << "print list content after unique\n";
    print(lst2);

    std::cout << "sort list item,then print them\n";
    lst2.sort();
    std::cout << "sort list and then print.\n";
    print(lst2);
    lst2.unique();
    print(lst2);

    std::cout << "erase list value and then print the list.\n";
    list<int>::iterator iter = lst2.begin();
    for(;iter != lst2.end();){
       if(*iter == 3){
           iter= lst2.erase(iter);
       }else{
           std::cout << *iter << " ";
           iter++;
       }
    }
    std::cout << std::endl;
    print(lst2);



    return 0;
}
template<typename Container>
static void print(Container container)  {
    for(const auto & item : container) {
       std::cout << item << " ";
    }
    std::cout << std::endl;
}