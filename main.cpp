#include <iostream>
#include <typeinfo>
#include "registerer.h"
#include "multi_base.h"
#include "size_of_empty_class.h"
#include "vector_test.h"
using std::cout;
using std::endl;

namespace base {
    class Base {
    public:
        virtual int Foo() { return 0; }
        virtual ~Base() {
           cout << "Destruct Base\n"; }
    };
    REGISTER_REGISTERER(Base);

#define REGISTER_BASE(name) REGISTER_CLASS(Base, name)
}  // namespace base

namespace sub1 {
    class Sub1 : public base::Base {
    public:
        Sub1() {
            cout << "Sub1\n";
        }
        virtual ~Sub1() {
            cout << "Destruct Sub1\n"; }
        virtual int Foo() { return 1; }
    };
    REGISTER_BASE(Sub1);
}  // namespace sub1

int main() {
    std::cout << "Hello, World!" << std::endl;
    base::Base * base = base::BaseRegister::GetInstanceByName("Sub1");
    if(base ==NULL){
        cout << "base is NULL\n";
    }else{
        cout << static_cast<void*>(base);
    }
    if(1 == base->Foo()){
        cout << "base::Foo is " << base->Foo();
    }
    delete base;

    /*
    std::cout << "multi base test" << std::endl;
    SubC c;
    c.print();

    std::cout << "sizeof empty class " << std::endl;
    std::cout << SIZEOF_EMPTY_CLASS(size_of_empty_class) <<"\n";

    std::cout << std::endl;
    const std::type_info &i= typeid(size_of_empty_class);
    std::cout << i.name() << std::endl;
     */
    //vector_test::vector_resize();
    vector_test::delete_test();

    return 0;
}