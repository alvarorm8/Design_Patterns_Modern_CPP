#include <cstdio>
#include <vector>
#include <iostream>
#include <boost/predef/library/c.h>
#include <boost/predef/library/c.h>
#include <boost/predef/library/c.h>
#include <boost/predef/library/c.h>

/*
Here the idea is to have a common function called connect_to which allow us to connect a neuron to a neuron, a neuron to a layer, a layer to a neuron and a layer to a layer.

Here we would have to define 4 different functions, which will cause the same problem as in the Bridge pattern, the "Cartesian Product" complexity explosion. So here we use
the Composite pattern to solve it.

We define an interface called SomeNeurons which has the basic implementation of the connect_to function. 

The problem in the for loop of SomeNeurons connect_to is that if the type is a Layer, we have no problem since it is a vector, 
but for a single neuron we don't have a begin iterator and an end iterator, that's why, we define the begin and end functions.

So now, we can use the connect_to function of SomeNeurons with single elements and composite elements.
*/
using namespace std;

struct Neuron;

template <typename Self>
struct SomeNeurons
{
  template <typename T> void connect_to(T& other)
  {
    //here this pointer is pointing to a SomeNeurons object, which is not helpful to know which type of element its pointing to (neuron or layer)
    //that's why, we make a cast to a Pointer of Self type (which will be Neuron or Layer) to be able to know the type and iterate over its neurons.
    //Here we are using CTRP, which is the Curiously Recurring Template Pattern
    for (Neuron& from : *static_cast<Self*>(this)) 
    {
      for (Neuron& to : other)
      {
        from.out.push_back(&to);
        to.in.push_back(&from);
      }
    }
  }
};

struct Neuron : SomeNeurons<Neuron>
{
  vector<Neuron*> in, out;
  unsigned int id;

  Neuron()
  {
    static int id = 1; 
    this->id = id++;
  }

  /*template <typename T> void connect_to(T& other)
  {
    for (Neuron& target : other)
      connect_to(target);
  }*/

  // legal in MSVC only
  /*template<> void connect_to<Neuron>(Neuron& other)
  {
    out.push_back(&other);
    other.in.push_back(this);
  }*/

  // connect_to(vector<Neuron>&)

  Neuron* begin() { return this; }
  Neuron* end() { return this + 1; }

  friend ostream& operator<<(ostream& os, const Neuron& obj)
  {
    for (Neuron* n : obj.in)
    {
      os << n->id << "\t-->\t[" << obj.id << "]" << endl;
    }

    for (Neuron* n : obj.out)
    {
      os << "[" << obj.id << "]\t-->\t" << n->id << endl;
    }
    return os;
  }
};

struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer> //not a good idea to inherit from stl as vector since they don't have virtual destructors, but in this case we allow it for the demo
{
  NeuronLayer(int count)
  {
    while (count-- > 0)
      emplace_back(Neuron{});
  }

  friend ostream& operator<<(ostream& os, NeuronLayer& obj)
  {
    
    for (auto& n : obj) os << n;
    return os;
  }
};

void main()
{
  Neuron n1, n2;
  n1.connect_to(n2);

  cout << n1 << n2 << endl;

  NeuronLayer l1{5};
  Neuron n3;
  l1.connect_to(n3);
  
  cout << "Neuron " << n3.id << endl << n3 << endl;
  cout << "Layer " << endl << l1 << endl;

  NeuronLayer l2{ 2 }, l3{ 3 };
  l2.connect_to(l3);
  cout << "Layer l2" << endl << l2;
  cout << "Layer l3" << endl << l3;
}