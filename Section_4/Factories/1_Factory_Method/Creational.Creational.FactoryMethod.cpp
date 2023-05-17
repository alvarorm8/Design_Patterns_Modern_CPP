//#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

enum class PointType
{
  cartesian,
  polar
};

class Point
{
  /*
  Here the basic implementation is not sufficient to know what a and b are, for example in polar coordinates if a is rho o theta, 
  even though we can add documentation, is not enough to be a good constructor. Furthermore, we don't want to use a lot of parameters
  like PointType, since the constructor this way can become really big and hard to understand.

  Also if we want to have different methods called PointFromCartesian and PointFromPolar we can not since the constructor has to be named
  as the class, so there's a problem here.

  Point(float a, float b, PointType type = PointType::cartesian)
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

  /*
  * For the Factory Method we have to put the constructor as private, and then, add static functions which creates objects using the private constructor of the class with the 
  * specific implementation we want to use. In this case, those would be NewCartesian and NewPolar functions.
  */
  Point(const float x, const float y)
    : x{x},
      y{y}
  {
  }

public:
  float x, y;


  friend std::ostream& operator<<(std::ostream& os, const Point& obj)
  {
    return os
      << "x: " << obj.x
      << " y: " << obj.y;
  }

  static Point NewCartesian(float x, float y)
  {
    return{ x,y };
  }
  static Point NewPolar(float r, float theta)
  {
    return{ r*cos(theta), r*sin(theta) };
  }
};

int main_z()
{
  // will not work
  //Point p{ 1,2 };

  auto p = Point::NewPolar(5, M_PI_4);
  std::cout << p << std::endl;

  getchar();
  return 0;
}