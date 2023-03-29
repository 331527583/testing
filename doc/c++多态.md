C++多态
 

 关于多态，简而言之就是用父类型别的指针指向其子类的实例，然后通过父类的指针调用实际子类的成员函数。这种技术可以让父类的指针有“多种形态”，这是一种泛型技术。

 

多态
函数重载(overload)
相同的作用域（在同一个类中）；
函数名字相同、参数（类型或个数）不同；
virtual关键字可有可无；
 

 

隐藏(hide)
隐藏是指派生类的函数屏蔽了与其同名的基类函数，有2种情况：

派生类有和基类同名的函数，但参数不同，基类函数无论有无virtual关键字，基类的函数将被隐藏；
派生类有和基类同名的函数，且参数相同，如果基类函数无virtual关键字，基类的函数将被隐藏；
 

覆盖(override)
派生类有和基类同名的函数，且参数相同，如果基类函数有virtual关键字，基类的函数将被覆盖；
 

说明：

重载比较容易理解，是在同一个类中声明的多个同名函数，而隐藏和覆盖都是在派生类中声明了与基类同名的函数，这种情况下不是隐藏就是覆盖，两者最大区别是：

覆盖是动态绑定（主要通过虚函数），隐藏是静态绑定。

 

看个例子：

复制代码
class Base {
    public:
        void f(int p) { cout << "Base::f(int)" << endl; }
        void f(float p) { cout << "Base::f(float)" << endl; }
        virtual void g() { cout << "Base::g()" << endl; }
};

class Derived: public Base {
    public:
        void f(int p) { cout << "Derived::f(int)" << endl; }
        virtual void f(float p) { cout << "Derived::f(float)" << endl; }
        void g() { cout << "Derived::g()" << endl; }
};

int main(int argc, char** argv) {
    Derived d;

    Base *pb = &d;
    pb->f(3);       // Base::f(int)
    pb->f(3.14f);   // Base::f(float)
    pb->g();        // Derived::g()

    Derived *pd = &d; 
    pd->f(3);       // Derived::f(int)
    pd->f(3.14f);   // Derived::f(float)
    pd->g();        // Derived::g()


    return 0;
}
复制代码
如上面的代码，Base::f(int)与Base::f(float) 就是函数重载；Derived::g()对Base::g()就是函数覆盖；

而隐藏是指当用基类的指针pb调用函数f()，总是调用到基类的版本，用派生类的指针pd调用函数f()，总是调用到派生类的版本，虽然它们指向同一个对象d。

上面的例子中，pb指针的静态类型是Base*，动态类型是Derived*，而pd的静态、动态类型都是Derived* ，也就是指针pb的静态类型和动态类型不一致，这也是动态绑定的基础。

 

看一个特殊的虚函数——虚析构函数：

复制代码
class A { 
    public:
    A() {cout <<"A()"<< endl;};
    A(int x) {cout<<"A(int)"<<endl;}
    virtual ~A() {cout << "~A()" << endl;}
    private:
    char d;
};

class B : public A{
    public:
    B() {cout <<"B()"<< endl;};
    B(int x) {cout<<"B(int)"<<endl;}
    ~B() {cout << "~B()" << endl;}
};

int main() {
　　A* pb = new B(3);
　　delete pb;
}
复制代码
输出结果为：

A()
B(int)
~B()
~A()
这里先后调用了子类、父类的析构函数。如果把父类析构函数的virtual关键字去掉，删除基类指针指向的派生类对象时就不会触发动态绑定，将只调用父类析构函数，而不会调用派生类的析构函数。

另外，这里调用的父类构造函数是无参数版本，如果想让父类构造函数也是带参数版本，可以这样做：

复制代码
class A {
    public:
    A() {cout <<"A()"<< endl;};
    A(int x) {cout<<"A(int)"<<endl;}
    virtual ~A() {cout << "~A()" << endl;}
    private:
    char d;
};

class B : public A{
    public:
    B() {cout <<"B()"<< endl;};
    B(int x):A(x) {cout<<"B(int)"<<endl;}
    ~B() {cout << "~B()" << endl;}
};
复制代码
此时输出结果为

A(int)
B(int)
~B()
~A()
 

 

 

 

 

虚函数（Virtual Function）
虚函数的特征：
基类通常应将派生类需要重定义的成员函数声明为虚函数；
除了构造函数之外，任意的非static成员函数都可以是虚函数；
一旦函数在基类中声明为虚函数，它就一直为虚函数，派生类无法改变该函数为虚函数这一事实。派生类重定义虚函数时，可以使用virtual关键字，但不是必须这样做；
基类指针（或引用）可以指向派生类对象；派生类指针（或引用）不能指向基类对象；
通过基类指针（或引用）调用非虚函数时，则无论实际对象是什么类型，都执行基类类型所定义的函数。
通过基类指针（或引用）调用虚函数时，编译器将在运行时确定调用哪个函数，被调用的是与动态类型相对应的函数。
派生类中虚函数的声明必须与基类中的定义方式完全匹配，有一个例外：返回对基类指针（或引用）的虚函数，派生类中的虚函数可以返回派生类的指针（或引用）。
可以使用作用域操作符覆盖虚函数机制，例如：
Item_base *baseP = &derived;
double c = baseP->net_price(42);     // 调用派生类中的版本
double d = baseP->Item_base::net_price(42);     // 调用基类中的版本
 

 
虚函数表（Virtual Table）
虚函数表（VT） 是一个类的虚函数的地址表，这张表解决了继承、覆盖的问题。这样，在有虚函数的类的实例中这个表被分配在了这个实例的内存中，所以，当我们用父类的指针来操作一个子类的时候，这张虚函数表就显得由为重要了，它就像一个地图一样，指明了实际所应该调用的函数。
C++的编译器应该是保证虚函数表的指针存在于对象实例中最前面的位置（这是为了保证取到虚函数表的有最高的性能——如果有多层继承或是多重继承的情况下）。 这意味着我们通过对象实例的地址得到这张虚函数表，然后就可以遍历其中函数指针，并调用相应的函数。
 
单继承 
看个例子：
复制代码
class Base {
    public:
        virtual void f() { cout << "Base::f" << endl; }
        virtual void g() { cout << "Base::g" << endl; }
        virtual void h() { cout << "Base::h" << endl; }
};

typedef void(*Fun)(void);
int main(int argc, char** argv) {
    Base b;
    long* pvt = (long*) (&b);       // 虚函数表地址

    long* pfun1 = (long*)(*pvt);    // 第一个虚函数

    for (int i = 0; i < 3; i++) {
        Fun fun = (Fun)(*(pfun1 + i));
        fun();
    }   

    return 0;
}
复制代码
运行结果：

Base::f
Base::g
Base::h
 

对象内存布局：



在上面这个图中，我在虚函数表的最后多加了一个结点，这是虚函数表的结束结点，就像字符串的结束符“/0”一样，其标志了虚函数表的结束。这个结束标志的值在不同的编译器下是不同的。

 

 

 然后看下有继承的时候，派生类对象的虚函数表是怎样的：
复制代码
class Base {
    public:
        virtual void f() { cout << "Base::f" << endl; }
        virtual void g() { cout << "Base::g" << endl; }
        virtual void h() { cout << "Base::h" << endl; }
};

class Derived: public Base {
    public:
        virtual void f1() { cout << "Derived::f1" << endl; }
        virtual void g1() { cout << "Derived::g1" << endl; }
        void h1() { cout << "Derived::h1" << endl; }
};

typedef void(*Fun)(void);
int main(int argc, char** argv) {
    Base b;
    Derived d;

    long* pvt = (long*) (&d);       // 虚函数表地址
    long* pfun1 = (long*)(*pvt);    // 第一个虚函数

    for (int i = 0; i < 5; i++) {
        Fun fun = (Fun)(*(pfun1 + i));
        fun();
    }

    return 0;
}
复制代码
运行结果：

Base::f
Base::g
Base::h
Derived::f1
Derived::g1
 

上面的派生类没有覆盖，再看下有覆盖的场景：

复制代码
class Base {
    public:
        virtual void f() { cout << "Base::f" << endl; }
        virtual void g() { cout << "Base::g" << endl; }
        virtual void h() { cout << "Base::h" << endl; }
};

class Derived: public Base {
    public:
        virtual void f1() { cout << "Derived::f1" << endl; }
        virtual void g() { cout << "Derived::g" << endl; }
        void h1() { cout << "Derived::h1" << endl; }
};

typedef void(*Fun)(void);
int main(int argc, char** argv) {
    Base b;
    Derived d;

    long* pvt = (long*) (&d);       // 虚函数表地址
    long* pfun1 = (long*)(*pvt);    // 第一个虚函数

    for (int i = 0; i < 4; i++) {
        Fun fun = (Fun)(*(pfun1 + i));
        fun();
    }

    return 0;
}
复制代码
运行结果：

Base::f
Derived::g
Base::h
Derived::f1
可见，派生类的虚函数g()覆盖了原本基类g()函数的位置，此时对下面的代码

 Base *pb = (Base*)&d;
 pb->g();
输出结果为

Derived::g
由pb所指的内存中的虚函数表的g()的位置已经被Derived::g()函数地址所取代，于是在实际调用发生时，是Derived::g()被调用了，这就实现了多态。

 
 
总结下就是： 
虚函数按照其声明顺序放于表中；
父类的虚函数在子类的虚函数前面；
如果子类的虚函数覆盖了父类，则该虚函数被放到了虚表中原来父类虚函数的位置。
 
 
 
 
 多继承
看个多继承的例子
复制代码
class Base1 {
    public:
        virtual void f() { cout << "Base1::f" << endl; }
        virtual void g() { cout << "Base1::g" << endl; }
        virtual void h() { cout << "Base1::h" << endl; }
};

class Base2 {
    public:
        virtual void f() { cout << "Base2::f" << endl; }
        virtual void g() { cout << "Base2::g" << endl; }
        virtual void h() { cout << "Base2::h" << endl; }
};

class Base3 {
    public:
        virtual void f() { cout << "Base3::f" << endl; }
        virtual void g() { cout << "Base3::g" << endl; }
        virtual void h() { cout << "Base3::h" << endl; }
};

class Derived: public Base1, Base2, Base3 {
    public:
        virtual void f1() { cout << "Derived::f1" << endl; }
        virtual void g1() { cout << "Derived::g1" << endl; }
};

typedef void(*Fun)(void);
int main(int argc, char** argv) {
    Derived d;

    long* pvt = (long*) (&d);           // 虚函数表地址
    long* pfun1 = (long*)(*pvt);        // Base1虚函数表
    long* pfun2 = (long*)(*(pvt+1));    // Base2虚函数表
    long* pfun3 = (long*)(*(pvt+2));    // Base3虚函数表

    cout<<"Base1 vt:"<<endl;
    for (int i = 0; i < 5; i++) {
        Fun fun = (Fun)(*(pfun1 + i));
        fun();
    }

    cout<<endl<<"Base2 vt:"<<endl;
    for (int i = 0; i < 3; i++) {
        Fun fun = (Fun)(*(pfun2 + i));
        fun();
    }

    cout<<endl<<"Base3 vt:"<<endl;
    for (int i = 0; i < 3; i++) {
        Fun fun = (Fun)(*(pfun3 + i));
        fun();
    }

    return 0;
}
复制代码
运行结果

复制代码
Base1 vt:
Base1::f
Base1::g
Base1::h
Derived::f1
Derived::g1

Base2 vt:
Base2::f
Base2::g
Base2::h

Base3 vt:
Base3::f
Base3::g
Base3::h
复制代码
 

对象内存布局



 
 
 
上面的例子没有覆盖，如果让派生类的g()覆盖基类同名虚函数：
复制代码
class Derived: public Base1, Base2, Base3 {
    public:
        virtual void f() { cout << "Derived::f" << endl; }
        virtual void g1() { cout << "Derived::g1" << endl; }
};

typedef void(*Fun)(void);
int main(int argc, char** argv) {
    Derived d;

    long* pvt = (long*) (&d);           // 虚函数表地址
    long* pfun1 = (long*)(*pvt);        // Base1虚函数表
    long* pfun2 = (long*)(*(pvt+1));    // Base2虚函数表
    long* pfun3 = (long*)(*(pvt+2));    // Base3虚函数表

    cout<<"Base1 vt:"<<endl;
    for (int i = 0; i < 4; i++) {
        Fun fun = (Fun)(*(pfun1 + i));
        fun();
    }

    cout<<endl<<"Base2 vt:"<<endl;
    for (int i = 0; i < 3; i++) {
        Fun fun = (Fun)(*(pfun2 + i));
        fun();
    }

    cout<<endl<<"Base3 vt:"<<endl;
    for (int i = 0; i < 3; i++) {
        Fun fun = (Fun)(*(pfun3 + i));
        fun();
    }

    return 0;
}
复制代码
运行结果

复制代码
Base1 vt:
Derived::f
Base1::g
Base1::h
Derived::g1

Base2 vt:
Derived::f
Base2::g
Base2::h

Base3 vt:
Derived::f
Base3::g
Base3::h
复制代码
 

对象内存布局



我们可以看见，三个父类虚函数表中的f()的位置被替换成了子类的函数指针。这样，我们就可以任一静态类型的父类来指向子类，并调用子类的f()了，例如：
复制代码
 Base1* pb1 = (Base1*)&d;
 pb1->f();   // Derived::f
 pb1->g();   // Base1::g

 Base2* pb2 = (Base2*)&d;
 pb2->f();   // Derived::f
 pb2->g();   // Base2::g

 Base3* pb3 = (Base3*)&d;
 pb3->f();   // Derived::f
 pb3->g();   // Base3::g
复制代码
 

总结下就是： 
每个父类都有自己的虚表；
子类的成员函数被放到了第一个父类的表中（所谓的第一个父类是按照声明顺序来判断的），这样做就是为了解决不同的父类类型的指针指向同一个子类实例，而能够调用到实际的函数；
 

最后，我们知道，子类没有重载父类的虚函数是一件毫无意义的事情。因为多态也是要基于函数重载的。虽然在上面的图中我们可以看到Base1的虚表中有Derive的虚函数g1()，但我们根本不可能使用下面的语句来调用子类的自有虚函数：

Base1* pb1 = (Base1*)&d;
pb1->g1();   // Error!
任何妄图使用父类指针想调用子类中的未覆盖父类的成员函数的行为都会被编译器视为非法，所以，这样的程序根本无法编译通过。但在运行时，我们可以通过指针的方式访问虚函数表来达到违反C++语义的行为（如上面代码例子）。

 

另外，如果父类的虚函数是private或是protected的，但这些非public的虚函数同样会存在于虚函数表中，所以，我们同样可以使用访问虚函数表的方式来访问这些non-public的虚函数，这是很容易做到的。

 

 
虚继承
在多继承中，很容易产生命名冲突，比如典型的是菱形继承，如下图所示：
 

 
类 A 派生出类 B 和类 C，类 D 继承自类 B 和类 C，这个时候类 A 中的成员变量和成员函数继承到类 D 中变成了两份，一份来自 A-->B-->D 这条路径，另一份来自 A-->C-->D 这条路径。 
例子：
复制代码
//间接基类A
class A{
protected:
    int m_a;
};
//直接基类B
class B: public A{
protected:
    int m_b;
};
//直接基类C
class C: public A{
protected:
    int m_c;
};
//派生类D
class D: public B, public C{
public:
    void seta(int a){ m_a = a; }  //命名冲突
    void setb(int b){ m_b = b; }  //正确
    void setc(int c){ m_c = c; }  //正确
    void setd(int d){ m_d = d; }  //正确
private:
    int m_d;
};
int main(){
    D d;
    return 0;
}
复制代码
如上代码，在class D中访问m_a时会出错，因为类 B 和类 C 中都有成员变量 m_a（从 A 类继承而来），编译器不知道选用哪一个，所以产生了歧义。

为了消除歧义，我们可以在 m_a 的前面指明它具体来自哪个类：
void seta(int a){ B::m_a = a; }
这样表示使用 B 类的 m_a。当然也可以使用 C 类的：

void seta(int a){ C::m_a = a; }
 

为了解决此问题，C++引入了虚继承，使得在派生类中只保留一份间接基类的成员。

例子：

复制代码
//间接基类A
class A {
protected:
    int m_a;
};
//直接基类B
class B: virtual public A {
protected:
    int m_b;
};
//直接基类C
class C: virtual public A {
protected:
    int m_c;
};
//派生类D
class D: public B, public C {
public:
    void seta(int a){ m_a = a; }  // ok
    void setb(int b){ m_b = b; }  //正确
    void setc(int c){ m_c = c; }  //正确
    void setd(int d){ m_d = d; }  //正确
private:
    int m_d;
};
复制代码
这段代码使用虚继承重新实现了上图所示的菱形继承，这样在派生类 D 中就只保留了一份成员变量 m_a，直接访问就不会再有歧义了。

虚继承的目的是让某个类做出声明，承诺愿意共享它的基类。其中，这个被共享的基类就称为虚基类（Virtual Base Class），本例中的 A 就是一个虚基类。在这种机制下，不论虚基类在继承体系中出现了多少次，在派生类中都只包含一份虚基类的成员。
 

 
如上图，在虚派生中，假设 A 定义了一个名为 x 的成员变量，当我们在 D 中直接访问 x 时，会有三种可能性：
如果 B 和 C 中都没有 x 的定义，那么 x 将被解析为 A 的成员，此时不存在二义性；
如果 B 或 C 其中的一个类定义了 x，也不会有二义性，派生类的 x 比虚基类的 x 优先级更高；
如果 B 和 C 中都定义了 x，那么直接访问 x 将产生二义性问题；
可以看到，使用多继承经常会出现二义性问题，必须十分小心。
 
 
 
 
 

钻石型继承的内部布局
 这里首先给出一个经典的菱形继承实例，及其具体实现



其中，vptr表示虚表，vbptr 表示虚基类，tiptr 表示type_info指针；
 
 
 
 
 
参考文档：
http://blog.csdn.net/haoel/article/details/1948051
 