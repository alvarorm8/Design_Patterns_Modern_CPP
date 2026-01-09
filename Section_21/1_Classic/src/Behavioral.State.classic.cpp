#include <iostream>
#include <string>
using namespace std;
/*
Here we implement the classic state pattern. We have a class State which is later inherited in the other state classes to create the different states.
In this base class we have the different states defined as functions. The base implementation of the functions is used to warn if we try to change from one
state to the same state.

In the classic state pattern, each state class implements the functions which represents the other states to represent the transition to the other states,
e.g. the OnState implements the off function.

Then we have the state machine class, which has the functionality to move to one state to another, in this case, the class LightSwitch which has the function
set_state, and the functions to change to the different states.

This example works fine, but the usage of delete->this for example is something not recommended normally, so for this reason and the way it is implemented, this way
of implementing the state pattern is not recommended.
*/

class LightSwitch;

struct State
{
  virtual void on(LightSwitch *ls)
  {
    cout << "Light is already on\n";
  }
  virtual void off(LightSwitch *ls)
  {
    cout << "Light is already off\n";
  }
};

struct OnState : State
{
  OnState()
  {
    cout << "Light turned on\n";
  }

  void off(LightSwitch* ls) override;
};

struct OffState : State
{
  OffState()
  {
    cout << "Light turned off\n";
  }

  void on(LightSwitch* ls) override;
};

class LightSwitch
{
  State *state;
public:
  LightSwitch()
  {
    state = new OffState();
  }
  void set_state(State* state)
  {
    this->state = state;
  }
  void on() { state->on(this); }
  void off() { state->off(this); }
};

void OnState::off(LightSwitch* ls)
{
  cout << "Switching light off...\n";
  ls->set_state(new OffState());
  delete this;
}

void OffState::on(LightSwitch* ls)
{
  cout << "Switching light on...\n";
  ls->set_state(new OnState());
  delete this;
}

int main()
{
  LightSwitch ls;
  ls.on();
  ls.off();
  ls.off();
  return 0;
}