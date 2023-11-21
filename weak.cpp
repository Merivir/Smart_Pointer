#include "weak.h"

template <typename T>
Weak<T>::Weak() : m_pt(nullptr) {}

template <typename T>
Weak<T>::Weak(T* ptr) : m_pt(new ControlBlock<T>(ptr)) {}

template <typename T>
Weak<T>::Weak(const Weak& other) : m_pt(other.m_pt) {
    if (m_pt) {
        m_pt->weakCount++;
    }
}

template <typename T>
Weak<T>::Weak(Weak&& other) noexcept : m_pt(other.m_pt) {
    other.m_pt = nullptr;
}

template <typename T>
Weak<T>::Weak(const Shared<T>& other) : m_pt(other.m_ptr) {
    if (m_pt) {
        m_pt->weakCount++;
    }
}

template <typename T>
Weak<T>::~Weak() {
    if (m_pt) {
        m_pt->weakCount--;
        if (m_pt->weakCount == 0 && m_pt->refCount == 0) {
            delete m_pt;
        }
    }
}

template <typename T>
Shared<T> Weak<T>::lock() const {
    return m_pt && refCount() > 0 ? Shared<T>(*this) : Shared<T>(nullptr);
}

template <typename T>
int Weak<T>::refCount() const {
    return m_pt ? m_pt->refCount : 0;
}

template <typename T>
T& Weak<T>::operator*() {
    return *(m_pt->m_val);
}

template <typename T>
template <typename U, typename>
T* Weak<T>::operator->() {
    if (m_pt == nullptr) {
        throw std::runtime_error("You are dereferencing nullptr");
    }
    return m_pt->m_val;
}

template <typename T>
Weak<T>& Weak<T>::operator=(const Weak& other) {
    if (this != &other) {
        if (m_pt) {
            m_pt->weakCount--;
            if (m_pt->weakCount == 0 && m_pt->refCount == 0) {
                delete m_pt;
            }
        }

        m_pt = other.m_pt;

        if (m_pt) {
            m_pt->weakCount++;
        }
    }

    return *this;
}

template <typename T>
Weak<T>& Weak<T>::operator=(Weak&& other) noexcept {
    if (this != &other) {
        if (m_pt) {
            m_pt->weakCount--;
            if (m_pt->weakCount == 0 && m_pt->refCount == 0) {
                delete m_pt;
            }
        }

        m_pt = other.m_pt;
        other.m_pt = nullptr;
    }

    return *this;
}

