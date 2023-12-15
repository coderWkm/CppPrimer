#include "Vec.h"
#include <algorithm>
template <typename T>
std::allocator<T> Vec<T>::alloc;   // static成员需要在类外定义

template <typename T>
void Vec<T>::push_back(const T &val)
{
    chk_n_alloc();
    alloc.construct(first_free++, val);
}
template <typename T>
std::pair<T*, T*>
    Vec<T>::alloc_n_copy(const T *beg, const T *end)
{
    auto data = alloc.allocate(end - beg);
    return {data, uninitialized_copy(beg, end, data)};
}
template <typename T>
void Vec<T>::free()
{
    if (elements) { // 必须先判断elements是否为空
        /*
        for (auto p = first_free; p != elements; )
            alloc.destroy(--p);
        */

        // for_each + lambda
        std::for_each(elements, first_free, [this](T& s){
           this->alloc.destroy(&s); 
        });        
        alloc.deallocate(elements, cap - elements);
    }

}
template <typename T>
Vec<T>::Vec(const Vec<T> &copy)
{
    auto data = alloc_n_copy(copy.begin(), copy.end());
    elements = data.first;
    first_free = cap = data.second;  // cap也在这赋值，是因为alloc_n_copy分配的内存大小，就是传入的字符串的大小
}
template <typename T>
Vec<T>::Vec(const std::initializer_list<T> &args)
{
    auto data = alloc_n_copy(args.begin(), args.end());
    elements = data.first;
    first_free = cap = data.second;
}
template <typename T>
Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
template <typename T>
Vec<T>::~Vec()
{
    free();
}

template <typename T>
void Vec<T>::reallocate()
{
    auto newcapacity = size() ? 2*size() : 1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements; 
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}