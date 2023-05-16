#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

/*
* More complicated example of Builder pattern in which the object to build is very complex, so we need several builders to
* manage different aspects of the object.This is know as a Builder Façade.
* 
* A façade is another pattern which has another section and here we combine the Builder and the Façade patterns.
* 
* Here the object we want to construct is Person (see comments there in .h).
* 
* When all comments in .h files have been read, follow the comments below.
* 
* In the call:
* 1. We first create a PersonBuilder object with create
* 2. Calling lives creates a PersonAddressBuilder (we can call it since we have a PersonBuilder that inherits from PersonBuilderBase 
* which has the function works)and we can call its functions at, with_postcode and in
* 3. Calling works (we can call it since we have a PersonAddressBuilder that inherits from PersonBuilderBase which has the function works)
* we creates a PersonJobBuilder and we can call its functions at, as_a and earning
* 4. We implicitly call the operator in PersonAddressBuilderBase to construct the Person object
* 5. We call the operator << defined in Person.h
* 
* Here we can see why the PersonBuilderBase, PersonAddressBuilder and PersonJobBuilder do not have a Person object, because if the do, we would have 3 Person
* objects in total when creating the PersonBuilder, PersonAddressBuilder and PersonJobBuilder objects.
*/

int main__()
{
  Person p = Person::create()
    .lives()
        .at("123 London Road")
        .with_postcode("SW1 1GB")
        .in("London")
    .works()
        .at("PragmaSoft")
        .as_a("Consultant")
        .earning(10e6);

  cout << p << endl;
  getchar();
  return 0;
}