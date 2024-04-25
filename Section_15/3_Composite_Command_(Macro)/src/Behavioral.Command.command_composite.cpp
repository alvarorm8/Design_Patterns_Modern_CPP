#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;

/*
Think about the implementation of macros in a Microsoft office application, for example. That is a sequence of commands
that gets recorded one after another, and you can sort of you can play back all the commands one after another, and you
can also undo them all in reverse order with a single invocation.

So we're going to do the same thing here by basically turning a vector of commands into a separate object, which also has
methods called call and undo, which operate on a chunk of different commands at the same time.

This is something that's called the composite design pattern, by the way. So here we're going to merge the composite design
pattern with the command design pattern. Typically known as MACROS.

We start with the definition of CompositeBankAccountCommand, and the idea is the following. You initialize the composite bank 
account command with a set of commands that you want to invoke, and then you can call them in a single function call and you
can undo them in a single function call.

Later, we can define classes with predefined actions inheriting this class, like the MoneyTransferCommand class.

The problem is that with this initial implementation, the commands are not related, which means that if for example we want to transfer
a huge ammount of money from one to another, since there's a limit of -500, the withdraw method of the first account would fail, but it would do
the deposit on the second account. To solve it we want to somehow make sure that the commands are all tied to one another so that if one of them fails,
then the other fails as well.

For that, we define the DependentCompositeCommand which adds the logic of the success of the operation, and if one command fails, the others do it too.

So this is just a small illustration of the kind of problems that you can encounter as you have commands depending on other commands. So it's very easy to make
a vector of them, but it's a lot harder to actually make sure that you get some eventual consistency.

This is why you get this composite command as an extension of the ordinary command design pattern, because you want additional logic, you want commands depending
on other commands and interplaying with other commands.
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

// vector doesn't have virtual dtor, but who cares?
struct CompositeBankAccountCommand : vector<BankAccountCommand>, Command
{
  CompositeBankAccountCommand(const initializer_list<value_type>& items)
    : vector<BankAccountCommand>(items)
  {
  }

  void call() override
  {
    for (auto& cmd : *this)
      cmd.call();
  }

  void undo() override
  {
    for (auto it = rbegin(); it != rend(); ++it)
      it->undo();
  }
};

struct DependentCompositeCommand : CompositeBankAccountCommand
{
  explicit DependentCompositeCommand(
    const initializer_list<value_type>& items)
    : CompositeBankAccountCommand{ items } {}

  void call() override
  {
    bool ok = true;
    for (auto& cmd : *this)
    {
      if (ok)
      {
        cmd.call();
        ok = cmd.succeeded;
      }
      else
      {
        cmd.succeeded = false;
      }
    }
  }
};

struct MoneyTransferCommand : DependentCompositeCommand
{
  MoneyTransferCommand(BankAccount& from,
    BankAccount& to, int amount): 
    DependentCompositeCommand
    {
      BankAccountCommand{from, BankAccountCommand::withdraw, amount},
      BankAccountCommand{to, BankAccountCommand::deposit, amount}
    } {}
};


int main()
{
  BankAccount ba, ba2;

  ba.deposit(100);

  MoneyTransferCommand cmd { ba, ba2, 50 };

  cout << ba.balance << endl;
  cout << ba2.balance << endl;

  cmd.call();

  cout << ba.balance << endl;
  cout << ba2.balance << endl;

  cmd.undo();

  cout << ba.balance << endl;
  cout << ba2.balance << endl;

  return 0;
}
