/*
Roses can be red, blue or red and blue. Given the class interface Flower and class Rose, build decorators RedFlower and BlueFlower that would print the following:

Rose rose;
RedFlower red_rose{rose};
RedFlower red_red_rose{red_rose};
BlueFlower blue_red_rose{red_rose};
cout << rose.str();          // "A rose"
cout << red_rose.str();      // "A rose that is red"
cout << red_red_rose.str();  // "A rose that is red"
cout << blue_red_rose.str(); // "A rose that is red and blue"
*/


#include <iostream>
#include <string>
using namespace std;

struct Flower
{
  virtual string str() = 0;
};

struct Rose : public Flower
{
  string str() override {
    return "A rose";
  }
};

struct RedFlower : public Flower
{
  Flower* flower;

  RedFlower(Flower* flower) : flower(flower) {}

  string str() override
  {
    string s = flower->str();
    if (s.find("red") != string::npos) return s;
    else if (s.find("blue") != string::npos)
    {
      return s + " and red";
    }
    else return s + " that is red";
  }
};

struct BlueFlower : public Flower
{
  Flower* flower;

  BlueFlower(Flower* flower)
    : flower{ flower } {}

  string str() override {
    string s = flower->str();
    if (s.find("blue") != string::npos) return s;
    else if (s.find("red") != string::npos)
    {
      return s + " and blue";
    }
    else return s + " that is blue";
  }
};

int main() {
  Rose rose;
  RedFlower red_rose{ &rose };
  //here if inside the class there's a reference to Flower, it won't call to RedFlower.str() 2 times and then Rose.str() 1 time as we could expect since the reference is to red_rose (RedFlower) and the object that wraps it is red_red_rose (RedFlower).
  //Instead, if we have a pointer, it will behave as expected, calling RedFlower.str() 2 times and then Rose.str() 1 time.
  RedFlower red_red_rose{ &red_rose };
  //Here if we have a reference it will work as expected, since the reference is to red_rose (RedFlower) and the object that wraps it is blue_red_rose (BlueFlower)
  BlueFlower blue_red_rose{ &red_rose };
  std::cout << "/////// rose ///////\n\n";
  cout << rose.str() << endl;          // "A rose"
  std::cout << "/////// red_rose ///////\n\n";
  cout << red_rose.str() << endl;      // "A rose that is red"
  std::cout << "/////// red_red_rose ///////\n\n";
  cout << red_red_rose.str() << endl;  // "A rose that is red"
  std::cout << "/////// blue_red_rose ///////\n\n";
  cout << blue_red_rose.str() << endl; // "A rose that is red and blue"

  return 0;
}