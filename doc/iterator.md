# 迭代器失效问题
## 插入操作
vector和string涉及内存重新分配时候，迭代器（iterator）、指针（pointer）和引用(reference)均失效。若没有内存重新分配，
则插入点之前的iterator有效，插入点之后iterator失效。

deque（双端队列），如果插入点除front和back外的其他位置，iterator、pointer、reference失效；当插入元素是front和back时，
deque的iterator迭代器失效，但reference和pointer有效。（todo:需要测试这种场景）

对于list（双向链表）和forward_list，所有的iterator、pointer、reference均有效；

## 删除操作
vector和string ，删除点之前的iterator、pointer、reference有效，off-the-end迭代器总是失效的。
deque，如果删除点是除front和back外其他位置，iterator、pointer、reference失效；**当删除front和back时，
off-the-end失效，其他的iterator、pointer、reference有效??**
list和forward_list，所有的iterator、pointer和reference有效；
map，如果某一个元素已经被删除，则（被删除元素）对应的迭代器失效，不应该再被使用，否则程序会导致未定义行为。
