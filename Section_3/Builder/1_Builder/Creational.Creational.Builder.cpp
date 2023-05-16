#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
using namespace std;

struct HtmlBuilder;

struct HtmlElement
{
  string name;
  string text;
  vector<HtmlElement> elements;
  const size_t indent_size = 2;

  HtmlElement() {}
  HtmlElement(const string& name, const string& text)
    : name(name),
    text(text)
  {
  }

  string str(int indent = 0) const
  {
    ostringstream oss;
    string i(indent_size*indent, ' ');
    oss << i << "<" << name << ">" << endl;
    if (text.size() > 0)
      oss << string(indent_size*(indent + 1), ' ') << text << endl;

    for (const auto& e : elements)
      oss << e.str(indent + 1);

    oss << i << "</" << name << ">" << endl;
    return oss.str();
  }

  // This function is used in main to construct the object in one single line
  static HtmlBuilder build_base(string root_name)
  {
      return { root_name };
  }

  // This function is a variation of the previous one to return a pointer instead of a reference
  static unique_ptr<HtmlBuilder> build(string root_name)
  {
    return make_unique<HtmlBuilder>(root_name);
  }
};

struct HtmlBuilder
{
  HtmlBuilder(string root_name)
  {
    root.name = root_name;
  }

  // Here we implement the fluent interface (commented in main)
  // to be able to call in a single line several times the function.
  // Instead of returning void, we return a pointer or a reference to 
  // the this pointer, so we can call several times the function.
  HtmlBuilder& add_child(string child_name, string child_text)
  {
    HtmlElement e{ child_name, child_text };
    root.elements.emplace_back(e);
    return *this;
  }

  // Here we implement the fluent interface again as a pointer
  HtmlBuilder* add_child_2(string child_name, string child_text)
  {
    HtmlElement e{ child_name, child_text };
    root.elements.emplace_back(e);
    return this;
  }

  string str() { return root.str(); }

  //Operator to return a HtmlElement when creating an object with HtmlBuilder
  operator HtmlElement() const { return std::move(root); } //We can move the element since we won't use the HtmlBuilder object, since we're returning a HtmlElemnt
  HtmlElement root;
};

struct HtmlBuilder2;
class HtmlElement2;

int demo()
{
    /*
    * The two examples shown here are simple string concatenation to create a website text.
    * 
    * But this is not scalable to a real website for example, in which we have lots of components, 
    * we can define rules, etc.
    * 
    * For that, we have the Builder pattern, which defines an Object Oriented Structure (OOS) which 
    * represent the different parts you are building, in this case a website (title, paragraphs, pictures, etc.) 
    * and support its transformation, in this case, to a string. Later you define another class which helps you construct
    * the class you have created and work with it.
    * 
    * So here, the first thing we do is defining the HtmlElement, and later, in another class, the HtmlBuilder which is going
    * to build the HtmlElement objects, so we don't have to work with the HtmlElement objects. HmtlBuilder allows us to work
    * with HtmlElements, in this case, using the str function.
    */
    // <p>hello</p>
    auto text = "hello";
    string output;
    output += "<p>";
    output += text;
    output += "</p>";
    printf("<p>%s</p>", text);

    // <ul><li>hello</li><li>world</li></ul>
    string words[] = { "hello", "world" };
    ostringstream oss;
    oss << "<ul>";
    for (auto w : words)
    oss << "  <li>" << w << "</li>";
    oss << "</ul>";
    printf(oss.str().c_str());

    // easier
    HtmlBuilder builder{ "ul" };
    // This call is done like this thanks to the fluent builder.,
    // which is very common in design patterns and known as
    // fluent interface.
    builder.add_child("li", "hello").add_child("li", "world");
    //builder.add_child("li", "hello")
    //builder.add_child("li", "world");
    cout << builder.str() << endl;

    // Here we use the static function of HtmlElement to construct the object in one single line
    // If we use auto we get a HtmlBuilder, but if we put HtmlElement, we use the operator ()
    // defined in HtmlBuilder to return a HtmlElement directly
    HtmlElement builder3 = HtmlElement::build_base("ul")
        .add_child("li", "hello").add_child("li", "world");
    cout << builder3.str() << endl;

    // Here the logic is the same as before but we use the static function of HtmlElement modified
    // to return a pointer instead of a reference, but reference is more sensible.
    auto builder2 = HtmlElement::build("ul")
    ->add_child_2("li", "hello")->add_child_2("li", "world");
    cout << builder2 << endl;

    /*
    * The problem with this implementation is that the client using the API might not know about the conversion
    * operator, so to be easier to construct we can do the following (which will be used in HtmlElement2 and HtmlBuilder2):
    * 
    * First make constructors of HtmlElement2 private, so clients can not create HtmlElement2 objects directly
    * Second make HtmlBuilder2 friend class to allow it to use constructor of HtmlElement2
    * Third create a create function in HtmlElement2 which returns a HtmlBuilder2 object
    * Fourth create a build function in HtmlBuilder2 which returns a HtmlElement2 object
    * 
    * This way you encourage the client to use the API like this:
    */

    HtmlElement2 elem = HtmlElement2::create("root_name").add_child("Hello", "World").build();

    cout << elem.str() << endl;
    getchar();
    return 0;
}

class HtmlElement2
{
    friend struct HtmlBuilder2;
    string name;
    string text;
    vector<HtmlElement2> elements;
    const size_t indent_size = 2;

    HtmlElement2() {}
    HtmlElement2(const string& name, const string& text)
        : name(name),
        text(text)
    {
    }

public:
    string str(int indent = 0) const
    {
        ostringstream oss;
        string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << endl;
        if (text.size() > 0)
            oss << string(indent_size * (indent + 1), ' ') << text << endl;

        for (const auto& e : elements)
            oss << e.str(indent + 1);

        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }

    static HtmlBuilder2 create(string root_name) {
        return { root_name };
    }
};

struct HtmlBuilder2
{
    HtmlBuilder2(string root_name)
    {
        root.name = root_name;
    }

    HtmlBuilder2& add_child(string child_name, string child_text)
    {
        HtmlElement e{ child_name, child_text };
        root.elements.emplace_back(e);
        return *this;
    }

    HtmlBuilder2* add_child_2(string child_name, string child_text)
    {
        HtmlElement e{ child_name, child_text };
        root.elements.emplace_back(e);
        return this;
    }

    string str() { return root.str(); }

    HtmlElement2 build() {
        return root;
    }

    operator HtmlElement2() const { return std::move(root); }
    HtmlElement2 root;
};