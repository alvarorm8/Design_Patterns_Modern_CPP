/*
The state machine pattern is implemented here with boost msm library.
The includes are divided in:
  - backend: defines the state machine
  - frontend: executes or orquestrates the state machine

We start by defining the different states names in a vector to later use them.

The triggers are defined in this ocasion as classes or structs.

Here the state machine is created by inheriting from the class state_machine_def.
Inside of it, we can define the different states, inheriting from the state class.
Also, we can customise the different states adding behaviours, like the on_entry and on_exit functions.

After that, we define the transitions table, which define how to go from one state to another (similar to the map done in
the previous section), where we define the initial state, the trigger and the final state. The transitions can also be
customised. For example, the last one includes two additional elements, the first one is an action (PhoneBeingDestroyed) which is invoked when 
the transition from OnHold to PhoneDestroyed happens, and the second one is a guard condition (CanDestroyPhone) which causes that the transition
from OnHold to PhoneDestroyed can only happen when the condition is met.

Another thing that we need to define is the initial state, using a typedef (typedef OffHook initial_state;).

The last thing to define is a function to determine what happens is we have no transition to go. This is done with the function no_transition.

In the main function, we define the state machine object, and transition from states with the function process_event.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// back-end
#include <boost/msm/back/state_machine.hpp>

//front-end
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;

vector<string> state_names{
  "off hook"s,
  "connecting"s,
  "connected"s,
  "on hold"s,
  "destroyed"s
};

// transitions/events
struct CallDialed {};
struct HungUp {};
struct CallConnected {};
struct PlacedOnHold {};
struct TakenOffHold {};
struct LeftMessage {};
struct PhoneThrownIntoWall {};

struct PhoneStateMachine : state_machine_def<PhoneStateMachine>
{
  bool angry{ true }; // start with false

  struct OffHook : state<> {};
  struct Connecting : state<>
  {
    template <class Event, class FSM>
    void on_entry(Event const& evt, FSM&)
    {
      cout << "We are connecting..." << endl;
    }
    // also on_exit
  };
  struct Connected : state<> {};
  struct OnHold : state<> {};
  struct PhoneDestroyed : state<> {};

  struct PhoneBeingDestroyed
  {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const&, FSM&, SourceState&, TargetState&)
    {
      cout << "Phone breaks into a million pieces" << endl;
    }
  };
  
  struct CanDestroyPhone
  {
    template <class EVT, class FSM, class SourceState, class TargetState>
    bool operator()(EVT const&, FSM& fsm, SourceState&, TargetState&)
    {
      return fsm.angry;
    }
  };

  // start, event, target, action, guard
  struct transition_table : mpl::vector <
    Row<OffHook, CallDialed, Connecting>,
    Row<Connecting, CallConnected, Connected>,
    Row<Connected, PlacedOnHold, OnHold>,
    Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed, 
        PhoneBeingDestroyed, CanDestroyPhone>
  > {};

  // starting state
  typedef OffHook initial_state;

  // what happens if there's nowhere to go
  template <class FSM, class Event>
  void no_transition(Event const& e, FSM&, int state)
  {
    cout << "No transition from state " << state_names[state]
      << " on event " << typeid(e).name() << endl;
  }
};



int main()
{
  msm::back::state_machine<PhoneStateMachine> phone;

  auto info = [&]()
  {
    auto i = phone.current_state()[0];
    cout << "The phone is currently " <<
      state_names[i] << "\n";
  };

  info();
  phone.process_event(CallDialed{});
  info();
  phone.process_event(CallConnected{});
  info();
  phone.process_event(PlacedOnHold{});
  info();
  phone.process_event(PhoneThrownIntoWall{});
  info();

  // try process_event here :), the no_transition function is called.
  phone.process_event(CallDialed{});

  cout << "We are done using the phone" << "\n";

  return 0;
}
