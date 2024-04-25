/*
Implement the Account::process() function to process different account commands.

The rules are obvious:
    - success indicates whether the operation was successful
    - You can only withdraw money if you have enough in your account
*/

#include <gtest/gtest.h>

struct Command
{
  enum Action { deposit, withdraw } action;
  int amount{0};
  bool success{false};
};

struct Account
{
  int balance{0};

  void process(Command& cmd)
  {
    // todo
    switch(cmd.action) {
        case Command::deposit:
            balance += cmd.amount;
            cmd.success = true;
            break;
        case Command::withdraw:
            if (balance >= cmd.amount){
                balance -= cmd.amount;
                cmd.success = true;
            } else {
                cmd.success = false;
            }
            break;
    }
  }
};

namespace
{
  class Evaluate : public testing::Test
  {
  public:
  };

  TEST_F(Evaluate, LotsOfAccountTests)
  {
    Account a;
    Command command{Command::deposit, 100};
    a.process(command);

    ASSERT_EQ(100, a.balance);
    ASSERT_TRUE(command.success);

    command = Command{Command::withdraw, 50};
    a.process(command);

    ASSERT_EQ(50, a.balance);
    ASSERT_TRUE(command.success);

    command = Command{Command::withdraw, 150};
    a.process(command);

    ASSERT_EQ(50, a.balance);
    ASSERT_FALSE(command.success);
  }
} // namespace

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}