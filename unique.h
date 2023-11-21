#ifndef UNIQUE_H
#define UNIQUE_H

template <typename T>
class Unique {
public:
    Unique(T* ptr);
    ~Unique();
    Unique(const Unique&) = delete;
    Unique& operator=(const Unique&) = delete;
    Unique(Unique&& other) noexcept;
    Unique& operator=(Unique&& other) noexcept;
    T& operator*() const;
    T* operator->() const;

private:
    T* m_ptr;
};

#endif // UNIQUE_H
