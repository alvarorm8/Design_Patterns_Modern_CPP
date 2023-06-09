#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
using namespace boost;
using namespace flyweights;

/*
* Here, the idea is that we have a MMO game, so to store the first name and last name of the users, instead of having strings in the class User, which would waste memory
* when the name is replicated from one user to another, we are using a static map which will store all the different names that are registered.
* 
* So, when a user is registered it will have two indexes to the static map, one for the first name and another for the last name, that way, names are stored only once
* and what is repeated are the indexes.
* 
* Anytime an user is registered, first the system will check whether the name or last name exist and if they do, it will assign the indexes, or if any of it doesn't exist
* the index will be incremented and the new name will be stored in the map.
* 
* Here we are using boost::bimap, which is like an stl map but allows us to search in both ways, if we search the key it will give us the value, and if we look for the value, it will give us the key.
* 
* Since the flyweight pattern is very common, it has been already packaged in libraries so we can use it. In User2 we use boost implementation of the flyweight pattern
*/
// coloring in the console by-letter vs using ranges

// boost.flyweight  

// naive
typedef uint32_t key;

// mmorpg
struct User
{
  User(const string& first_name, const string& last_name)
    : first_name{add(first_name)}, last_name{add(last_name)}
  {
  }

  const string& get_first_name() const
  {
    return names.left.find(last_name)->second;
  }

  const string& get_last_name() const
  {
    return names.left.find(last_name)->second;
  }

  static void info()
  {
    for (auto entry : names.left)
    {
      cout << "Key: " << entry.first << ", Value: " << entry.second << endl;
    }
  }

  friend ostream& operator<<(ostream& os, const User& obj)
  {
    return os
      << "first_name: " << obj.first_name << " " << obj.get_first_name()
      << " last_name: " << obj.last_name << " " << obj.get_last_name();
  }

protected:
  static bimap<key, string> names;
  static int seed;

  static key add(const string& s)
  {
    auto it = names.right.find(s);
    if (it == names.right.end())
    {
      // add it
      key id = ++seed;
      names.insert(bimap<key, string>::value_type(seed, s));
      return id;
    }
    return it->second;
  }
  key first_name, last_name;
};

int User::seed = 0;
bimap<key, string> User::names{};

void naive_flyweight()
{
  User john_doe{ "John", "Doe" };
  User jane_doe{ "Jane", "Doe" };

  cout << "John " << john_doe << endl;
  cout << "Jane " << jane_doe << endl;

  User::info();
}

struct User2
{
  // users share names! e.g., John Smith
  flyweight<string> first_name, last_name;
  //string first_name, last_name;
  // ...

  User2(const string& first_name, const string& last_name) 
    : first_name{ first_name }, last_name{ last_name }
  {
  }
};

void boost_flyweight()
{
  User2 john_doe{ "John", "Doe" };
  User2 jane_doe{ "Jane", "Doe" };

  
  cout << boolalpha <<  (&jane_doe.last_name.get() == &john_doe.last_name.get()) << endl; //compare if the last names are the same object, get gives you the actual object, and we can get its address
  cout << boolalpha <<  (&jane_doe.first_name.get() == &john_doe.first_name.get()) << endl; //compare if the last names are the same object, get gives you the actual object, and we can get its address
  cout << john_doe.first_name << endl; //it prints the actual name, not the object flyweight
}

int main()
{
  std::cout << "///// naive_flyweight /////" << std::endl;
  naive_flyweight();
  std::cout << "///// boost_flyweight /////" << std::endl;
  boost_flyweight();

  //getchar();
  return 0;
}
