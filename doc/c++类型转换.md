总结下上面列出了几个使用const_cast的场景：
指向const的指针修改其所指向的非const对象；
将一个const实参传给一个普通形参；
const成员函数修改非const成员；
去volatile属性；

一般转换分为两种: 上行转换和下行转换。
上行转换大致意思是把子类实例向上转换为父类型, 下行转换是把父类实例转换为子类实例；
通常子类因为继承关系会包含父类的所有属性, 但是有些子类的属性父类没有；
所以上行转换的时候，子类实例转换给父类是安全的，转换后的指针或者对象可以放心使用父类的所有方法或者属性；
但是下行转换的时候可能是不安全的，因为假如子类有父类没有的属性或者方法的话，父类指针或者实例转换为子类型后，转换后的实例中并没有子类多出来的方法或属性，当调用到这些方法或属性时程序就会崩溃了。

static_cast主要在以下几种场合中使用：
用于类层次结构中，父类和子类之间指针和引用的转换；进行上行转换，把子类对象的指针/引用转换为父类指针/引用，这种转换是安全的；进行下行转换，把父类对象的指针/引用转换成子类指针/引用，这种转换是不安全的，需要编写程序时来确认；
用于基本数据类型之间的转换，例如把int转char，int转enum等，需要编写程序时来确认安全性；
把void指针转换成目标类型的指针（这是极其不安全的）；


Run-Time Type Identification (RTTI)
RTTI 是运行时类型信息，它提供了运行时确定对象类型的方法。



typeid操作符的返回结果是名为type_info的标准库类型的对象的引用，编译器会为每一种typeid操作的类型生成一份保存在数据段的type_info数据。

对于c++的内置数据类型，typeid可以方便的输出它们的数据类型，例如：
```
复制代码
template<class T>
void typeinfo(T val) {
    const char* t = typeid(val).name();

    if (*t == 's') {
        cout << "short" << endl;
    } else if (*t == 'j') {
        cout << "unsigned int" << endl;
    } else if (*t == 'i') {
        cout << "int" << endl;
    } else if (*t == 'c') {
        cout << "char" << endl;
    } else if (*t == 'd') {
        cout << "double" << endl;
    } else if (*t == 'f') {
        cout << "float" << endl;
    }
}

int main() {
    short s = 2;
    unsigned ui = 10;
    int i = 10;
    char ch = 'a';
    float f = 1.0f;
    double d = 2;

    typeinfo(s);    // short
    typeinfo(ui);   // unsigned int
    typeinfo(i);    // int
    typeinfo(ch);   // char
    typeinfo(f);    // float
    typeinfo(d);    // double

    return 0;
}
复制代码
```


对类类型也可以查看其类型：

复制代码
class A {
public:
    void Print() { cout << "This is class A." << endl; }
};

class B : public A {
public:
    void Print() { cout << "This is class B." << endl; }
};

int main() {
    A *p = new A();
    A a2;
    A& a3 = a2;

    cout << typeid(p).name() << endl; // P1A
    cout << typeid(a2).name() << endl; // 1A
    cout << typeid(a3).name() << endl; // 1A

    B *pB = new B();
    cout << typeid(pB).name() << endl; // P1B

    A* pA = new B();
    cout << typeid(pA).name() << endl;  // P1A
    cout << typeid(*pA).name() << endl; // 1A

    return 0;
}
复制代码
这个例子中，最后2行，用基类指针pA指向派生类对象，此时pA 和 *pA 都是A类型；

如果我们把父类中的Print函数加上virutal，如下：

复制代码
class A {
public:
    virtual void Print() { cout << "This is class A." << endl; }
};

class B : public A {
public:
    void Print() { cout << "This is class B." << endl; }
};

int main() {
    A *p = new A();
    A a2;
    A& a3 = a2;

    cout << typeid(p).name() << endl; // P1A
    cout << typeid(a2).name() << endl; // 1A
    cout << typeid(a3).name() << endl; // 1A

    B *pB = new B();
    cout << typeid(pB).name() << endl; // P1B

    A* pA = new B();
    cout << typeid(pA).name() << endl;  // P1A
    cout << typeid(*pA).name() << endl; // 1B

    return 0;
}
复制代码
此时，pA仍是A类型，但*pA却变成了B类型；这就是RTTI 在起作用，

当类中不存在虚函数时，typeid是编译时期的事情，也就是静态类型；
当类中存在虚函数时，typeid是运行时期的事情，也就是动态类型。
此外，对于父类指针类型变量，typeid(ptr).name不具有多态性，仍返回此父类的指针类名。如果直接传入对象如typeid(*ptr).name则具有多态性


dynamic_cast（动态转换）
dynamic_cast 主要用于类对象的指针和引用的类转换，作用是把 exdivssion 转换成 type-id 类型的对象。其中 type-id 必须是类的指针、类的引用或者 void *。

dynamic_cast 在执行类型转换时首先检查能否成功转换，如果能成功转换则转换；如果是指针转换失败，则返回 NULL；如果是引用转换失败，则抛出 bad_cast 异常。

dynamic_cast < type-id > （ exdivssion ）


有时我们需要在运行时查询一个对象是否能作为某种多态类型使用。与Java的instanceof，以及C#的as、is运算符类似，C++提供了dynamic_cast函数用于动态转型。相比C风格的强制类型转换和C++ reinterpret_cast，dynamic_cast提供了类型安全检查，是一种基于能力查询(Capability Query)的转换，所以在多态类型间进行转换更提倡采用dynamic_cast。

dynamic_cast依赖于RTTI ，在转换时，会检查转换的对象是否真的可以转换成type-id类型，这种检查不是语法上的，而是真实情况的检查。

先看RTTI 相关部分，通常，许多编译器都是通过vtable（虚函数表）找到对象的RTTI信息的，这也就意味着，如果基类没有虚函数，也就无法判断一个基类指针所指对象的真实类型，这时候，dynamic_cast只能用来做安全的转换，例如从派生类指针转换成基类指针。而这种转换其实并不需要dynamic_cast参与。




看个例子

T1 obj;

T2* pObj = dynamic_cast<T2*>(&obj);　　　　// T1*转换为T2*，失败返回NULL

T2& refObj = dynamic_cast<T2&>(obj);　　  // T1&转换为T2&，失败抛出bad_cast异常
被转换对象obj的类型T1必须是多态类型，即T1必须公有继承自其它类，或者T1拥有虚函数（继承或自定义）。若T1为非多态类型，使用dynamic_cast会报编译错误。

在多态类型间转换，分为3种类型：

子类向基类的向上转型(Up Cast)
基类向子类的向下转型(Down Cast)
横向转型(Cross Cast)
向上转型是多态的基础，需不要借助任何特殊的方法，只需用将子类的指针或引用赋给基类的指针或引用即可，当然dynamic_cast也支持向上转型，而其总是肯定成功的。而对于向下转型和横向转型来讲，都属于能力查询。



如下例子，Square类继承了Shape，Circle类则同时继承了Shape、Rollable，
![imag](.\\imag\\shape_rollable.png)




我们尝试把Square、Circle两种动态类型转换为Rollable，前者失败，后者成功（因为Circle继承了Rollable，且有虚函数）。

复制代码
class Shape {
public:
    virtual ~Shape() {};
    virtual void draw() const = 0;
};

class Rollable {
public:
    virtual ~Rollable() {};
    virtual void roll() = 0;
};

class Circle : public Shape, public Rollable {
    void draw() const {cout << "draw circle" << endl;}
    void roll() {cout << "roll circle" << endl;}
};

class Square : public Shape {
    void draw() const {cout << "draw square" << endl;}
};

int main() {
    Shape *pShape1 = new Square();
    Shape *pShape2 = new Circle();

    Rollable *pRollable1 = dynamic_cast<Rollable*>(pShape1);
    cout << pRollable1 << endl; // NULL

    Rollable *pRollable2 = dynamic_cast<Rollable*>(pShape2);
    cout << pRollable2 << endl; // NOT NULL

    return 0;
}
复制代码
在上面的例子中，dynamic_cast 将 pRollable2指针 在 pShare2指针 的基础上进行偏移（比如+8），















reinterpret_cast
支持任何转换，但仅仅是如它的名字所描述的那样“重解释”而已，不会对指针的值进行任何调整，用它完全可以做到“指鹿为马”，但很明显，它是最不安全的转换，使用它的时候，你得头脑清醒，知道自己在干什么；

