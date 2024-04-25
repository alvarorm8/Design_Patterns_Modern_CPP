#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
We want to manipulate this bank account and we might want to also record the fact that the bank account is manipulated. 
So we're going to have a command which modifies the bank account in a particular way, depositing or withdrawing money and
that you can also save somewhere there by having an audit log of everything that's happening in the system.

For that, we create the interface Command and the implement with BankAccountCommand.

In the main, we use a vector and a for loop which calls the action function for each member of the vector.
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

  void withdraw(int amount)
  {
    if (balance - amount >= overdraft_limit)
    {
      balance -= amount;
      cout << "withdrew " << amount << ", balance now " << 
        balance << "\n";
    }
  }
};

struct Command
{
  virtual ~Command() = default;
  virtual void call() const = 0;
};

// should really be BankAccountCommand
struct BankAccountCommand : Command
{
  BankAccount& account;
  enum Action { deposit, withdraw } action;
  int amount;

  BankAccountCommand(BankAccount& account, 
    const Action action, const int amount)
    : account(account), action(action), amount(amount) {}

  void call() const override
  {
    switch (action)
    {
    case deposit:
      account.deposit(amount);
      break;
    case withdraw: 
      account.withdraw(amount);
      break;
    default: break;
    }
  }
};

int main()
{
  BankAccount ba;
  vector<BankAccountCommand> commands{
    BankAccountCommand{ba, BankAccountCommand::deposit, 100},
    BankAccountCommand{ba, BankAccountCommand::withdraw, 200}
  };

  cout << ba.balance << endl;

  // apply all the commands
  for (auto& cmd : commands)
  {
    cmd.call();
  }

  cout << ba.balance << endl;
  return 0;
}
