#include <map>
#include <memory>
#include <iostream>
using namespace std;

/*
* The multiton is a variation of the singleton pattern but is not directly linked to it.
* 
* This variation sets up the kind of key value store where you can optionally restrict the number of elements which are included to the store
* and given out to the client.
* 
* First we have to define the range of values to use as key, you can use enum class (like Importance here), ints, etc.
* 
* Now we construct a singleton construct that construct an instance for each one of the key values.
* 
* In Multiton class, we have a map with keys and shared_ptr pointers, that will be the store. And then we have the function get
* which will give us the correspondant pointer based in the key passed, or if it does not exist, we create a new one and store into the map.
* 
* The multiton is not meant to be instantiated, but to be used through its get member.
* 
* When we try to create a second instance of the secondary key, it's not created, there will be only one.
*/

enum class Importance
{
  primary,
  secondary,
  tertiary
};

template <typename T, typename Key = std::string>
class Multiton
{
public:
  static shared_ptr<T> get(const Key& key)
  {
    if (const auto it = instances.find(key);
        it != instances.end())
    {
      return it->second;
    }

    auto instance = make_shared<T>();
    instances[key] = instance;
    return instance;
  }
protected:
  Multiton() = default;
  virtual ~Multiton() = default;
private:
  static map<Key, shared_ptr<T>> instances;
};

template <typename T, typename Key>
map<Key, shared_ptr<T>> Multiton<T, Key>::instances;

class Printer
{
public:
  Printer()
  {
    ++Printer::totalInstanceCount;
    cout << "A total of " <<
      Printer::totalInstanceCount <<
      " instances created so far\n";
  }
private:
  static int totalInstanceCount;
};
int Printer::totalInstanceCount = 0;

int main()
{
  typedef Multiton<Printer, Importance> mt;

  auto main = mt::get(Importance::primary);
  auto aux = mt::get(Importance::secondary);
  auto aux2 = mt::get(Importance::secondary);
}