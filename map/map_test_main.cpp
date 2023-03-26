//
// Created by apple on 2023/3/26.
//
#include <map>
#include <iostream>
#include <string>
#include "util/comm.h"
using std::string;

int main(){
    std::map<int,string> kv{{1,"1"},{2,"2"},{3,"3"},{4,"4"},{5,"5"}};
    for(auto it : kv){
        std::cout << it.first << ":" << it.second<< "\n";
    }

    std::cout << "delete value:3 \n";
    auto iter = kv.begin();
    for(;iter != kv.end();){
       if(iter->second == "3") {
           kv.erase(iter++);
       }else{
           //++iter;
           iter++;
       }
    }
    util::print(kv);


    return 0;
}
