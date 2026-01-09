#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
using namespace std;

/*
An example of a dynamic strategy is created for printing data in different formats.

We start by creating the class ListStrategy, which will be the base class to print the data. Here we add the basic implementation, so in case a specific class does not need to add
anything at the start or the end, we don't need to implement this in the derived classes. The add_list_item is pure virtual, as this method always needs to be implemented.

Later we create the TextProcessor class, which wil allow us to use a particular strategy in order to print a list of items. 
In the dynamic strategy, you simply have a variable of a strategy type (ListStrategy in this case), which makes possible to change the selection in runtime, and in the static approach you take it as a template argument,
so it is not possible to change during runtime the format.
In this class, we have different functions to select the type of format and clear the selection, and we use the ListStrategy element to add elements to the list to print.

To select the format, we create the classes MarkdownListStrategy and HtmlListStrategy, which inherit from ListStrategy.

In the MarkdownListStrategy, we implement only the add_list_item, since the start and end functions do not need anything else for markdown.

In the ListStrategy, we implement the add_list_item, start and end functions, since the html format requires specific start and end for a list.
*/

enum class OutputFormat
{
  Markdown,
  Html
};

struct ListStrategy
{
  virtual ~ListStrategy() = default;
  virtual void add_list_item(ostringstream& oss, const string& item) = 0;
  virtual void start(ostringstream& oss) {};
  virtual void end(ostringstream& oss) {};
};

struct MarkdownListStrategy : ListStrategy
{
  void add_list_item(ostringstream& oss, const string& item) override
  {
    oss << " * " << item << endl;
  }
};

struct HtmlListStrategy : ListStrategy
{
  void start(ostringstream& oss) override
  {
    oss << "<ul>" << endl;
  }

  void end(ostringstream& oss) override
  {
    oss << "</ul>" << endl;
  }

  void add_list_item(ostringstream& oss, const string& item) override
  {
    oss << "<li>" << item << "</li>" << endl;
  }
};

struct TextProcessor
{
  void clear()
  {
    oss.str("");
    oss.clear();
  }
  void append_list(const vector<string> items)
  {
    list_strategy->start(oss);
    for (auto& item : items)
      list_strategy->add_list_item(oss, item);
    list_strategy->end(oss);
  }

  void set_output_format(const OutputFormat format)
  {
    switch(format)
    {
    case OutputFormat::Markdown: 
      list_strategy = make_unique<MarkdownListStrategy>();
      break;
    case OutputFormat::Html: 
      list_strategy = make_unique<HtmlListStrategy>();
      break;
    default:
      throw runtime_error("Unsupported strategy.");
    }
  }
  string str() const { return oss.str(); }
private:
  ostringstream oss;
  unique_ptr<ListStrategy> list_strategy;
};

int main()
{
  // markdown
  TextProcessor tp;
  tp.set_output_format(OutputFormat::Markdown);
  tp.append_list({"foo", "bar", "baz"});
  cout << tp.str() << endl;

  // html
  tp.clear();
  tp.set_output_format(OutputFormat::Html);
  tp.append_list({"foo", "bar", "baz"});
  cout << tp.str() << endl;

  return 0;
}
