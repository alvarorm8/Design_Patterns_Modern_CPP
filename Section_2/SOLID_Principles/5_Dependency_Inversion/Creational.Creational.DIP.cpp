#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;
/*
* Dependency Inversion Principle:
*
* A. High-level modules should not depend on low-level modules.
*    Both should depend on abstractions (interfaces).
* B. Abstractions should not depend on details. 
*    Details should depend on abstractions (interfaces).
*
* By abstractions we mean interfaces or base classes.
* 
* The sentence A means we want the modules to be as general as possible so you don't depend on implementation.
* 
* Here, if in Research high level module, if we want to find the relationship, we would have to pass as argument
* to Research constructor a Relationships reference, which is a low level module, so this principle would be broken.
* The problem is that if the low level module changes the vector, or anything like that, in the high level module we would
* have to change the implementation, so that's a problem.
* 
* To fix this, we can implement an interface like RelationshipBrowser, so the high level module gets a reference of 
* that interface and the low level module implements that interface through inheritation. This way, the high level module
* does not depend on the low level module, and both high level and low level modules depend on abstraction through a general interface.
* 
* Also the single responsibility principle puts the logic of looking for a relationship between people in Relationships class, not in 
* Research class, so we can do it through the find_all_children_of method putting it into the interface RelationshipBrowser.
*/

enum class Relationship
{
  parent,
  child,
  sibling
};

struct Person
{
  string name;
};

struct RelationshipBrowser
{
  virtual vector<Person> find_all_children_of(const string& name) = 0;
};

struct Relationships : RelationshipBrowser // low-level module, because it stores data
{
  vector<tuple<Person, Relationship, Person>> relations;

  void add_parent_and_child(const Person& parent, const Person& child)
  {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }

  vector<Person> find_all_children_of(const string &name) override
  {
    vector<Person> result;
    for (auto&& [first, rel, second] : relations)
    {
      if (first.name == name && rel == Relationship::parent)
      {
        result.push_back(second);
      }
    }
    return result;
  }
};

struct Research // high-level module, because it works with data
{
  Research(RelationshipBrowser& browser)
  {
    for (auto& child : browser.find_all_children_of("John"))
    {
      cout << "John has a child called " << child.name << endl;
    }
  }
//  Research(const Relationships& relationships)
//  {
//    auto& relations = relationships.relations;
//    for (auto&& [first, rel, second] : relations)
//    {
//      if (first.name == "John" && rel == Relationship::parent)
//      {
//        cout << "John has a child called " << second.name << endl;
//      }
//    }
//  }
};

int main()
{
  Person parent{"John"};
  Person child1{"Chris"};
  Person child2{"Matt"};

  Relationships relationships;
  relationships.add_parent_and_child(parent, child1);
  relationships.add_parent_and_child(parent, child2);

  Research _(relationships);

  return 0;
}