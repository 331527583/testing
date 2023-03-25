//
// Created by apple on 2023/3/23.
//

#include "registerer.h"
namespace registerer{
    BaseClassMap& global_factory_map()  {
        static BaseClassMap * baseClassMap = new BaseClassMap();
        return *baseClassMap;
    }
}