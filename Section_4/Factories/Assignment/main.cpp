/*
You are given a class called Person. The person has two fields: id and name .

Please implement a non-static PersonFactory that has a create_person()  method that takes a person's name.

The id of the person should be set as a 0-based index of the object created. So, the first person the factory makes should have id=0, second id=1 and so on.
*/

#include <string>
#include <iostream>
using namespace std;

struct Person
{
  int id;
  string name;
};

class PersonFactory
{
  inline static int personID = 0;
public:
  Person create_person(const string& name)
  {
    return { personID++, name };
  }
};

int main() {

  PersonFactory pf;

  Person p1 = pf.create_person("Alvaro");
  Person p2 = pf.create_person("Luis");
  Person p3 = pf.create_person("Clara");
  Person p4 = pf.create_person("Laura");

  std::cout << "p1: " << p1.id << ", " << p1.name << std::endl;
  std::cout << "p2: " << p2.id << ", " << p2.name << std::endl;
  std::cout << "p3: " << p3.id << ", " << p3.name << std::endl;
  std::cout << "p4: " << p4.id << ", " << p4.name << std::endl;
  return 0;
}