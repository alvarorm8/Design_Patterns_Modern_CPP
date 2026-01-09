/*
State Coding Exercise
A combination lock is a lock that opens after the right digits have been entered. A lock is preprogrammed with a combination (e.g., 12345 ) and the user is expected to enter this combination to unlock the lock.

The lock has a status  field that indicates the state of the lock. The rules are:

If the lock has just been locked (or at startup), the status is LOCKED.
If a digit has been entered, that digit is shown on the screen. As the user enters more digits, they are added to Status.
If the user has entered the correct sequence of digits, the lock status changes to OPEN.
If the user enters an incorrect sequence of digits, the lock status changes to ERROR.
Please implement the CombinationLock  class to enable this behavior. Be sure to test both correct and incorrect inputs.

Here is an example unit test for the lock:

CombinationLock cl({1,2,3});
ASSERT_EQ("LOCKED", cl.status);
cl.enter_digit(1);
ASSERT_EQ("1", cl.status);
cl.enter_digit(2);
ASSERT_EQ("12", cl.status);
cl.enter_digit(3);
ASSERT_EQ("OPEN", cl.status);
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum class State
{
  LOCKED,
  OPEN,
  ERROR
};

std::string stateToString(State c) {
  switch (c) {
    case State::LOCKED:   return "LOCKED";
    case State::OPEN: return "OPEN";
    case State::ERROR:  return "ERROR";
  }
  return "Unknown";
}

class CombinationLock
{
    vector<int> combination;
    vector<int>::const_iterator it;
public:
    string status;

    CombinationLock(const vector<int> &combination) : combination(combination) {
      it = this->combination.cbegin();
      status = stateToString(State::LOCKED);
    }

    void enter_digit(int digit)
    {
      if (digit != *it) {
        status = stateToString(State::ERROR);
      } else {
        if (status == stateToString(State::LOCKED)
          || status == stateToString(State::OPEN) 
          || status == stateToString(State::ERROR))
        {
          status = std::to_string(digit);
        } else {
          status.append(std::to_string(digit));
        }
        std::cout << status << std::endl;
        it++;
        if (it == combination.cend()) {
          // if it reaches this point, the combination is correct since the error state has not been achieved
          status = stateToString(State::OPEN);
        }
      }
    }
};

#include <gtest/gtest.h>

namespace {

    class Evaluate : public ::testing::Test {};

    TEST_F(Evaluate, TestSuccess)
    {
      CombinationLock cl({1,2,3});
      ASSERT_EQ("LOCKED", cl.status);

      cl.enter_digit(1);
      ASSERT_EQ("1", cl.status);

      cl.enter_digit(2);
      ASSERT_EQ("12", cl.status);

      cl.enter_digit(3);
      ASSERT_EQ("OPEN", cl.status);
    }

    TEST_F(Evaluate, TestFailure)
    {
      CombinationLock cl({1,2,3});
      ASSERT_EQ("LOCKED", cl.status);

      cl.enter_digit(1);
      ASSERT_EQ("1", cl.status);

      cl.enter_digit(2);
      ASSERT_EQ("12", cl.status);

      cl.enter_digit(5);
      ASSERT_EQ("ERROR", cl.status);
    }

}  // namespace

int main(int ac, char* av[])
{
  //::testing::GTEST_FLAG(catch_exceptions) = false;
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}