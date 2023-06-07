#pragma once
#include <string>

/*
* The pimple idiom is about hiding the implementation details of a particular class by sticking it into its implementation.
* 
* The idea is that the implementation details of Person class are deferred or bridged into a separate class. For that, we declare 
* a class inside (PersonImpl) and a pointer to that class, but the implementation of that class is not done in the main class (Person)
* 
* We instatiate the inner class (PersonImpl) in the constructor and destructor of the main class (Person). 
* Also, the actual definition of the inner class happens in the .cpp file (we define the PersonImpl class there Person::PersonImpl, and the member Person::PersonImpl::greet(Person* p)),
* and when we define Person::greet, we only have to call to impl->greet().
* 
* This way, when someone consumes this as a API, in the header file they can't see any detail of the implementation.
* 
* The utility of this is that if you implement this in a regular way, when the API is generated, the .h file will be given to the consumer, and if you have for example a private section
* with secret functions that you need, even though the consumer can't see the implementation of those secret functions, he will know about them. With this, they won't know anything.
*/

struct Person
{
  std::string name;

  class PersonImpl;
  PersonImpl *impl; // bridge - not necessarily inner class, can vary

  Person();
  ~Person();

  void greet();
};
