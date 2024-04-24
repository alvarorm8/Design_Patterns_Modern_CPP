#include <iostream>
#include <string>
using namespace std;

/*
We are a building a chain of pointer (list of pointer).

In the classic implementation of the pattern, to modify the parameteres of a a class, we define a modifier class (CreatureModifier).
This class is a singly linked list, so it is a class which has a pointer to the next member of the same class. So this allows us to chain the creature modifiers together.
The whole point is that you inherit the creature modifier and you define what kind of modifications you actually want to be done on the creature.

The class has a reference to the creature that we're going to modify (Can be done with a pointer or sharedptr also)

This class has a method called handle, which simply calls to the next element of the chain handle method (this is how we propagate the effect on the chain). This class is going to be inherited,
and in the child classes, we do the modifications we want and then we call the base class implementation of the method to follow the chain execution.

Once we don't want the modifiers to take effect, what you do is you simply fail to propagate the base class call. For that, we do a modifier which has no effect (NoBonusesModifier)
and which does not call the base class call of handle. We add this modifier to the first element in the chain, so the chain fails in its propagation.

This particular implementation of a chain of responsibility is really quite artificial, because essentially what's happening here is you're building a singly linked list.
So the question is, well, why not just use a list or a vector? It's certainly a very valid concern. Why not simply just have some sort of structure maybe inside the goblin itself, which keeps the different modifiers?
So this is how people used to build chain of responsibilities, but it's not really how it's done anymore.
*/

struct Creature
{
  string name;
  int attack, defense;

  Creature(const string& name, const int attack, const int defense)
    : name(name),
      attack(attack),
      defense(defense)
  {
  }

  friend ostream& operator<<(ostream& os, const Creature& obj)
  {
    return os
      << "name: " << obj.name
      << " attack: " << obj.attack
      << " defense: " << obj.defense;
  }
};

class CreatureModifier
{
  CreatureModifier* next{ nullptr }; // unique_ptr
protected:
  Creature& creature; // pointer or shared_ptr
public:
  explicit CreatureModifier(Creature& creature)
    : creature(creature)
  {
  }
  virtual ~CreatureModifier() = default;

  void add(CreatureModifier* cm)
  {
    /*
    This is how you add an element to the end of a singly linked list because you don't implicitly know where the list ends. So you just follow the pointer chain until you reach the very end.
    */
    if (next) next->add(cm);
    else next = cm;
  }

  /*
  To have a default implementation is relevant because when we inherit the creature modifier, we're going to be wanting to, 
  in addition to doing our thing, we're going to be wanting to call the base handle invocation, this particular invocation in order
  to actually follow the entire chain.
  */
  // two approaches:

  // 1. Always call base handle(). There could be additional logic here.
  // 2. Only call base handle() when you cannot handle things yourself.

  virtual void handle()
  {
    if (next) next->handle();
  }
};

// 1. Double the creature's attack
// 2. Increase defense by 1 unless power > 2
// 3. No bonuses can be applied to this creature

class NoBonusesModifier : public CreatureModifier
{
public:
  explicit NoBonusesModifier(Creature& creature)
    : CreatureModifier(creature)
  {
  }

  void handle() override
  {
    // nothing
  }
};

class DoubleAttackModifier : public CreatureModifier
{
public:
  explicit DoubleAttackModifier(Creature& creature)
    : CreatureModifier(creature)
  {
  }

  void handle() override
  {
    // First, do what we want, second, call the base class method to follow the chain of responsibility
    creature.attack *= 2;
    CreatureModifier::handle();
  }
};

class IncreaseDefenseModifier : public CreatureModifier
{
public:
  explicit IncreaseDefenseModifier(Creature& creature)
    : CreatureModifier(creature)
  {
  }


  void handle() override
  {
    if (creature.attack <= 2)
      creature.defense += 1;
    CreatureModifier::handle();
  }
};

int main()
{
  Creature goblin{ "Goblin", 1, 1 };
  // The route is kind of the start of our singly linked list.
  CreatureModifier root{ goblin };
  DoubleAttackModifier r1{ goblin };
  DoubleAttackModifier r1_2{ goblin };
  IncreaseDefenseModifier r2{ goblin };
  //NoBonusesModifier nb{ goblin }; // effectively Command objects

  //root.add(&nb);
  root.add(&r1); // Added r1 to root as next
  root.add(&r1_2); // root has a next, so it calls r1->add and adds r1_2 to r1 as next
  root.add(&r2); // root has a next, so it calls r1->add, r1 has a next, so ti calls r1_2 and adds r2 to r1_2 as next

  root.handle(); // annoying

  cout << goblin << endl;

  //getchar();
  return 0;
}
