#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Window.h"
#include "TextBuffer.h"
using namespace std;

/*
* The first thing we do is create a singleton pattern to only allow to have 1 console.
* 
* Later, we create public functions to be able to modify the console options, for example, a single line, multicolumn console.
* 
* In the private section of the class, we put the constructor of course to be a singleton, and delete the copy constructor and the copy assignment operator.
* 
* So basically, in a façade design, we take the things we want to create (in this case a console application) and create a class to encapsulate all the complicated parts 
* where we are initializing members, allocating memory and resources, etc., and expose those complicated parts in simple class functions so the application is easy to use 
* as an API. Here we use this class in Bloom.cpp.
* 
* Optionally, we can expose more complex methods to controle in a deeper way our API, like the buffer for example.
*/

class Console
{
public:
  static Console& instance()
  {
    static Console console;
    return console;
  }

  vector<shared_ptr<Window>> windows;

  // cannot make this static
  shared_ptr<Window> single(const string& title, uint8_t charsWide, uint8_t charsHigh)
  {
    auto w = make_shared<Window>(title, charsWide * charWidth, charsHigh * charHeight);
    auto buffer = make_shared<TextBuffer>(charsWide, charsHigh);
    w->buffers.push_back(buffer);
    auto viewport = make_shared<Viewport>(buffer);
    w->viewports.push_back(viewport);
    windows.push_back(w);
    return w;
  }

  shared_ptr<Window> multicolumn(const string& title, uint8_t columnCount, uint8_t columnWidth, uint8_t charsHigh)
  {
    auto w = make_shared<Window>(title, columnCount * columnWidth * charWidth, charsHigh * charHeight);
    for (uint8_t c = 0; c < columnCount; ++c)
    {
      auto buffer = make_shared<TextBuffer>(columnWidth, charsHigh);
      w->buffers.push_back(buffer);
      auto viewport = make_shared<Viewport>(buffer, buffer->get_size(), Point{}, Point{ columnWidth*c, 0 });
      w->viewports.push_back(viewport);
      windows.push_back(w);
    }
    return w;
  }

private:
  const int charWidth = 10, charHeight = 14;
  Console(){}
  Console(Console const&) = delete;
  void operator=(Console const&) = delete;
};
