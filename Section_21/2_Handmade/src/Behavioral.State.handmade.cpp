#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

/*
The handmade implementation of the state pattern is shown here. We start by defining an enumeration with the different states.
Later, the operator << is implemented for the different states so we can show them later in the console.

The Trigger class defines the different things that can trigger the change from one state to another. Additionally, the
operator << is implemented for the different states so we can show them later in the console.

Later, in the main function we are modelling the state machine. Basically a state machine is a set of rules which define the possibilities
to transition from one state to another.

This is represented with a map of with the current state, and a vector of the states where it can go and the triggers required to go to that state. 
*/

enum class State
{
  OffHook,
  Connecting,
  Connected,
  OnHold,
  OnHook
};

inline ostream& operator<<(ostream& os, const State& s)
{
  switch (s)
  {
  case State::OffHook:
    os << "off the hook";
    break;
  case State::Connecting:
    os << "connecting";
    break;
  case State::Connected: 
    os << "connected";
    break;
  case State::OnHold:
    os << "on hold";
    break;
  case State::OnHook:
    os << "on the hook";
    break;
  }
  return os;
}

enum class Trigger
{
  CallDialed,
  HungUp,
  CallConnected,
  PlacedOnHold,
  TakenOffHold,
  LeftMessage,
  StopUsingPhone
};

inline ostream& operator<<(ostream& os, const Trigger& t)
{
  switch (t)
  {
  case Trigger::CallDialed:
    os << "call dialed";
    break;
  case Trigger::HungUp:
    os << "hung up";
    break;
  case Trigger::CallConnected:
    os << "call connected";
    break;
  case Trigger::PlacedOnHold:
    os << "placed on hold";
    break;
  case Trigger::TakenOffHold:
    os << "taken off hold";
    break;
  case Trigger::LeftMessage: 
    os << "left message";
    break;
  case Trigger::StopUsingPhone:
    os << "putting phone on hook";
    break;
  default: break;
  }
  return os;
}

int main(char* argv[])
{
  map<State, vector<pair<Trigger, State>>> rules;

  rules[State::OffHook] = {
    {Trigger::CallDialed, State::Connecting},
    {Trigger::StopUsingPhone, State::OnHook}
  };

  rules[State::Connecting] = {
    {Trigger::HungUp, State::OffHook},
    {Trigger::CallConnected, State::Connected}
  };

  rules[State::Connected] = {
    {Trigger::LeftMessage, State::OffHook},
    {Trigger::HungUp, State::OffHook},
    {Trigger::PlacedOnHold, State::OnHold}
  };

  rules[State::OnHold] = {
    {Trigger::TakenOffHold, State::Connected},
    {Trigger::HungUp, State::OffHook}
  };

  State currentState{ State::OffHook },
        exitState{ State::OnHook };

  while (true)
  {
    cout << "The phone is currently " << currentState << endl;
    // We define a label here
  select_trigger:
    cout << "Select a trigger:" << "\n";

    int i = 0;
    for (auto item : rules[currentState])
    {
      cout << i++ << ". " << item.first << "\n";
    }

    int input;
    cin >> input;
    if (input < 0 || (input+1) > rules[currentState].size())
    {
      cout << "Incorrect option. Please try again." << "\n";
      goto select_trigger; //we go to the label here
    }

    currentState = rules[currentState][input].second;
    
    if (currentState == exitState) break;
  }

  cout << "We are done using the phone" << "\n";
  return 0;
}
