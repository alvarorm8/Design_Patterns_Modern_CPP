#include <iostream>
#include <string>
#include <vector>
using namespace std;

// two classes of objects

// Renderers - determine how an object is drawn
// Shapes - determine what to draw

/*
* If we have 2 types of renderers and 2 types of shapes (circle, rectangle, and raster and vector, for example), in a normal implementation we would have to define
* 2x2 renderes (RasterCircleRenderer, RasterRectangleRenderer, VectorCircle...), if we have 3 and 3, we would have to define 9, so this is the "Cartesian Product" complexity explosion.
* 
* To avoid this, we use the bridge pattern through interfaces (abstraction).
* 
* We start with Renderer class which is the general interface (in this case only for circles, but it could be for more shapes), and 
* then we inherit it in VectorRenderer and RasterRenderer.
* 
* In Shape class, we have a reference (or pointer) to the Renderer base class, which will be the bridge.
* This class will serve as a base class for all the shapes we want.
* 
* So we define the Circle class, which inherits from Shape and uses the Renderer reference methods.
* 
* Later, when we create a Circle, we will pass to the constructor a Renderer object of type VectorRenderer or RasterRenderer.
* 
* This way, we don't have to implement so many classes.
*/

struct Renderer
{
  virtual void render_circle(float x, float y, float radius) = 0;
  //virtual void render_rectangle(...) = 0;
};

struct VectorRenderer : Renderer
{
  void render_circle(float x, float y, float radius) override
  {
    cout << "Rasterizing circle of radius " << radius << endl;
  }
};

struct RasterRenderer : Renderer
{
  void render_circle(float x, float y, float radius) override
  {
    cout << "Drawing a vector circle of radius " << radius << endl;
  }
};

struct Shape
{
protected:
  Renderer& renderer; //this is the bridge
  Shape(Renderer& renderer) : renderer{ renderer } {}
public:
  virtual void draw() = 0; // implementation specific
  virtual void resize(float factor) = 0; // abstraction specific
};

struct Circle : Shape
{
  float x, y, radius;

  void draw() override
  {
    renderer.render_circle(x, y, radius);
  }

  void resize(float factor) override
  {
    radius *= factor;
  }

  Circle(Renderer& renderer, float x, float y, float radius)
    : Shape{renderer},
      x{x},
      y{y},
      radius{radius}
  {
  }
};

void bridge()
{
  RasterRenderer rr;
  Circle raster_circle{ rr, 5,5,5 };
  raster_circle.draw();
  raster_circle.resize(2);
  raster_circle.draw();
}

int main()
{
  bridge();
  getchar();
  return 0;
}
