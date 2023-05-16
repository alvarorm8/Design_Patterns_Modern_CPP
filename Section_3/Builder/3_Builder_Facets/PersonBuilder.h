#pragma once
#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase
{
protected:
  //to avoid duplicated Person elements when inheriting this class, a common approach is to have a base class with a reference to the object
  //and in derived classes to actually have the object
  Person& person; 
  explicit PersonBuilderBase(Person& person)
    : person{ person }
  {
  }
public:

  //Like in 1_Builder we create an operator to return a Person object when creating an object with PersonBuilderBase
  operator Person() const
  {
    return std::move(person);
  }

  // builder facets

  PersonAddressBuilder lives() const;
  PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase
{
  Person p; //the derived class has the actual object Person, but not in PersonAddressBuilder and PersonJobBuilder to avoid duplication of Person object
public:
  PersonBuilder(): PersonBuilderBase{p}
  {
  }

};