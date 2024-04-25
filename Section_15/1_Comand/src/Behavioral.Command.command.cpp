#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
We want to manipulate this bank account and we might want to also record the fact that the bank account is manipulated. 
So we're going to have a command which modifies the bank account in a particular way, depositing or withdrawing money and
that you can also save somewhere there by having an audit log of everything that's happening in the system.

For that, we create the interface Command and the implement with BankAccountCommand.

In the main, first we do it with the vector, and the for loop which calls the action function for each member of the vector,
and later we use the CompositeBankAccountCommand class.
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
  virtual void undo() const = 0;
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

  void undo() const override
  {
    switch (action)
    {
    case withdraw:
      account.deposit(amount);
      break;
    case deposit:
      account.withdraw(amount);
      break;
    default: break;
    }
  }
};

// vector doesn't have virtual dtor, but who cares?
struct CompositeBankAccountCommand 
  : vector<BankAccountCommand>, Command
{
  CompositeBankAccountCommand(const initializer_list<value_type>& items)
    : vector<BankAccountCommand>(items) {}

  void call() const override
  {
    for (auto& cmd : *this)
      cmd.call();
  }

  void undo() const override
  {
    for (auto& cmd : *this)
      cmd.undo();
  }
};

int main()
{
  BankAccount ba;
  /*vector<BankAccountCommand> commands{*/
  CompositeBankAccountCommand commands {
    BankAccountCommand{ba, BankAccountCommand::deposit, 100},
    BankAccountCommand{ba, BankAccountCommand::withdraw, 200}
  };

  cout << ba.balance << endl;

  // apply all the commands
  /*for (auto& cmd : commands)
  {
    cmd.call();
  }*/
  commands.call();

  cout << ba.balance << endl;

  /*for_each(commands.rbegin(), commands.rend(),
    [](const BankAccountCommand& cmd) { cmd.undo(); });*/
  commands.undo();

  cout << ba.balance << endl;
  return 0;
}
