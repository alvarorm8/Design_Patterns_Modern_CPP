#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;

/*
Here we continue with the work done in section 1 adding the undo operation. For that, we modify the logic and create a flag "succeeded" which indicates if the previous operation is correct to undo it.
*/

struct BankAccount
{
  int balance = 0;
  int overdraft_limit = -500;

  void deposit(int amount)
  {
    balance += amount;
    cout << "deposited " << amount << ", balance now " <<
      balance << "\n";
  }

  bool withdraw(int amount)
  {
    if (balance - amount >= overdraft_limit)
    {
      balance -= amount;
      cout << "withdrew " << amount << ", balance now " <<
        balance << "\n";
      return true;
    }
    return false;
  }
};

struct Command
{
  bool succeeded;
  virtual void call() = 0;
  virtual void undo() = 0;
};

// should really be BankAccountCommand
struct BankAccountCommand : Command
{
  BankAccount& account;
  enum Action { deposit, withdraw } action;
  int amount;

  BankAccountCommand(BankAccount& account, const Action action,
    const int amount)
    : account(account),
      action(action), amount(amount)
  {
    succeeded = false;
  }

  void call() override
  {
    switch (action)
    {
    case deposit:
      account.deposit(amount);
      succeeded = true;
      break;
    case withdraw:
      succeeded = account.withdraw(amount);
      break;
    }
  }

  void undo() override
  {
    if (!succeeded) return;

    switch (action)
    {
    case withdraw:
      if (succeeded)
        account.deposit(amount);
      break;
    case deposit:
      account.withdraw(amount);
      break;
    }
  }
};

int main()
{
  BankAccount ba;
  vector<BankAccountCommand> commands{
    BankAccountCommand{ ba, BankAccountCommand::deposit, 100 },
    BankAccountCommand{ ba, BankAccountCommand::withdraw, 200 }
  };

  cout << ba.balance << endl;

  // apply all the commands
  for (auto& cmd : commands)
  {
  cmd.call();
  }

  cout << ba.balance << endl;

  for_each(commands.rbegin(), commands.rend(),
  [](BankAccountCommand& cmd) { cmd.undo(); });

  cout << ba.balance << endl;
  return 0;
}
