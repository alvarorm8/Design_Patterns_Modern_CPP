#include <array>
#include <iostream>
#include <numeric>

/*
* An example of an intersection of the composite and proxy patterns is shown. It has to do with the ways that fields are exposed from objects.
* 
* The Creature class is done in a regular way, and it is too tedious to implement all the different methods we want, like maximum, etc. Even worse, if we have 10 statistics, it would be much more tedious.
* 
* The solution the composite pattern offers is the idea of having aggregate storage or composite storage for the fields.
* 
* So we are rewriting the Creature class using an approach called Array Baxt Properties, in which we use an enum to indicate all the abilities.
* 
* So the main idea is you don't need to have all fields separately, you can have a single field and use STL algorithms to process them.
*/

//class Creature
//{
//  int strength, agility, intelligence;
//  // new property
//  int charisma;
//public:
//  int get_strength() const
//  {
//    return strength;
//  }
//
//  void set_strength(int strength)
//  {
//    Creature::strength=strength;
//  }
//
//  int get_agility() const
//  {
//    return agility;
//  }
//
//  void set_agility(int agility)
//  {
//    Creature::agility=agility;
//  }
//
//  int get_intelligence() const
//  {
//    return intelligence;
//  }
//
//  void set_intelligence(int intelligence)
//  {
//    Creature::intelligence=intelligence;
//  }
//
//  // sum, average, max.
//
//  double sum() const {
//    return strength + agility + intelligence;
//  }
//
//  double average() const {
//    return sum() / 3.0;
//  }
//
//  int max() const {
//    return ::max(::max(strength, agility), intelligence);
//  }
//};

class Creature
{
  enum Abilities { str, agl, intl, count }; //count is the terminating element of the enum, it is used to know how many elements the enum has
  std::array<int, count> abilities; //array of count elements (number of abilities)
public:
  int get_strength() const { return abilities[str]; }
  void set_strength(int value) { abilities[str] = value; }

  int get_agility() const { return abilities[agl]; }
  void set_agility(int value) { abilities[agl] = value; }

  int get_intelligence() const { return abilities[intl]; }
  void set_intelligence(int value) { abilities[intl] = value; }

  int sum() const {
    return std::accumulate(abilities.begin(), abilities.end(), 0);
  }

  double average() const {
    return sum() / (double)count;
  }

  int max() const {
    return *max_element(abilities.begin(), abilities.end());
  }
};

int main(int ac, char* av[])
{
  Creature orc;
  orc.set_strength(16);
  orc.set_agility(11);
  orc.set_intelligence(9);

  std::cout << "The orc has an average stat of "
       << orc.average()
       << " and a maximum stat of "
       << orc.max()
       << "\n";

  return 0;
}