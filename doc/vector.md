resize 设定vector元素个数；如果超过capacity后，会扩充容量；

reserve 设定vector容量，**只保证容量至少达到设定值，不会比设定值小**

reserve如果无法达到直接缩容的目的；

vector 删除元素后，迭代器失效，需要保存返回的迭代器.iterator = vec.erase(iterator) 删除元素