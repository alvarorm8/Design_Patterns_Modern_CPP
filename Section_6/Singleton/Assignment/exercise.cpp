/*
Implementing a singleton is a bit too easy, so you've got a different challenge.

You are given the function SingletonTester::is_singleton()  defined below. This function takes a factory, and needs to return true  or false
depending on whether that factory produces singletons.

This one's actually easy. Ask yourself: what traits do two 'instances' of a singleton have in common? -> the address
*/

#include <functional>
#include <memory>
#include <iostream>
using namespace std;

class Once {
    Once() {
        std::cout << "Creating Once: " << this << std::endl;
    }
    ~Once() {
        std::cout << "Destroying Once: " << this << std::endl;
    }
public:
    static Once* get() {
        static Once obj;
        std::cout << "Address of obj: " << &obj << std::endl;
        return &obj;
    }
};

struct SingletonTester
{
    template <typename T>
    bool is_singleton(function<T* ()> factory)
    {
        T* obj1{ factory() };
        T* obj2{ factory() };

        return obj1 == obj2;
    }
};

int main() {
    std::cout << "main starts" << std::endl;
    SingletonTester tester;
    auto isSingleton{ tester.is_singleton<Once>([]() -> Once* {return Once::get(); }) };
    std::cout << boolalpha << isSingleton << std::endl;
    std::cout << "main ends" << std::endl;
}