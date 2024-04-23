#include <string>
#include <iostream>
using namespace std;
/*
You are given the Person class and asked to write a ResponsiblePerson wrapper/proxy that does the following:

-Allows person to drink unless they are younger than 18 (in that case, return "too young")
-Allows person to drive unless they are younger than 16 (otherwise, "too young")
-In case of driving while drink, returns "dead"

The interface of ResponsiblePerson  has to match that of Person , except for the constructor, which takes an underlying Person object..
*/

class Person
{
    friend class ResponsiblePerson;
    int age;
public:
    Person(int age) : age(age) {}

    int get_age() const { return age; }
    void set_age(int age) { this->age = age; }

    string drink() const { return "drinking"; }
    string drive() const { return "driving"; }
    string drink_and_drive() const { return "driving while drunk"; }
};

class ResponsiblePerson
{
public:
    ResponsiblePerson(const Person& person) : person(person) {}
    // todo
    int get_age() const { return person.age; }
    void set_age(int age) { this->person.age = age; }
    string drink() const { 
        if (person.get_age() < 18)
            return "too young";
        return person.drink();
    }
    string drive() const {
        if (person.get_age() < 16)
            return "too young";
        return person.drive();
    }
    string drink_and_drive() const {
        return "dead";
    }
private:
    Person person;
};

int main() {
    Person person(28);

    std::cout << person.drink() << std::endl;
    std::cout << person.drive() << std::endl;
    std::cout << person.drink_and_drive() << std::endl;

    ResponsiblePerson person2(person);

    std::cout << person2.drink() << std::endl;
    std::cout << person2.drive() << std::endl;
    std::cout << person2.drink_and_drive() << std::endl;
}