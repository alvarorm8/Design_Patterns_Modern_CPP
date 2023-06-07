/*
You are given an example of an inheritance hierarchy which results in Cartesian-product duplication.

Please refactor this hierarchy, giving the base class Shape an initializer that takes a Renderer defined as

struct Renderer
{
  virtual string what_to_render_as() const = 0;
}
as well as VectorRenderer and RasterRenderer.

The expectation is that each constructed object has a member called str()  that returns its textual representation, for example,

Triangle(RasterRenderer()).str() // returns "Drawing Triangle as pixels"
*/

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

//Original code until to do:

//struct Shape
//{
//  string name;
//};
//
//struct Triangle : Shape
//{
//  Triangle()
//  {
//    name = "Circle";
//  }
//};
//
//struct Square : Shape
//{
//  Square()
//  {
//    name = "Square";
//  }
//};
//
//struct VectorSquare : Square
//{
//  string str() const
//  {
//    return "Drawing " + name + " as lines";
//  }
//};
//
//struct RasterSquare : Square
//{
//  string str() const
//  {
//    return "Drawing " + name + " as pixels";
//  }
//};

// imagine e.g. VectorTriangle/RasterTriangle etc. here

//to do

struct Renderer
{
  virtual string what_to_render_as() const = 0;
};


struct VectorRenderer : Renderer
{
  string what_to_render_as() const override
  {
    return "lines";
  }
};

struct RasterRenderer : Renderer
{
  string what_to_render_as() const override
  {
    return "pixels";
  }
};

struct Shape
{
  string name;
protected:
  Renderer& renderer; //this is the bridge
  Shape(Renderer& renderer) : renderer{ renderer } {}
public:
  string str() const {
    ostringstream oss;
    oss << "Drawing " << name << " as " << renderer.what_to_render_as();
    return oss.str();
  }
};

struct Triangle : public Shape {
  Triangle(Renderer& renderer) : Shape{ renderer } 
  {
    name = "Triangle";
  }
};

struct Square : public Shape {
  Square(Renderer& renderer) : Shape{ renderer }
  {
    name = "Square";
  }
};

int main() 
{
  RasterRenderer renderer;
  std::cout << Triangle(renderer).str();
  //Triangle(RasterRenderer()).str();
  return 0;
}


