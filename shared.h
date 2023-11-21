#ifndef SHARED_H
#define SHARED_H

#include "controlBlock.hpp"

template <typename T>
class Weak;

template <typename T>
class Shared {
public:
    Shared(T* ptr);
    Shared(const Shared& other);
    Shared(Shared&& other) noexcept;  
    Shared(const Weak<T>& weak);
    ~Shared();

    Shared& operator=(const Shared& other);
    Shared& operator=(Shared&& other) noexcept; 

    T& operator*();
    template <typename U = T, typename = std::enable_if_t<!std::is_fundamental_v<U>>>
    T* operator->();
    int refCount() const;

private:
    ControlBlock<T>* m_ptr;
    friend class Weak<T>;
};

#endif // SHARED_H
