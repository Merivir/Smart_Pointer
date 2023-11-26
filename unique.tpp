#include <iostream>

template <typename T>
Unique<T>::Unique(T* ptr) : m_ptr(ptr) {}

template <typename T>
Unique<T>::~Unique() {
    delete m_ptr;
}

template <typename T>
Unique<T>::Unique(Unique&& other) noexcept : m_ptr(other.m_ptr) {
    other.m_ptr = nullptr;
}

template <typename T>
Unique<T>& Unique<T>::operator=(Unique&& other) noexcept {
    if (this != &other) {
        delete m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
    }
    return *this;
}

template <typename T>
T& Unique<T>::operator*() const {
    return *m_ptr;
}

template <typename T>
T* Unique<T>::operator->() const {
    return m_ptr;
}

template <typename T, typename... Args>
Unique<T> make_unique(Args&&... args) {
    return Unique<T>(new T(std::forward<Args>(args)...));
}
