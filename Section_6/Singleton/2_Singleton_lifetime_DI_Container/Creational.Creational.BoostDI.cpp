#include "Creational.Creational.di.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

/*
* Instead of defining manually the singleton hiding the constructor and creating the get method, you can rely on an inversion of control container
* used in a typical dependency injection framework. Basically, it creates a singleton for you. In DI containers you configure differents components with
* different lifetimes, and singleton is a lifetime specification that only one component exists at one time.
* 
* The DI container used here is boost/di.h
* 
* The code of Engine, ILogger, ConsoleLogger and Car does not appear on the video, IFoo, Foo and Bar is what he shows.
* 
* Here we use boost::di to create a singleton of Foo that is shared between Bar's instances. When we print the id, is 1 in both instances and the address is the same.
*/

using std::make_unique;
using std::make_shared;

struct Engine
{
  float volume = 5;
  int horse_power = 400;

  friend std::ostream& operator<<(std::ostream& os, const Engine& obj);
};

std::ostream& operator<<(std::ostream& os, const Engine& obj)
{
    return os
        << "volume: " << obj.volume
        << " horse_power: " << obj.horse_power;
}

struct ILogger
{
  virtual ~ILogger()
  {
  }

  virtual void Log(const std::string& s) = 0;
};

struct ConsoleLogger : ILogger
{
  ConsoleLogger()
  {
  }

  void Log(const std::string& s) override
  {
    std::cout << "LOG:" << s.c_str() << std::endl;
  }
};

struct Car
{
  std::unique_ptr<Engine> engine;
  std::shared_ptr<ILogger> logger;

  Car(std::unique_ptr<Engine> engine, const std::shared_ptr<ILogger>& logger)
    : engine{move(engine)},
      logger{logger}
  {
    logger->Log("making a car");
  }
  friend std::ostream& operator<<(std::ostream& os, const Car& obj);
};

std::ostream& operator<<(std::ostream& os, const Car& obj)
{
return os << "car with engine: " << *obj.engine;
}

struct IFoo {
    virtual std::string name() = 0;
};

struct Foo : IFoo {
    static int id;
    Foo() { ++id; }
    std::string name() override {
        return "foo " + std::to_string(id);
    }
};

int Foo::id = 0;

struct Bar {
    std::shared_ptr<IFoo> foo;
};

int main()
{
  // manual
  auto logger = make_shared<ConsoleLogger>();
  auto c = make_shared<Car>(make_unique<Engine>(),logger);

  using namespace boost;
  auto injector = di::make_injector(
    di::bind<ILogger>().to<ConsoleLogger>()
  );
  auto car = injector.create<std::shared_ptr<Car>>();

  std::cout << *car << std::endl;

  //////////////////

  auto injector2 = di::make_injector(
      di::bind<IFoo>().to<Foo>().in(di::singleton) //whenever anyone asks for an IFoo, is maped to Foo and its lifetime is singleton
  );

  auto bar1 = injector2.create<std::shared_ptr<Bar>>();
  auto bar2 = injector2.create<std::shared_ptr<Bar>>();

  std::cout << bar1->foo->name() << std::endl;
  std::cout << bar2->foo->name() << std::endl;

  std::cout << boolalpha << (bar1->foo.get() == bar2->foo.get()) << std::endl;

  getchar();
  return 0;
}
