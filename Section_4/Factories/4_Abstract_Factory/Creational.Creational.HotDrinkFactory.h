#pragma once
#include "Creational.Creational.HotDrink.h"

struct HotDrinkFactory
{
  virtual unique_ptr<HotDrink> make() const = 0;
};