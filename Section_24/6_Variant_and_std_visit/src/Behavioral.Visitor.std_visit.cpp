#include <variant>
#include <iostream>

using namespace std;

/*
In this example we are using the std::variant to create a visitor pattern. 

std::variant is used to replace the old way of having a class which can have defined one field or the other field, for example if we have an union.

In the main example house can be defined as a number or as a string, and only can be defined as one or another at a specific time.

For accessing the part of house which is actually been assigned, is not so simple as accessing a boolean, we need to implement the visitor pattern, but slightly different one.

In modern C++ the typical way of doing it is using std::visit, where you pass as argument a callable (the visitor itself) and the object you want to visit.
We can define the visitor as a class, like AddressPrinter, or as a lambda function.

In the AddressPrinter you need to define the operator (), and at compile time it checks that you have all the possible cases for the variant implemented.

In the case of the lambda function, we define the argument as auto, since we don't know which kind of argument we receive.
Later, we see which kind of argument we have with "using T = decay_t<decltype(arg)>;", and later we use "if constexpr" to check which option to execute.
*/

struct AddressPrinter
{
  void operator()(const string& house_name) const {
    cout << "A house called " << house_name << "\n";
  }

  void operator()(const int house_number) const {
    cout << "House number " << house_number << "\n";
  }
};

int main(int ac, char* av[])
{
  variant<string, int> house;
  //house = "Montefiore Castle";
  house = 221;

  AddressPrinter ap;
  std::visit(ap, house);

  // what if you want to create a visitor in-place?
  std::visit([](auto& arg) {
    using T = decay_t<decltype(arg)>;

    if constexpr (is_same_v<T, string>)
    {
      cout << "A house called " << arg.c_str() << "\n";
    }
    else
    {
      cout << "House number " << arg << "\n";
    }
  }, house);

  return 0;
}