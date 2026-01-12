// visitor examples for design patterns c++ book
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

/*
In this example we have the general classes Expression, DoubleExpression and AdditionExpression, which are used to evaluate an expression.

Here we are going to use the double dispatch (dispatch refers to the process of knowing which piece of code has to be executed), since in C++ is impossible
to perform a dispatch in a single step at compile time when dealing with pointers (like in the expression "print(ae->left);" from the reflective visitor). We need to force
the system to check which kind of object the pointer is pointing to. Is not the best approach, but it is acceptable.

For that, in the base class Expression we define a method called accept (is a convention to call it like this in the double dispatch mechanism). In this method, we use a 
visitor class, which is able to visit every element of the class hierarchy (DoubleExpression, AdditionExpression, etc.). We have a base class called ExpressionVisitor, with a method
called visit (another convention in the visitor pattern) for each kind of child class in the hierarchy (DoubleExpression, AdditionExpression, etc.). Now, for each functionality we 
want to perform in the visit function, we define a child class of ExpressionVisitor, like ExpressionPrinter and ExpressionEvaluator.

Now, they way the invocation of the correct method happens is with a double hop. In the accept methods we always call "visitor->visit(this);" and inside the visit method (the correct visit method
to call is determined at runtime depending on the type of the visitor object the pointer is pointing to) we perform the operations we want to do.
Now the trick here, and the reason why we can not implement the accept method in the base class, is the type of the "this" pointer used in each accept method. We need to know at compile time which type of object we
pass to the visit method (so the correct visit method is called), and for that, we need to implement the function accept in each one of the child classes.

This explained before is the double dispatch mechanism, which respects the single responsibility principle and the open close principle, but it is not a perfect solution. This would also be called cyclic visitor, which is based
on function overloading. The main problem of this approach is that it only works is you have a stable hierarchy of classes with an inheritance approach which forces the presence of the accept method.
*/

struct SubtractionExpression;
struct DoubleExpression;
struct AdditionExpression;

struct ExpressionVisitor
{
  virtual void visit(DoubleExpression* de) = 0;
  virtual void visit(AdditionExpression* ae) = 0;
  virtual void visit(SubtractionExpression* se) = 0;
};

struct ExpressionPrinter : ExpressionVisitor
{
  ostringstream oss;
  string str() const { return oss.str(); }
  void visit(DoubleExpression* de) override;
  void visit(AdditionExpression* ae) override;
  void visit(SubtractionExpression* se) override;
};

struct ExpressionEvaluator : ExpressionVisitor
{
  double result;
  void visit(DoubleExpression* de) override;
  void visit(AdditionExpression* ae) override;
  void visit(SubtractionExpression* se) override;
};

struct Expression
{
  virtual void accept(ExpressionVisitor* visitor) = 0;
};

struct DoubleExpression : Expression
{
  double value;
  explicit DoubleExpression(const double value)
    : value{ value } {}

  void accept(ExpressionVisitor* visitor) override
  {
    visitor->visit(this);
  }
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

  void accept(ExpressionVisitor* visitor) override
  {
    visitor->visit(this);
  }
};

struct SubtractionExpression : Expression
{
  Expression *left, *right;

  SubtractionExpression(Expression* const left, Expression* const right)
    : left{ left }, right{ right } {}

  ~SubtractionExpression()
  {
    delete left;
    delete right;
  }

  void accept(ExpressionVisitor* visitor) override
  {
    visitor->visit(this);
  }
};

void ExpressionPrinter::visit(DoubleExpression* de)
{
  oss << de->value;
}

void ExpressionPrinter::visit(AdditionExpression* e)
{
  bool need_braces = dynamic_cast<SubtractionExpression*>(e->right);
  e->left->accept(this);
  oss << "+";
  if (need_braces) oss << "(";
  e->right->accept(this);
  if (need_braces) oss << ")";
}

void ExpressionPrinter::visit(SubtractionExpression* se)
{
  bool need_braces = dynamic_cast<SubtractionExpression*>(se->right);
  if (need_braces) oss << "(";
  se->left->accept(this);
  oss << "-";
  se->right->accept(this);
  if (need_braces) oss << ")";
}

void ExpressionEvaluator::visit(DoubleExpression* de)
{
  result = de->value;
}

void ExpressionEvaluator::visit(AdditionExpression* ae)
{
  ae->left->accept(this); // evaluate part
  auto temp = result;
  ae->right->accept(this); // evaluate part
  result = temp + result;
}

void ExpressionEvaluator::visit(SubtractionExpression* se)
{
  se->left->accept(this);
  auto temp = result;
  se->right->accept(this);
  result = temp - result;
}

int main()
{
  auto e = new AdditionExpression{
    new DoubleExpression{ 1 },
    new SubtractionExpression {
      new DoubleExpression{ 2 },
      new DoubleExpression{ 3 }
    }
  };
  ostringstream oss;
  ExpressionPrinter printer;
  ExpressionEvaluator evaluator;
  printer.visit(e);
  evaluator.visit(e);
  cout << printer.str() << " = " << evaluator.result << endl;
  delete e;
  return 0;
}
