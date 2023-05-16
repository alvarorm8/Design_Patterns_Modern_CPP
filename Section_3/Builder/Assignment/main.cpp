/*
You are asked to implement the Builder design pattern for rendering simple chunks of code.

Sample use of the builder you are asked to create:

auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
cout << cb;
The expected output of the above code is:

class Person
{
  string name;
  int age;
};
Please observe the same placement of curly braces and use two-space indentation.
*/

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class ClassRender {
  string className;
  vector<pair<string, string>> members;
public:
  ClassRender(string className) : className{ className } {}

  void addMember(pair<string, string> member) {
    members.emplace_back(member);
  }

  const string & getClassName() const {
    return className;
  }

  const vector<pair<string, string>> & getMembers() const {
    return members;
  }
};

class CodeBuilder
{
  ClassRender classRender;
  const size_t indent_size = 2;
public:
  CodeBuilder(const string& class_name) : classRender{class_name} {}

  CodeBuilder& add_field(const string& name, const string& type) {
    classRender.addMember(make_pair(type, name));
    return *this;
  }

  const ClassRender & getClassRender() const {
    return classRender;
  }
  friend ostream& operator<<(ostream& os, const CodeBuilder& obj);
};

//If we define it inside the CodeBuilder class, the compiler does not get it and it highlights an error un << use. But it works
//If we define as a global function, it gets it.
ostream& operator<<(ostream& os, const CodeBuilder& obj)
{
  os << "class " << obj.classRender.getClassName() << endl
    << "{" << endl;
  if (obj.classRender.getMembers().size() > 0) {
    for (const pair<string, string>& member : obj.classRender.getMembers()) {
      os << string(obj.indent_size, ' ') << member.first << " " << member.second << ";" << endl;
    }
  }
  os << "};";
  return os;
}

int main() {
  auto cb = CodeBuilder{ "Person" }.add_field("name", "string").add_field("age", "int");
  cout << cb;
  return 0;
}