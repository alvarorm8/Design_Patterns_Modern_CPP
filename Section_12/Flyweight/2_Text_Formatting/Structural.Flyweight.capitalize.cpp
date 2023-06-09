#include <iostream>
#include <string>
#include <ostream>
#include <vector>
using namespace std;

/*
* Here we want an applicaction to format text. 
* The class FormattedText is a first way of doing it but it is very unefficient since we are storing a vector of bools and iterating over each char and checking whether or not they have to be capital.
*
* The class BetterFormattedText is where we apply the flyweight pattern to not waste memory like in FormattedText.
* The flyweight is applied through the internal class TextRange which allows us to avoid having to store the vector of booleans so it is more efficient.
*/

class FormattedText
{
  string plain_text;
  bool *caps;// this way is very unefficient
public:
  explicit FormattedText(const string& plainText)
    : plain_text{plainText}
  {
    caps = new bool[plainText.length()];
    memset(caps, 0, plainText.length());
  }
  ~FormattedText()
  {
    delete[] caps;
  }
  void capitalize(int start, int end)
  {
    for (int i = start; i <= end; ++i)
      caps[i] = true;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const FormattedText& obj)
  {
    string s;
    for (int i = 0; i < obj.plain_text.length(); ++i)
    {
      char c = obj.plain_text[i];
      s += (obj.caps[i] ? toupper(c) : c);
    }
    return os << s;
  }
};

class BetterFormattedText
{
public:
  struct TextRange
  {
    int start, end;
    bool capitalize, bold, italic;

    bool covers(int position) const
    {
      return position >= start && position <= end;
    }
  };

  TextRange& get_range(int start, int end)
  {
    formatting.emplace_back(TextRange{ start, end });
    return *formatting.rbegin();
  }

  explicit BetterFormattedText(const string& plainText)
    : plain_text{plainText}
  {
  }

  friend std::ostream& operator<<(std::ostream& os, const BetterFormattedText& obj)
  {
    string s;
    for (size_t i = 0; i < obj.plain_text.length(); i++)
    {
      auto c = obj.plain_text[i];
      for (const auto& rng : obj.formatting)
      {
        if (rng.covers(i) && rng.capitalize)
          c = toupper(c);
        s += c;
      }
    }
    return os << s;
  }

private:
  string plain_text;
  vector<TextRange> formatting;
};

int main(int argc, char* argv[])
{
  FormattedText ft("This is a brave new world");
  ft.capitalize(10, 15);
  cout << ft << endl;

  BetterFormattedText bft("This is a brave new world");
  bft.get_range(10, 15).capitalize = true;
  cout << bft << endl;
}
