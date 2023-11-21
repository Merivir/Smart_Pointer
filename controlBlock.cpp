#include "controlBlock.hpp"

template <typename T>
ControlBlock<T>::ControlBlock(T* val) : m_val(val), refCount(1), weakCount(0) {}

template <typename T>
ControlBlock<T>::ControlBlock(ControlBlock&& other)
    : m_val(other.m_val), refCount(other.refCount), weakCount(other.weakCount) {
    other.m_val = nullptr;
    other.refCount = 0;
    other.weakCount = 0;
}

template <typename T>
ControlBlock<T>& ControlBlock<T>::operator=(ControlBlock&& other) {
    if (this != &other) {
        delete m_val;
        m_val = other.m_val;
        other.m_val = nullptr;
        refCount = other.refCount;
        weakCount = other.weakCount;
        other.refCount = 0;
        other.weakCount = 0;
    }

    return *this;
}

template <typename T>
ControlBlock<T>::~ControlBlock() {
    if (refCount == 0 && m_val != nullptr) {
        delete m_val;
    }
}
