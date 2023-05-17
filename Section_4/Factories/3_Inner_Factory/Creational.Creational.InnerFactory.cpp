#include <cmath>

// do not need this for factory
enum class PointType
{
  cartesian,
  polar
};

/*
* The problem with solution 2_Factory is that it may be hard for the clients to realize they have to use the PointFactory class, they will look at Point class
* and when they see everything is private, they don't know what to do.
* 
* A solution to this is insert the PointFactory class inside Point class, so they can see it and use it. With this, we don't need the friend class, since a inner
* class can access the private members of the outer class.
* 
* Even better, if you make that inner class private, to use it
* we can make use of the singleton pattern, which is, create a static member of PointFactory in Point class and allow clients to use that member.
* 
* This is known as Inner Factory pattern. The static member is optional of course, you could do with PointFactory class public, or make a getFactory method which returns
* an object of the PointFactory class inside Pointm, etc.
*/

class Point
{
  /*Point(float a, float b, PointType type = PointType::cartesian)
  {
  if (type == PointType::cartesian)
  {
  x = a; b = y;
  }
  else
  {
  x = a*cos(b);
  y = a*sin(b);
  }
  }*/

  // use a factory method
  Point(float x, float y) : x(x), y(y) {}

  class PointFactory
  {
    PointFactory() {}
  public:
    static Point NewCartesian(float x, float y)
    {
      return { x,y };
    }
    static Point NewPolar(float r, float theta)
    {
      return{ r*cos(theta), r*sin(theta) };
    }
  };
public:
  float x, y;
  static PointFactory Factory;
};

int main_2()
{
  // will not work
  // Point p{ 1,2 };

  // nope!
  // Point::PointFactory pf;

  // if factory is public, then
  //auto p = Point::PointFactory::NewCartesian(3, 4);

  // at any rate, use this
  auto pp = Point::Factory.NewCartesian(2, 3);

  return 0;
}