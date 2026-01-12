// visitor examples for design patterns c++ book
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

/*
In this example we have the general classes Expression, DoubleExpression and AdditionExpression, which are used to evaluate an expression.

In this example, we want to keep the single resposibility principle, so we decide to move all the printing functionality into a separate class
called ExpressionPrinter. In this class, if we want to have a function for each type of Expression it would not be possible. This is because,
for example, in the print function which takes a AdditionExpression, we need to call "print(ae->left, oss);" to print each operand, but in a 
statically typed language like C++ where we need to determine which function to call at compile time, this would not be possible, since we receive
a pointer and we do not know which kind of object the pointer is pointing to (this would not happen in a dynamically typed language). To be able to do
this, we need to know which kind object we are using, and for that, the simples option is to use a dynamic cast, which is a kind of reflection mechanism 
(even though C++ does not support reflection as other languages).

Now the downsides of this kind of visitor are"
  - the cost of the dynamic cast at runtime.
  - the cost of adding every single child class in the hierarchy
  - the cost of forgetting about some child class

So, this kind of visitor respects the single responsibility pattern, but it is not perfect either.
*/

struct Expression
{
  virtual ~Expression() = default;
};

struct DoubleExpression : Expression
{
  double value;
  explicit DoubleExpression(const double value)
    : value{ value } {}
};

struct AdditionExpression : Expression
{
  Expression *left, *right;

  AdditionExpression(Expression* const left, Expression* const right)
    : left{ left }, right{ right } {}

  ~AdditionExpression()
  {
    delete left;
    delete right;
  }
};

struct ExpressionPrinter
{
  /*void print(DoubleExpression *de, ostringstream& oss) const
  {
    oss << de->value;
  }
  void print(AdditionExpression *ae, ostringstream& oss) const
  {
    oss << "(";
    print(ae->left, oss);
    oss << "+";
    print(ae->right, oss);
    oss << ")";
  }*/
  ostringstream oss;

  void print(Expression *e)
  {
    if (auto de = dynamic_cast<DoubleExpression*>(e))
    {
      oss << de->value;
    } 
    else if (auto ae = dynamic_cast<AdditionExpression*>(e))
    {
      oss << "(";
      print(ae->left);
      oss << "+";
      print(ae->right);
      oss << ")";
    }
  }

  string str() const { return oss.str(); }
};

int main()
{
  auto e = new AdditionExpression{
    new DoubleExpression{ 1 },
    new AdditionExpression{
      new DoubleExpression{ 2 },
      new DoubleExpression{ 3 }
    }
  };
  ostringstream oss;
  //e->print(oss);
  ExpressionPrinter ep;
  ep.print(e);
  cout << ep.str() << endl;
  delete e;
  return 0;
}