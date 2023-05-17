#include <cmath>

enum class PointType
{
  cartesian,
  polar
};

/*
* Here the idea is the same as in the 1_Factory_Method solution, but we move the construction of the objects to a different class called Factory.
* We have to define it as friend class of Point which would break the Open Close Principle since we're modifying the class after its creation.
* 
* If we don't want to break it, we can make the constructor public to not break. 
* 
* Personally I think is better to break the OCP since it is a minimum change.
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
  Point(float x, float y) : x(x), y(y){}
public:
  float x, y;

  friend class PointFactory;
};

class PointFactory
{
  //static functions is totally optional
  static Point NewCartesian(float x, float y)
  {
    return Point{ x,y };
  }

  static Point NewPolar(float r, float theta)
  {
    return Point{ r*cos(theta), r*sin(theta) };
  }
};
