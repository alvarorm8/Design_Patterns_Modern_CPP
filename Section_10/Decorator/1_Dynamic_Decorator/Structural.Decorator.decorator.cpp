#include <string>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

/*
* 
* ////////////////////////////////////////////// Dynamic decorator //////////////////////////////////////////////
* Here our original classes are shape, circle and square. 
* 
* Later we want to add a color functionality, for that we are using the dynamic decorator pattern, which aggregates the decorated object as a reference.
* 
* In this case, the new class is ColoredShape, which has a reference to Shape and inherits from it. The same happens with TransparentShape. 
* We are adding new functionalities (color and transparency) to a class without modifying it.
* 
* These classes are used in wrapper function below. The problem with the dynamic decorator is that we don't have access to the methods of the class, for example
* if we define a red_circle as a ColoredShape, we don't have access to the resize function of circle class.
* 
* ////////////////////////////////////////////// Static decorator //////////////////////////////////////////////
* 
* That's why, we can use a static decorator.
* 
* A static decorator uses several tools from C++:
* - mixin inheritance: you can inherit from a template argument (which is not available in other languages)
* - perfect forwarding: in the constructor of the classes (explained below)
* 
* For the static decorator, we define the classes ColoredShape2 and TransparentShape2, which inherit from a template argument T (mixin inheritance).
* Later, we can define the objects like done in the function mixin_inheritance. 
* 
* Here we can call the functions from the base class, like resize, something in the dynamic decorator we couldn't.
* 
* We want to restrict T to be a Shape, so we can use static_assert and type traits, like now, or we can use C++20 concepts (commented above ColoredShape2).
* In the constructor, we want to be able to use something like 
* 
* ColoredShape2<Circle> green_circle{ "green", 5 };
* 
* where green goes to color and 5 goes to the Circle object, for that, we use construct forwarding. We know that the first argument is going to be a string, but the others
* can be anything which goes into the base class from which we inherit (T), so for that, we use a variadic template and pass with std::forward the rest of arguments to the base class
* constructor.
* 
* We can also combine several decorators, like done in the function mixin_inheritance. For example:
* 
* TransparentShape2<ColoredShape2<Circle>> blue_invisible_circle_0{ 0, "blue", 10 };
* 
* After we construct a combined object, we can modify its attributes both from color and transparency, call functions like resize, etc.
* 
* If we forget to pass any argument, like in TransparentShape2<ColoredShape2<Circle>> blue_invisible_circle_0{ 0 };
* 
* We need to have a default constructor, since it would call the constructor of ColoredShape2 and later Circle without any parameter.
* 
* ////////////////////////////////////////////// Functional decorator //////////////////////////////////////////////
* 
* Here we first define the Logger class, which has a name, a std::function and the function operator overloaded, so to use it, we can do it like in the function_decorator function.
* 
* The Logger2 class is the same but with a template argument instead of a std::function. In this case, we cana't use the Logger2 as the Logger class because the template argument deduction does not work, so
* we have to create a helper function called make_logger2.
* 
* If we want to have a Logger which accepts arguments and returns something, the implementation done until now does not work. So we create Logger3 class, which has as a template a return type R and an undetermined 
* number of arguments.
* 
*/

struct Shape
{
  virtual string str() const = 0;
};

struct Circle : Shape
{
  float radius;

  Circle(){}

  explicit Circle(const float radius)
    : radius{radius}
  {
  }

  void resize(float factor)
  {
    radius *= factor;
  }

  string str() const override
  {
    ostringstream oss;
    oss << "A circle of radius " << radius;
    return oss.str();
  }
};

struct Square : Shape
{
  float side;

  Square(){}

  explicit Square(const float side)
    : side{side}
  {
  }

  string str() const override
  {
    ostringstream oss;
    oss << "A square of with side " << side;
    return oss.str();
  }
};

// we are not changing the base class of existing
// objects

// cannot make, e.g., ColoredSquare, ColoredCircle, etc.

struct ColoredShape : Shape
{
  Shape& shape;
  string color;

  ColoredShape(Shape& shape, const string& color)
    : shape{shape},
      color{color}
  {
  }

  string str() const override
  {
    ostringstream oss;
    oss << shape.str() << " has the color " << color;
    return oss.str();
  }
};

struct TransparentShape : Shape
{
  Shape& shape;
  uint8_t transparency;


  TransparentShape(Shape& shape, const uint8_t transparency)
    : shape{shape},
      transparency{transparency}
  {
  }

  string str() const override
  {
    ostringstream oss;
    oss << shape.str() << " has "
      << static_cast<float>(transparency) / 255.f*100.f
      << "% transparency";
    return oss.str();
  }
};

// mixin inheritance

//template <typename T>
//concept IsAShape = std::is_base_of<Shape, T>::value;

//template <IsAShape T> struct ColoredShape2 : T {};

// note: class, not typename
template <typename T> struct ColoredShape2 : T
{
  static_assert(is_base_of<Shape, T>::value,
    "Template argument must be a Shape");

  string color;

  // need this (or not!)
  ColoredShape2(){}

  template <typename...Args>
  ColoredShape2(const string& color, Args ...args)
    : T(std::forward<Args>(args)...), color{color}
    // you cannot call base class ctor here
    // b/c you have no idea what it is
  {
  }

  string str() const override
  {
    ostringstream oss;
    oss << T::str() << " has the color " << color;
    return oss.str();
  }
};

template <typename T> struct TransparentShape2 : T
{
  uint8_t transparency;

  template<typename...Args>
  TransparentShape2(const uint8_t transparency, Args ...args)
    : T(std::forward<Args>(args)...), transparency{ transparency }
  {
  }

  string str() const override
  {
    ostringstream oss;
    oss << T::str() << " has "
      << static_cast<float>(transparency) / 255.f * 100.f
      << "% transparency";
    return oss.str();
  }
};

void wrapper()
{
  Circle circle{ 5 };
  cout << circle.str() << endl;

  ColoredShape red_circle{ circle, "red" };
  cout << red_circle.str() << endl;

  //red_circle.resize(); // oops

  TransparentShape red_half_visible_circle{ red_circle, 128 };
  cout << red_half_visible_circle.str() << endl;
}

void mixin_inheritance()
{
  ColoredShape2<Circle> green_circle_0{ "green", 5 };
  // won't work without a default constructor
  ColoredShape2<Circle> green_circle{ "green" };
  green_circle.radius = 123;
  cout << green_circle.str() << endl;
  green_circle.resize(20);

  TransparentShape2<ColoredShape2<Circle>> blue_invisible_circle_0{ 0, "blue", 10 };
  blue_invisible_circle_0.color = "light blue";
  blue_invisible_circle_0.resize(30);
  
  TransparentShape2<ColoredShape2<Square>> blue_invisible_square{ 0 };
  blue_invisible_square.color = "blue";
  blue_invisible_square.side = 321;
  cout << blue_invisible_square.str() << endl;
}

struct Logger
{
  function<void()> func;
  string name;

  Logger(const function<void()>& func, const string& name)
    : func{func},
      name{name}
  {
  }

  void operator()() const
  {
    cout << "Entering " << name << endl;
    func();
    cout << "Exiting " << name << endl;
  }
};

template <typename Func>
struct Logger2
{
  Func func;
  string name;

  Logger2(const Func& func, const string& name)
    : func{func},
      name{name}
  {
  }

  void operator()() const
  {
    cout << "Entering " << name << endl;
    func();
    cout << "Exiting " << name << endl;
  }
};

template <typename Func> auto make_logger2(Func func, 
  const string& name)
{
  return Logger2<Func>{ func, name }; 
}

// need partial specialization for this to work
template <typename> struct Logger3;

// return type and argument list
template <typename R, typename... Args> 
struct Logger3<R(Args...)>
{
  Logger3(function<R(Args...)> func, const string& name)
    : func{func},
      name{name}
  {
  }

  R operator() (Args ...args)
  {
    cout << "Entering " << name << endl;
    R result = func(args...);
    cout << "Exiting " << name << endl;
    return result;
  }

  function<R(Args ...)> func;
  string name;
};

template <typename R, typename... Args>
auto make_logger3(R (*func)(Args...), const string& name) //here it takes a function pointer, not an std::function
{
  return Logger3<R(Args...)>(
    std::function<R(Args...)>(func),  //we create a std::function from the function pointer
    name);
}

double add(double a, double b)
{
  cout << a << "+" << b << "=" << (a + b) << endl;
  return a + b;
}

void function_decorator()
{
  //Logger([]() {cout << "Hello" << endl; }, "HelloFunction")();
  
  // cannot do this
  //make_logger2([]() {cout << "Hello" << endl; }, "HelloFunction")();
  auto call = make_logger2([]() {cout << "Hello!" << endl; }, "HelloFunction");
  call();

  auto logged_add = make_logger3(add, "Add");
  auto result = logged_add(2, 3);
}

void constructor_forwarding()
{
  struct NotAShape
  {
    virtual string str() const { return string{}; }
  };

  // we don't want this to be legal, thus a static_assert above
  //ColoredShape2<NotAShape> legal;

  // no code completion for this case
  // can comment out argument, too! (default constructor)
  TransparentShape2<Square> hidden_square{ 1, 2 };
  cout << hidden_square.str() << endl;

  ColoredShape2<TransparentShape2<Square>> sq = { "red", 51, 5 };
  cout << sq.str() << endl;
}

int main()
{
  function_decorator();
  //wrapper();
  //mixin_inheritance();
  //constructor_forwarding();

  getchar();
  return 0;
}
