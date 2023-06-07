#include <iostream>
#include "Foo.h"

int main() {
	Foo p;

	int value = p.greet();
	
	std::cout << "The value got from greet is: " << value << std::endl;
}