#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <boost/lexical_cast.hpp>
using namespace std;

/*
* Basically, Single Responsability Principle says that 
* each class should have only a concern.
* 
* So in the Jounal example, if we decide to add the persistence idea inside
* the class, that would cause that if later we want to modify the persistence to 
* a database for example, we have to change the class.
* 
* That wouldn't be a problem if there's only one class, but if we have Journal, 
* we have Dictionary, we have News Paper, etc., as example of other classes, 
* and we want to change the persistence of every class to a database, we have to 
* modify all the classes.
* 
* If we put persistence in a separate class, called persistence, we only have to modify that
* class, so it is much better.
* 
* So basically, Journal has the concern to create, delete, modify, merge... entries and title,
* and persistence has the concern of the persistence of those properties of a Journal.
*/

struct Journal
{
  string title;
  vector<string> entries;

  explicit Journal(const string& title)
    : title{title}
  {
  }

  void add(const string& entry);

  // persistence is a separate concern, so it should be in a separate class
  void save(const string& filename);
};

void Journal::add(const string& entry)
{
  static int count = 1;
  //entries.push_back(boost::lexical_cast<string>(count++)
  entries.push_back(to_string(count++)
    + ": " + entry);
}

void Journal::save(const string& filename)
{
  ofstream ofs(filename);
  for (auto& s : entries)
    ofs << s << endl;
}

struct PersistenceManager
{
  static void save(const Journal& j, const string& filename)
  {
    ofstream ofs(filename);
    for (auto& s : j.entries)
      ofs << s << endl;
  }
};

void main()
{
  Journal journal{"Dear Diary"};
  journal.add("I ate a bug");
  journal.add("I cried today");

  //journal.save("diary.txt");

  PersistenceManager::save(journal, "diary.txt");

  //PersistenceManager pm;
  //pm.save(journal, "diary.txt");
}