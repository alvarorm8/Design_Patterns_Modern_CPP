#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/*
In this example we have the general classes Expression, DoubleExpression and AdditionExpression, which are used to evaluate an expression.

Here we are going to use the acyclic visitor, based on RTTI (Run-Time Type Information), so it is significantly slower, but has the benefit that does not put any limitation on hierarchies.

It starts with the definition of the Visitor base class, which has a function to visit any kind of object.
After that, we define the VisitorBase as a marker interface. We can't leave it empty since we need vtables to be created, so we need to define an empty destructor. This class is later used as 
argument in the accept functions.

In the accept methods of the different Expressions classes (included the base class) what we do is we ensure that the visitor object that we receive is of the type that knows how to accept an Expression, 
DoubleExpression, AdditionExpression, etc., respectively in each class. For that, we use the dynamic cast with the class Visitor, which ensure that the object is visitable for the type we have (Expression, etc.).
If this is correct, then we call the visit function.

In the ExpressionPrinter class, we inherit from the VisitorBase class (so it can be used in the accept functions) and from Visitor of all kind of classes in the hierarchy (Expression, 
DoubleExpression, AdditionExpression, etc.). Inside of it, we define a visit function for each type of the hierarchy (The one for the base class (Expression) does not do anything,
but it serves as a fallback (not explained in the class)). In this approach, if we don't have yet a visit function defined for a child class (we simulate it commenting the DoubleExpression implementation),
then the program would not crash, since the cast inside of the accept method would fail, but the program would continue its execution.
*/

template <typename Visitable>
struct Visitor
{
  virtual void visit(Visitable& obj) = 0;
};

struct VisitorBase // marker interface
{
  virtual ~VisitorBase() = default;
};

struct Expression
{
  virtual ~Expression() = default;

  virtual void accept(VisitorBase& obj)
  {
    using EV = Visitor<Expression>;
    if (auto ev = dynamic_cast<EV*>(&obj))
      ev->visit(*this);
  }
};

struct DoubleExpression : Expression{
  double value;

  DoubleExpression(double value) : value(value) {}

  virtual void accept(VisitorBase& obj)
  {
    using DEV = Visitor<DoubleExpression>;
    if (auto ev = dynamic_cast<DEV*>(&obj))
      ev->visit(*this);
  }
};

struct AdditionExpression : Expression
{
  Expression *left, *right;

  AdditionExpression(Expression *left, Expression *right) : left(left), right(right) {}

  ~AdditionExpression()
  {
    delete left;
    delete right;
  }

  virtual void accept(VisitorBase& obj)
  {
    using AEV = Visitor<AdditionExpression>;
    if (auto ev = dynamic_cast<AEV*>(&obj))
      ev->visit(*this);
  }
};

struct ExpressionPrinter : VisitorBase,
                           Visitor<Expression>,
                           //Visitor<DoubleExpression>,
                           Visitor<AdditionExpression>
{
  void visit(Expression &obj) override
  {
    // fallback?
  }

  // can remove double visitor without failure
//  void visit(DoubleExpression &obj) override
//  {
//    oss << obj.value;
//  }

  void visit(AdditionExpression &obj) override
  {
    oss << "(";
    obj.left->accept(*this);
    oss << "+";
    obj.right->accept(*this);
    oss << ")";
  }

  string str() const { return oss.str(); }
private:
  ostringstream oss;
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

  ExpressionPrinter ep;
  ep.visit(*e);
  cout << ep.str() << "\n";
	return 0;
}
