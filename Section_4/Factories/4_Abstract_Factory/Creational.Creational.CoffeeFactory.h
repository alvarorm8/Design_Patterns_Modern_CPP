#pragma once
#include <memory>
#include "Creational.Creational.HotDrink.h"
#include "Creational.Creational.HotDrinkFactory.h"

struct HotDrink;

struct CoffeeFactory : HotDrinkFactory
{
  unique_ptr<HotDrink> make() const override
  {
    return make_unique<Coffee>();
  }
};