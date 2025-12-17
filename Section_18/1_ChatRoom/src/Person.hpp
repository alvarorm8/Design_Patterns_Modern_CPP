#pragma once
#include <string>
#include <vector>
using namespace std;

/*
Here we define a person in the chatroom. All the persons are going to have a reference or pointer to the mediator.
This is how typically goes with this pattern. The mediator can be a singleton, or a global static variable, but there's only one 
in the whole system.

We define several functions like the say to send a message to all people, pm to send a message to one person, etc.
*/

struct ChatRoom;

struct Person {
  string name;
  ChatRoom* room{nullptr};
  vector<string> chat_log;

  Person(const string &name);

  void say(const string& message) const;
  void pm(const string& who,
    const string& message) const;

  void receive(const string& origin,
    const string& message);

  bool operator==(const Person &rhs) const;

  bool operator!=(const Person &rhs) const;
};


