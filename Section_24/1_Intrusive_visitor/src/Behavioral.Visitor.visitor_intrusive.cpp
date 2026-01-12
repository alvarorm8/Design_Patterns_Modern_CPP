// visitor examples for design patterns c++ book
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

/*
In this example we have the general classes Expression, DoubleExpression and AdditionExpression, which are used to evaluate an expression.

Later, we want to print the expression (not evaluate yet), in this case we are going to assume we can break the open close principle, so 
we add the print function in the base class Expression, and implement it in the child classes.

This kind of visitor is called intrusive visitor, since it takes the original classes and it modifies them. In this case is possible since there are
only 3 classes, but if we had 20, 40 classes, it would be impossible. Also, in this kind of visitor the single resposibility principle is broken,
since the printing is a separate function from the addition.
*/

struct Expression
{
  virtual void print(ostringstream& oss) = 0;
};

struct DoubleExpression : Expression
{
  double value;
  explicit DoubleExpression(const double value)
    : value{value} {}

  void print(ostringstream& oss) override
  {
    oss << value;
  }
};

struct AdditionExpression : Expression
{
  Expression *left, *right;

  AdditionExpression(Expression* const left, Expression* const right)
    : left{left}, right{right} {}

  ~AdditionExpression()
  {
    delete left;
    delete right;
  }

  void print(ostringstream& oss) override
  {
    oss << "(";
    left->print(oss);
    oss << "+";
    right->print(oss);
    oss << ")";
  }
};

int main()
{
  auto e = new AdditionExpression{
    new DoubleExpression{1},
    new AdditionExpression{
      new DoubleExpression{2},
      new DoubleExpression{3}
    }
  };
  ostringstream oss;
  e->print(oss);
  cout << oss.str() << endl;
  delete e;
  return 0;
}