#include "Foo.h"

#include <iostream>

class Foo::inner
{
	int ID;
public:
	inner();
	int greet(Foo* p);
};

Foo::inner::inner() : ID{10}
{}

int Foo::inner::greet(Foo* p)
{
	std::cout << "Hello there!" << std::endl;
	return 10;
}

int Foo::greet()
{
	return inside->greet(this);
	//return (*inside).greet(this);
}
