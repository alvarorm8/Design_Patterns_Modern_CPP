#include "headers.hpp"
#include "Observer.hpp"
#include "SaferObservable.hpp"

/*
Here we have the person class and we want to be informed each time the age of the person changes.

In the observer files we implement the observer base class which is interested in receiving the notifications when the age changes.
In this file we implement several observers: ConsolePersonObserver and TrafficAdministration.

In the observable files we implement the observable base class, which has several functions: the subscribe and unsubscribe to register and delete
observers, and the notify function notify to the observers. The Person class at the beginning inherits from it.

In the class Person2 we implement the same observable using boost:signals2 library. For this, we don't need to create an observer, since we can directly subscribe to the 
observable using a lambda function. This connection is saved to an object, and you can also unsubscribe using that object. The problem with the signals library is that it is
not thread safe, so we need to be cautious on its use.

The problem with this class is that it is not safe for concurrency, since if several observers subscribe to it at the same time, we can get a core dump due to 
several objects accessing the same resource (vector of observers) at the same time. For this reason, the SaferObservable class is created which has a mutex to protect
the memory.

The problem using a normal mutex is if we enter a SaferObservable function inside another SaferObservable function, for example, if we unsusbcribe inside a notification
(SaferObservable notify function -> goes to Observer field_changed function -> goest to SaferObservable unsubscribe function). This happens in the TrafficAdministration
observer, which only interested in people are too young to drive. The problem is that we alredy have a lock from the notify function, and now we are creating another one 
in the unsubscribe function with the same mutex, which causes a segmentation fault since the mutex is already in use. To fix this, we have two options:

- The first one is in the unsubscribe function to avoid modifying the vector. Instead we find the iterator (only available if we use vector, std::set for example can not do it)
and we put it into nullptr. In the notify function, we need to check that the element of the vector is not nullptr.

- The second one is to use recursive_mutex, which has some drawbacks, but it fixes our problem here.
*/

// observable

class Person : public SaferObservable<Person>
{
  int age{0};
public:
  Person(){}
  Person(int age) : age(age) {}

  int get_age() const
  {
    return age;
  }

  void set_age(int age)
  {
    if (this->age == age) return;

    auto old_can_vote = get_can_vote();
    this->age = age;
    notify(*this, "age");

    if (old_can_vote != get_can_vote())
      notify(*this, "can_vote");
  }

  bool get_can_vote() const {
    return age >= 16;
  }
};

template <typename T> struct Observable2{
  boost::signals2::signal<void(T&, const string&)> field_changed;
};

class Person2 : public Observable2<Person2>{
    int age;
  public:

    int get_age() const
    {
      return age;
    }

    void set_age(int age)
    {
      if (this->age == age) return;
      this->age = age;
      field_changed(*this, "age");
    }
};

// observers

struct ConsolePersonObserver
  : public Observer<Person>
{
private:
  void field_changed(Person &source, const std::string &field_name) override
  {
    cout << "Person's " << field_name << " has changed to ";
    if (field_name == "age") cout << source.get_age();
    if (field_name == "can_vote")
      cout << boolalpha << source.get_can_vote();
    cout << ".\n";
  }
};

struct TrafficAdministration : Observer<Person>
{
  void field_changed(Person &source, const std::string &field_name) override
  {
    if (field_name == "age")
    {
      if (source.get_age() < 17)
        cout << "Whoa there, you're not old enough to drive!\n";
      else
      {
        cout << "Oh, ok, we no longer care!\n";
        source.unsubscribe(*this);
      }
    }
  }
};

int main(int ac, char* av[])
{
  Person p;
  TrafficAdministration ta;
  p.subscribe(ta);

  p.set_age(15);
  p.set_age(16);
  try
  {
    p.set_age(17);
  }
  catch (const std::exception& e)
  {
    cout << "Oops, " << e.what() << "\n";
  }

  Person2 p2;
  auto conn = p2.field_changed.connect([](Person2& p, const std::string field_name){
    cout << field_name << " has changed to " << p.get_age() << "\n";
  });
  p2.set_age(20);

  conn.disconnect();

  p2.set_age(22); // this one is not received, since we disconnected.

  return 0;
}