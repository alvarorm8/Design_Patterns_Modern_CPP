/*
Given the provided code, you are asked to implement Line::deep_copy() to perform a deep copy of the current Line object.
Beware memory leaks!
*/

#include <iostream>
#include <memory>

struct Point
{
  int x{ 0 }, y{ 0 };

  Point() {}

  Point(const int x, const int y) : x{ x }, y{ y } {}
};

struct Line
{
  Point* start, * end;

  Line(Point* const start, Point* const end)
    : start(start), end(end)
  {
    std::cout << "Calling Line constructor!!" << std::endl;
    std::cout << "start address: " << start << std::endl;
    std::cout << "end address: " << start << std::endl;
  }

  ~Line()
  {
    std::cout << "Calling Line destructor!!" << std::endl;
    delete start;
    delete end;
  }

  Line deep_copy() const
  {
    return { new Point{start->x, start->y}, new Point{end->x, end->y} };
  }
};

int main() {
  Line l1{ new Point{}, new Point{4,5} };
  auto l2 = l1.deep_copy();
}