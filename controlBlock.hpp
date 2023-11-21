#ifndef CONTROLBLOCK_HPP
#define CONTROLBLOCK_HPP

#include <stdexcept>

template <typename T>
struct ControlBlock {
    T* m_val;
    int refCount;
    int weakCount;

    ControlBlock(T* val);
    ControlBlock(const ControlBlock& other) = delete;
    ControlBlock& operator=(const ControlBlock& other) = delete;
    ControlBlock(ControlBlock&& other) noexcept;
    ControlBlock& operator=(ControlBlock&& other) noexcept;
    ~ControlBlock();
};

#include "controlBlock.cpp"

#endif // CONTROLBLOCK_HPP
