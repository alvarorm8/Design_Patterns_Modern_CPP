#include "StdAfx.h"
#include "Window.h"
#include "TextBuffer.h"
#include "Console.h"
using namespace std;

/*
* Here a project from the professor is given where a console can be build and shown, but all the implementation details (creating a buffer, adding values, showing the window...) are hidden in a façade.
* 
* For that, we create the file Console.h, which will store the façade pattern.
*/

int main(int ac, char* av[])
{
  // create a single window and show it
  //Window window("Test", 2560, 1440);
  //Window window("Test", 1280, 720);

  //// let's try to create a viewport + buffer
  //auto buffer = make_shared<TextBuffer>(40, 40);
  //buffer->add_string("One");
  //buffer->add_string(string("Two"));
  //buffer->add_string(string("Three"));
  //buffer->add_string(string("Four"));
  //buffer->add_string(string("Five"));
  //window.buffers.push_back(buffer);
  //auto viewport = make_shared<Viewport>(buffer);
  //window.viewports.emplace_back(viewport);

  //auto viewport2 = make_shared<Viewport>(buffer, Size{ 40,40 }, Point{}, Point{ 45, 0 });
  //window.viewports.emplace_back(viewport2);
  //
  //auto viewport3 = make_shared<Viewport>(buffer, Size{ 40,40 }, Point{}, Point{ 90, 0 });
  //window.viewports.emplace_back(viewport3);

  //auto window = Console::instance().single("Test", 50, 30);
  auto window = Console::instance().multicolumn("Test", 2, 40, 40);

  for (size_t i = 0; i < 40; i++)
  {
    window->buffers[1]->add_string(
      string("This is line ") + boost::lexical_cast<string>(i),
      (i % 2 == 0));
  }

  window->Show();
  return 0;
}