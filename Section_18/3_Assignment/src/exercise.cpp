/*
Mediator Coding Exercise
Our system has any number of instances of Participant  classes. Each Participant has a value  integer, initially zero.

A participant can say()  a particular value, which is broadcast to all other participants. At this point in time, every other participant is obliged to increase their value  by the value being broadcast.

Example:

Two participants start with values 0 and 0 respectively
Participant 1 broadcasts the value 3. We now have Participant 1 value = 0, Participant 2 value = 3
Participant 2 broadcasts the value 2. We now have Participant 1 value = 2, Participant 2 value = 3
*/

#include <iostream>
#include <vector>
using namespace std;

struct IParticipant
{
  virtual ~IParticipant() = default;
  virtual void notify(IParticipant* participant, int value) = 0;
};

struct Mediator {
  std::vector<IParticipant*> participants;
  void broadcast(IParticipant* part, const int value) {
    for (auto participant : participants) {
      participant->notify(part, value);
    }
  }
};

struct Participant : IParticipant
{
    int value{0};
    Mediator& mediator;

    Participant(Mediator &mediator) : mediator(mediator)
    {
      mediator.participants.push_back(this);
    }

    void notify(IParticipant* participant, int value) override {
      if (this != participant) {
        this->value += value;
      }
    }

    void say(int value)
    {
        mediator.broadcast(this, value);
    }
};

#include "gtest/gtest.h"
// #include "helpers/iohelper.h"

namespace {

    class Evaluate : public ::testing::Test {};

    TEST_F(Evaluate, LongMediationTest) {
      Mediator m;
      Participant p1{m}, p2{m};

      ASSERT_EQ(0, p1.value);
      ASSERT_EQ(0, p2.value);

      p1.say(2);

      ASSERT_EQ(0, p1.value);
      ASSERT_EQ(2, p2.value);

      p2.say(4);

      ASSERT_EQ(4, p1.value);
      ASSERT_EQ(2, p2.value);
    }

}  // namespace