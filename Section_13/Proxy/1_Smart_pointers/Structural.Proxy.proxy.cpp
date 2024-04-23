#include <iostream>
#include <string>
#include <sstream>
#include <memory>
using namespace std;

/*
* Smart pointers are proxies because they look like raw pointers, they give you the -> operator and so on, but they have enhanced features like for example
* they delete themselves, you have the .get function, etc.
*/

struct BankAccount
{
  virtual ~BankAccount() = default;
  virtual void deposit(int amount) = 0;
  virtual void withdraw(int amount) = 0;
};

struct CurrentAccount : BankAccount // checking
{
  explicit CurrentAccount(const int balance)
    : balance(balance)
  {
  }

  void deposit(int amount) override
  {
    balance += amount;
  }

  void withdraw(int amount) override
  {
    if (amount <= balance) balance -= amount;
  }

  friend ostream& operator<<(ostream& os, const CurrentAccount& obj)
  {
    return os << "balance: " << obj.balance;
  }

private:
  int balance;
};

void smart_pointers()
{
  BankAccount* a = new CurrentAccount(123);
  a->deposit(321);
  delete a;

  // << will not work if you make this a shared_ptr<BankAccount>
  auto b = make_shared<CurrentAccount>(123);

  BankAccount* actual = b.get(); // pointer's own operations on a .
  b->deposit(321); // underlying object's operations are on ->
                   // note this expression is identical to what's above
  cout << *b << endl;
  // no delete

  // see shared_ptr in file structure window
}

int main()
{
    smart_pointers();

    getchar();
    return 0;
}
