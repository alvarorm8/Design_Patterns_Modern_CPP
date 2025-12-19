#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

/*
Here a memento example is created with a back account.

To store the status, the functions which modify the status of the bank account (like deposit) return a memento object.

The function restore restores the status reading a memento.

The memento class here is an external class, but it also makes sense to make it an inner class of the BankAccount class.

The memento pattern can also be used to execute redo and undo operations if the state of the class is small. Since the bank account has only 1 member, besides 
providing the memento to the external functions which call the methods, we can also save all the status. To allow these operations, we create the BankAccount2 class.
*/

class Memento
{
  int balance;
public:
  Memento(int balance)
    : balance(balance)
  {
  }
  friend class BankAccount;
  friend class BankAccount2;
};

class BankAccount
{
  int balance = 0;
public:
  explicit BankAccount(const int balance)
    : balance(balance)
  {
  }

  Memento deposit(int amount)
  {
    balance += amount;
    return { balance };
  }

  void restore(const Memento& m)
  {
    balance = m.balance;
  }

  friend ostream& operator<<(ostream& os, const BankAccount& obj)
  {
    return os << "balance: " << obj.balance;
  }
};

class BankAccount2 // supports undo/redo
{
  int balance = 0;
  vector<shared_ptr<Memento>> changes;
  int current; // saves the index of the status in which we are.
public:
  explicit BankAccount2(const int balance)
  : balance(balance)
  {
    changes.emplace_back(make_shared<Memento>(balance));
    current = 0;
  }

  shared_ptr<Memento> deposit(int amount)
  {
    balance += amount;
    auto m = make_shared<Memento>(balance);
    changes.push_back(m);
    ++current;
    return m;
  }

  void restore(const shared_ptr<Memento>& m)
  {
    if (m)
    {
      balance = m->balance;
      changes.push_back(m);
      current = changes.size() - 1; // points to the last element of changes
    }
  }

  shared_ptr<Memento> undo()
  {
    if (current > 0)
    {
      --current;
      auto m = changes[current];
      balance = m->balance;
      return m;
    }
    return{};
  }

  shared_ptr<Memento> redo()
  {
    if (current + 1 < changes.size())
    {
      ++current;
      auto m = changes[current];
      balance = m->balance;
      return m;
    }
    return{};
  }

  friend ostream& operator<<(ostream& os, const BankAccount2& obj)
  {
    return os << "balance: " << obj.balance;
  }
};

void memento()
{
  BankAccount ba{ 100 };
  auto m1 = ba.deposit(50); // 150
  auto m2 = ba.deposit(25); // 175
  cout << ba << "\n";

  // undo to m1
  ba.restore(m1);
  cout << ba << "\n";

  // redo
  ba.restore(m2);
  cout << ba << "\n";
}

void undo_redo()
{
  BankAccount2 ba{ 100 };
  ba.deposit(50);
  ba.deposit(25); // 125
  cout << ba << "\n";

  ba.undo();
  cout << "Undo 1: " << ba << "\n";
  ba.undo();
  cout << "Undo 2: " << ba << "\n";
  ba.redo();
  cout << "Redo 2: " << ba << "\n";

  ba.undo();
}

int main()
{
  // memento()
  undo_redo();

  getchar();
  return 0;
}
