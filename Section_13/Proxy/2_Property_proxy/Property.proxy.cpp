#include <iostream>
#include <string>
#include <sstream>
#include <memory>
using namespace std;

/*
* A property is basically an attribute plus a getter and a setter. This proxy allows you to access to the attribute with operators
* operator T() which converts to the type of the template and operator = to assign. You can do also a getter and a setter.
*/

// ======== Property Proxy ======================

template <typename T> struct Property
{
    T value;
    Property(const T initialValue)
    {
        *this = initialValue;
    }
    operator T()
    {
        return value;
    }
    T operator =(T newValue)
    {
        return value = newValue;
    }
};

// ===========================================

struct Creature
{
    Property<int> strength{ 10 };
    Property<int> agility{ 5 };
};

void property_proxy()
{
    Creature creature;
    creature.agility = 20;
    cout << creature.agility << endl;
}

int main()
{
    property_proxy();

    getchar();
    return 0;
}