#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <boost/lexical_cast.hpp>
#include <vector>

/*
* NOTE: GoogleTest library is used here, which construction is explained in GTest.md at repository root.
* 
* Here we are going to read a database with capitals and population. For that, we create the SingletonDataBase class, 
* whose constructor is private. Also, we have to delete the copy constructor and the assignment operator so no one can 
* create another instance of it.
* 
* To create an instante, we have the get method, which returns a reference to the object created inside the method as a static
* variable, so only one is created.
* 
* To use it, we can do it like: SingletonDatabase::get().get_population("Tokyo");
* 
* Lets supose later we create a class like SingletonRecordFinder and we want to test it. We do this at SingletonTests.cpp.
* 
* The problem in SingletonTotalPopulationTest is that we are strictly bounded to the production database, so it is not an unit test, but an integration test,
* since we wanted to test the SingletonRecordFinder method but we had to test also the database operations. This is also dangerous since the database might change
* at if it does not have Mexico City for example, the test will fail.
* 
* To solve this problem, we can use the Dependency Injection Principle so we don't depend on the real database. To do that, we can create a dummy database where we can inject
* data to pass the test. First, we create the Database class which will be the base class of all classes which implement databases (SingletonDatabase, DummyDatabase, etc.).
* 
* This base class will have the method get_population that all derived classes will implement. 
* 
* Second, we implement DummyDatabase which will have a set of data we know and it won't change, like the real database could.
* 
* Later, we create a class to test the operations which unlike SingletonRecordFinder will accept a reference to the base class, this will be ConfigurableRecordFinder.
* With it, we can now make a unit test without having the bound to the real database, since we can pass an object of the DummyDatabase, this will be DependantTotalPopulationTest.
* 
* So, the singleton problem, which is the hard link to the real database, has been resolved throughout the interface Database, applying the Dependency Injection Principle.
*/

class Database
{
public:
  virtual int get_population(const std::string& name) = 0;
};

class SingletonDatabase : public Database
{
  SingletonDatabase()
  {
    std::cout << "Initializing database" << std::endl;

    std::ifstream ifs("capitals.txt");

    std::string s, s2;
    while (getline(ifs, s))
    {
      getline(ifs, s2);
      int pop = boost::lexical_cast<int>(s2);
      capitals[s] = pop;
    }
    //instance_count++;
  }

  std::map<std::string, int> capitals;

public:
  //static int instance_count;

  SingletonDatabase(SingletonDatabase const&) = delete;
  void operator=(SingletonDatabase const&) = delete;

  static SingletonDatabase& get()
  {
    //when we define a static variable inside a function, is like doing it outside the function but the scope is only in the function,
    //this means the variable db has a application lifetime, it is not destroyed when the function ends. That's why when we call several 
    //times to get() only one instance of SingletonDatabase is created.
    static SingletonDatabase db;
    return db;
  }

  int get_population(const std::string& name) override
  {
    return capitals[name];
  }

  /*
  static SingletonDatabase* get_instance()
  {
    if (!instance)
      instance = new SingletonDatabase;
    return instance; // atexit
  }
  */
};

//int SingletonDatabase::instance_count = 0;

class DummyDatabase : public Database
{
  std::map<std::string, int> capitals;
public:


  DummyDatabase()
  {
    capitals["alpha"] = 1;
    capitals["beta"] = 2;
    capitals["gamma"] = 3;
  }

  int get_population(const std::string& name) override {
    return capitals[name];
  }
};

struct SingletonRecordFinder
{
  int total_population(std::vector<std::string> names)
  {
    int result = 0;
    for (auto& name : names)
      result += SingletonDatabase::get().get_population(name);
    return result;
  }
};

struct ConfigurableRecordFinder
{
  explicit ConfigurableRecordFinder(Database& db)
    : db{db}
  {
  }

  int total_population(std::vector<std::string> names) const
  {
    int result = 0;
    for (auto& name : names)
      result += db.get_population(name);
    return result;
  }

  Database& db;
};