#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <memory>
using namespace std;
#include <boost/lexical_cast.hpp>

/*
The idea is that we have a expression like this one string input{ "(13-4)-(12+1)" }; and we want to split it into separate tokens. And these tokens would be, for example, 
the opening round bracket, then the value 13, then the minus, then the value 4 and so on and so forth.

We're going to start by defining the kind of tokens that we can have in our system. Defined in Token structure. We're also going to have the text of the token itself.
And the reason why we want this is because, for example, if you have an integer, just knowing that it's an integer isn't enough to tell you what kind of integer it is,
what kind of value it actually has.

Second, we define the function lex which defines the process of lexing.

Now it's turn of the parsing section. We want to go through the tokens one by one, and we want to build an actual expression that we can hopefully evaluate.

So in order to define this, we're going to be defining some object oriented structures. And I'll define some abstract base class for the kind of things that we're going to have.

We start with the base class Element, and for each one of the Token types, we inherit this class and implement the eval method, like Integer and BinaryOperation.
Notice that the parentheses, they simply give us hints as to how the operations all involve one another. They don't actually show up anywhere by themselves.
So we certainly have to take care of the parentheses. That's going to be one of the challenges when parsing, but they don't make any appearance in the actual
code that we defined for the parsing structures.

Now, we define the parse function. The result in the example string is going to be a BinaryOperation, since the root of the operation is a + or a -.

Even for such a small interpreter, you can see that we've had to do quite a bit of work to actually separate the tokens that would be the Lexing part
and then turn those tokens into some sort of object oriented structure. That would be the parsing part.


*/

// lexing =================================================

struct Token
{
  enum Type { integer, plus, minus, lparen, rparen } type;
  string text;

  explicit Token(Type type, const string& text) :
    type{type}, text{text} {}

  friend ostream& operator<<(ostream& os, const Token& obj)
  {
    return os << "`" << obj.text << "`";
  }
};

vector<Token> lex(const string& input)
{
  vector<Token> result;

  for (int i = 0; i < input.size(); ++i)
  {
    switch (input[i])
    {
    case '+':
      result.push_back(Token{ Token::plus, "+" });
      break;
    case '-':
      result.push_back(Token{ Token::minus, "-" });
      break;
    case '(':
      result.push_back(Token{ Token::lparen, "(" });
      break;
    case ')':
      result.push_back(Token{ Token::rparen, ")" });
      break;
    default:
      // number
      ostringstream buffer;
      buffer << input[i];
      for (int j = i + 1; j < input.size(); ++j)
      {
        if (isdigit(input[j]))
        {
          buffer << input[j];
          ++i;
        }
        else
        {
          result.push_back(Token{ Token::integer, buffer.str() });
          break;
        }
      }
      if (!buffer.str().empty()) // 20201210
        result.push_back(Token{ Token::integer, buffer.str() });
    }
  }

  return result;
}

// parsing =====================================================

struct Element
{
  virtual ~Element() = default;
  virtual int eval() const = 0;
};

struct Integer : Element
{
  int value;
  explicit Integer(const int value)
    : value(value)
  {
  }
  int eval() const override { return value; }
};

struct BinaryOperation : Element
{
  enum Type { addition, subtraction } type;
  shared_ptr<Element> lhs, rhs;

  int eval() const override
  {
    if (type == addition) 
      return lhs->eval() + rhs->eval();
    return lhs->eval() - rhs->eval();
  }
};

unique_ptr<Element> parse(const vector<Token>& tokens)
{
  auto result = make_unique<BinaryOperation>();
  bool have_lhs = false;
  for (size_t i = 0; i < tokens.size(); i++)
  {
    auto& token = tokens[i];
    switch(token.type)
    {
    case Token::integer:
    {
      int value = boost::lexical_cast<int>(token.text);
      auto integer = make_shared<Integer>(value);
      if (!have_lhs) {
        result->lhs = integer;
        have_lhs = true;
      }
      else result->rhs = integer;
    }
      break;
    case Token::plus: 
      result->type = BinaryOperation::addition;
      break;
    case Token::minus:
      result->type = BinaryOperation::subtraction;
      break;
    case Token::lparen: 
    {
      int j = i;
      for (; j < tokens.size(); ++j)
        if (tokens[j].type == Token::rparen)
          break; // found it!

      vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
      auto element = parse(subexpression);
      if (!have_lhs) 
      {
        result->lhs = move(element);
        have_lhs = true;
      }
      else result->rhs = move(element);
      i = j; // advance
    }
    break;
    }
  }
  return result;
}



int main()
{
  string input{ "(14-4)+11" }; // see if you can make nested braces work
  auto tokens = lex(input);

  // let's see the tokens
  for (auto& t : tokens)
    cout << t << "   ";
  cout << endl;

  try {
    auto parsed = parse(tokens);
    cout << input << " = " << parsed->eval() << endl;
  } 
  catch (const exception& e)
  {
    cout << e.what() << endl;
  }

  return 0;
}
