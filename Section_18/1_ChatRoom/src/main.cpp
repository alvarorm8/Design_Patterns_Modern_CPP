#include "Person.hpp"
#include "ChatRoom.hpp"

/*

The mediator is a central component, and all the other components of the system have a reference to it.
The other components communicate exclusively through the mediator component, since they don't have any reference
to the others.

*/

int main()
{
  ChatRoom room;

  Person john{"John"};
  Person jane{"Jane"};
  room.join(&john);
  room.join(&jane);
  john.say("hi room");
  jane.say("oh, hey john");

  Person simon{"Simon"};
  room.join(&simon);
  simon.say("hi everyone!");

  jane.pm("Simon", "glad you found us, simon!");

  return 0;
}