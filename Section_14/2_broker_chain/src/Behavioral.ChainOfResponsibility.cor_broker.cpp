#include <iostream>
#include <string>
using namespace std;
#include <boost/signals2.hpp> //This is a library for implementing events
using namespace boost::signals2;

/*
We are now going to take a look at a much more sophisticated implementation of the chain of responsibility design pattern.
What we're going to be building is effectively an event broker. An event broker is actually a combination of several different patterns.

Event broker = change of responsibility + observer (signals2) + cqs (command query separation) 

cqs is a separate idea of splitting the system into commands and queries. This affects also the command design pattern (section 15).

Game class is a mediator, we're also covering the mediator design pattern.

We're going to set up the situation where in order to figure out a creature's attack or defense value, you query it and every single other
object in the game has a chance to modify the result of that query.

So what we're going to do here is we'll define a signal. And a signal is a way of defining an event that people can subscribe to.

Essentially, when you want to query something from the game, you take this signal and you give it a query and you invoke it and the query
goes through every single subscriber of that signal. And every single subscriber can actually do something with a query.

As an alternative of that would be if you just kept some kind of vector or list, which kept basically, which is done in the assignment.
*/


// class where you get to request some information about the creature
struct Query
{
  string creature_name;
  enum Argument { attack, defense } argument; //definition of the enum class (class word not needed because it is already inside a class) and set it as a parameter at the same time
  int result;

  Query(const string& creature_name, const Argument argument, const int result)
    : creature_name(creature_name),
      argument(argument),
      result(result)
  {
  }
};

struct Game // mediator
{
  signal<void(Query&)> queries; //signal which is a void function which takes a query reference
};

class Creature
{
  Game& game;
  int attack, defense;
public:
  string name;
  Creature(Game& game, const string& name, const int attack, const int defense)
    : game(game),
      attack(attack),
      defense(defense),
      name(name)
  {
  }
  
  // no need for this to be virtual
  /*
  Here we create a query and call the signal with that query and return the result of the query
  */
  int GetAttack() const
  {
    Query q{ name, Query::Argument::attack, attack };
    game.queries(q); // invoke whoever is subscribed to this signal and execute the void function with this query as argument.
    return q.result;
  }

  // We invoke the GetAttack method is the cout operator
  friend ostream& operator<<(ostream& os, const Creature& obj)
  {
    return os
      << "name: " << obj.name
      << " attack: " << obj.GetAttack() // note here
      << " defense: " << obj.defense;
  }
};

// Base class of the modifier
class CreatureModifier
{
  Game& game;
  Creature& creature;
public:
  virtual ~CreatureModifier() = default;

  // there is no handle() function

  CreatureModifier(Game& game, Creature& creature)
    : game(game),
      creature(creature)
  {
  }
};

class DoubleAttackModifier : public CreatureModifier
{
  connection conn;
public:
  DoubleAttackModifier(Game& game, Creature& creature)
    : CreatureModifier(game, creature)
  {
    // whenever someone wants this creature's attack,
    // we return DOUBLE the value
    // Here we subscribe to the signal and provide a lambda which implements the modification
    conn = game.queries.connect([&](Query& q)
    {
      if (q.creature_name == creature.name && 
        q.argument == Query::Argument::attack)
        q.result *= 2;
    });
  }

  // unsubscribe to the signal
  ~DoubleAttackModifier()
  {
    conn.disconnect();
  }
};

// similar idea, but Query instead of Command
int main(int ac, char* av[])
{
  Game game;
  Creature goblin{ game, "Strong Goblin", 2, 2 };

  cout << goblin << endl;

  {
    DoubleAttackModifier dam{ game, goblin };

    cout << goblin << endl;
  }

  cout << goblin << endl;
  return 0;
}
