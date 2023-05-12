#include <vector>
struct Document;

/*
* Interface Segregation Principle: Not create interfaces which are too large, which require too much implementation later.
* 
* Here struct IMachine has no problem at all, it would be ok, but what happens if you want to implement
* only a scanner or only a printer, you are forced to implement all the 3 methods. With this approach
* you're giving the client a wrong idea, because if you implement all 3 methods and only scan actually
* does some work (in a scanner for example) and the others are blank bodies, the API still gives the option 
* of printing and faxing something because the interface is too big.

* So it is better to implement small interfaces which segregate the functionalities needed.
* 
* Still, if you want to have a more complex machine which makes more than one functionality, you can always
* create new interfaces inheriting from the single interfaces you need, for example, IMachine.
*/

//struct IMachine
//{
//  virtual void print(Document& doc) = 0;
//  virtual void fax(Document& doc) = 0;
//  virtual void scan(Document& doc) = 0;
//};
//
//struct MFP : IMachine
//{
//  void print(Document& doc) override;
//  void fax(Document& doc) override;
//  void scan(Document& doc) override;
//};

// 1. Recompile
// 2. Client does not need this
// 3. Forcing implementors to implement too much

struct IPrinter
{
  virtual void print(Document& doc) = 0;
};

struct IScanner
{
  virtual void scan(Document& doc) = 0;
};

struct IFax
{
    virtual void fax(Document& doc) = 0;
};

struct Printer : IPrinter
{
  void print(Document& doc) override;
};

struct Scanner : IScanner
{
  void scan(Document& doc) override;
};

struct IMachine: IPrinter, IScanner
{
};

struct Machine : IMachine
{
  IPrinter& printer;
  IScanner& scanner;

  Machine(IPrinter& printer, IScanner& scanner)
    : printer{printer},
      scanner{scanner}
  {
  }

  void print(Document& doc) override {
    printer.print(doc);
  }
  void scan(Document& doc) override;
};

// IPrinter --> Printer
// everything --> Machine