#include <iostream>
#include "shared.cpp"
#include "weak.cpp"

int main() {
    Shared<int> shared1(new int(42));

    std::cout << "shared1 refCount: " << shared1.refCount() << std::endl;
    std::cout << "shared1 value: " << *shared1 << std::endl;

    Shared<int> shared2 = shared1;

    std::cout << "shared2 refCount: " << shared2.refCount() << std::endl;
    std::cout << "shared2 value: " << *shared2 << std::endl;

    Weak<int> weak1 = shared1;

    std::cout << "weak1 refCount: " << weak1.refCount() << std::endl;
    std::cout << "weak1 value: " << *weak1 << std::endl;

    Weak<int> weak2 = shared2;

    std::cout << "weak2 refCount: " << weak2.refCount() << std::endl;
    std::cout << "weak2 value: " << *weak2 << std::endl;

    {
        Shared<int> shared3 = weak1.lock();

        std::cout << "shared3 refCount: " << shared3.refCount() << std::endl;
        std::cout << "shared3 value: " << *shared3 << std::endl;
    }

    std::cout << "weak1 refCount after shared3 is out of scope: " << weak1.refCount() << std::endl;

    return 0;
}
