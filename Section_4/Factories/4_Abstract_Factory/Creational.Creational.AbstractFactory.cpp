#include <iostream>

#include <memory>
#include <map>
#include "Creational.Creational.HotDrink.h"
#include "Creational.Creational.DrinkFactory.h"
using namespace std;

/*
* Until now, all the previous sections are variations of the Factory Method pattern, now we're looking into the Abstract Factory pattern, which uses inheritance to 
* build a family of factories.
* 
* We start with the HotDrink.h file, which has the interface and the implementation of the classes we want to construct, in this case, HotDrink is the interface and Coffee and Tea
* are the implementations of that interface.
* 
* After that we create the factory for Hot Drink as a interface (Abstract Factory is HotDrinkFactory) and create Tea and Coffee factories inheriting from HotDrinkFactory.
* 
* Once we have these factories created, we have to create another file which will have the classes to keep track of the factories we have created, in this case, DrinkFactory.h.
* It is like a facilitator for using all the factories we have created and exposing them in a map or something similar.
* 
* In this case, we create DrinkFactory class, which stores a map with as many entries as factories created (TeaFactory and CoffeeFactory) and a method which uses those
* entries to the map to call polymorphically the functions in the factories.
* 
* Another aproach to this implementation instead of using an OO approach, we can use a more functional approach with lambdas. This is done in the DrinkWithVolumeFactory class.
* 
* In this class, the map contains a string and a function which returns a unique_ptr of a HotDrink, we don't need to use the HotDrinkFactories in this case.
* This way, in the constructor, we can define each one of the lambdas for each one of the classes we want to build (Tea and Coffee). 
* Later, we have a function to use this map which will call the elements in the map with the function operator () to call the specific lambda.
*/


// This is the way we would work with the classes if we don't have a Factory Pattern, but here we can use DrinkFactory.
unique_ptr<HotDrink> make_drink(string type)
{
  unique_ptr<HotDrink> drink;
  if (type == "tea")
  {
    drink = make_unique<Tea>();
    drink->prepare(200);
  }
  else 
  {
    drink = make_unique<Coffee>();
    drink->prepare(50);
  }
  return drink;
}

int main()
{
  std::cout << "<<<<<<<<<<<<<<<<<<< Using a basic approach with ifs >>>>>>>>>>>>>>>>>>>>>>>\n\n";
  auto d = make_drink("tea");

  std::cout << "<<<<<<<<<<<<<<<<<<< Using an Abstract Factory with OO approach >>>>>>>>>>>>>>>>>>>>>>>\n\n";
  DrinkFactory df;
  df.make_drink("coffee");

  std::cout << "<<<<<<<<<<<<<<<<<<< Using an Abstract Factory with function approach >>>>>>>>>>>>>>>>>>>>>>>\n\n";
  DrinkWithVolumeFactory dff;
  dff.make_drink("tea");

  getchar();
  return 0;
}