#pragma once
#include <algorithm>

/*
here we implement the chatroom class, which is the mediator.
It has several functions like the broadcast, join to display a message when someone joins the chat, etc.
*/

struct ChatRoom
{
  vector<Person*> people;

  void broadcast(const string& origin,
    const string& message);

  void join(Person* p);

  void message(const string& origin,
    const string& who,
    const string& message)
  {
    auto target = std::find_if(
      begin(people),
      end(people),
      [&](const Person *p) {
        return p->name == who;
      });
    if (target != end(people))
    {
      (*target)->receive(origin, message);
    }
  }
};


