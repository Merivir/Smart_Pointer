template <typename T>
Shared<T>::Shared(T* ptr) : m_ptr(new ControlBlock<T>(ptr)) {}

template <typename T>
Shared<T>::Shared(const Shared& other) : m_ptr(other.m_ptr) {
    if (m_ptr) {
        m_ptr->refCount++;
    }
}

template <typename T>
Shared<T>::Shared(Shared&& other) noexcept : m_ptr(other.m_ptr) {
    other.m_ptr = nullptr;
}

template <typename T>
Shared<T>::Shared(const Weak<T>& weak) : m_ptr(weak.m_pt) {
    if (m_ptr) {
        m_ptr->refCount++;
    }
}

template <typename T>
Shared<T>::~Shared() {
    if (m_ptr) {
        m_ptr->refCount--;
    }
    if (m_ptr->refCount == 0) {
        delete m_ptr;
    }
}

template <typename T>
Shared<T>& Shared<T>::operator=(const Shared& other) {
    if (this != &other) {
        if (m_ptr) {
            m_ptr->refCount--;
        }
        if (m_ptr->refCount == 0) {
            delete m_ptr;
        }

        m_ptr = other.m_ptr;
        m_ptr->refCount = other.m_ptr->refCount;

        if (m_ptr) {
            m_ptr->refCount++;
        }
    }

    return *this;
}

template <typename T>
Shared<T>& Shared<T>::operator=(Shared&& other) noexcept {
    if (this != &other) {
        if (m_ptr) {
            m_ptr->refCount--;
        }
        if (m_ptr->refCount == 0) {
            delete m_ptr;
        }

        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
    }

    return *this;
}

template <typename T>
T& Shared<T>::operator*() {
    if (m_ptr == nullptr) {
        throw std::runtime_error("You are dereferencing nullptr");
    }
    return *(m_ptr->m_val);
}

template <typename T>
template <typename U, typename>
T* Shared<T>::operator->() {
    if (m_ptr == nullptr) {
        throw std::runtime_error("You are dereferencing nullptr");
    }
    return m_ptr->m_val;
}

template <typename T>
int Shared<T>::refCount() const {
    if (m_ptr == nullptr) {
        throw std::runtime_error("You are dereferencing nullptr");
    }
    return m_ptr->refCount;
}

template <typename T, typename... Args>
Shared<T> make_shared(Args&&... args) {
    return Shared<T>(new T(std::forward<Args>(args)...));
}
