#ifndef WEAK_H
#define WEAK_H

#include "controlBlock.hpp"

template <typename T>
class Shared;

template <typename T>
class Weak {
public:
    Weak();
    Weak(T* ptr);
    Weak(const Weak& other);
    Weak(const Shared<T>& other);
    ~Weak();
    Shared<T> lock() const;
    int refCount() const;
    T& operator*();
    template <typename U = T, typename = std::enable_if_t<!std::is_fundamental_v<U>>>
    T* operator->();

private:
    ControlBlock<T>* m_pt;
    friend class Shared<T>;
};

#endif // WEAK_H
