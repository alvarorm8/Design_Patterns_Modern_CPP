#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <sstream>
using namespace std;
#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

struct Address
{
    string street;
    string city;
    int suite;


    Address(const string& street, const string& city, const int suite)
        : street{ street },
        city{ city },
        suite{ suite }
    {
    }

    Address() {} // required for serialization

    /*Address(const Address& other)
        : street{other.street},
        city{other.city},
        suite{other.suite}
    {
    }*/

    template <class archive>
    void serialize(archive& ar, const unsigned version)
    {
        ar& street;
        ar& city;
        ar& suite;
    }

    /*
    The function serialize can be splitted into save and load functions like this:

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    template <class archive>
    void save(archive& ar, const unsigned version) const
    {
        ar << street;
        ar << city;
        ar << suite;
    }

    template <class archive>
    void load(archive& ar, const unsigned version)
    {
        ar >> street;
        ar >> city;
        ar >> suite;
    }*/

    friend ostream& operator<<(ostream& os, const Address& obj);
};

ostream& operator<<(ostream& os, const Address& obj)
{
    return os
        << "street: " << obj.street
        << " city: " << obj.city
        << " suite: " << obj.suite;
}


struct Contact
{
    string name;
    Address* address;

    Contact& operator=(const Contact& other)
    {
        if (this == &other)
            return *this;
        name = other.name;
        address = other.address;
        return *this;
    }

    Contact() /* :name(nullptr), address(nullptr)*/
    {} // required for serialization

    Contact(string name, Address* address)
        : name{ name }, address{ address }
    {
        //this->address = new Address{ *address };
    }

    Contact(const Contact& other)
        : name{ other.name }
        //, address{ new Address{*other.address} }
    {
        address = new Address(
            other.address->street,
            other.address->city,
            other.address->suite
        );
    }
private:
    friend class boost::serialization::access; //so access can access the private members when serializing.

    template <class archive>
    void serialize(archive& ar, const unsigned version)
    {
        ar& name;
        ar& address;
    }

    /*
    The function serialize can be splitted into saveand load functions like this:

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    template <class archive>
    void save(archive& ar, const unsigned version) const
    {
        ar << name;
        ar << address;
    }

    template <class archive>
    void load(archive& ar, const unsigned version)
    {
        ar >> name;
        ar >> address;
    }
    */

public:
    ~Contact()
    {
        delete address;
    }


    friend ostream& operator<<(ostream& os, const Contact& obj);
};

ostream& operator<<(ostream& os, const Contact& obj)
{
    return os
        << "name: " << obj.name
        << " works at " << *obj.address; // note the star here
}

struct EmployeeFactory
{
    static Contact main;
    static Contact aux;

    static unique_ptr<Contact> NewMainOfficeEmployee(string name, int suite)
    {
        //static Contact p{ "", new Address{ "123 East Dr", "London", 0 } };
        return NewEmployee(name, suite, main);
    }

    static unique_ptr<Contact> NewAuxOfficeEmployee(string name, int suite)
    {
        return NewEmployee(name, suite, aux);
    }

private:
    static unique_ptr<Contact> NewEmployee(string name, int suite, Contact& proto)
    {
        auto result = make_unique<Contact>(proto);
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};

Contact EmployeeFactory::main{ "", new Address{ "123 East Dr", "London", 0 } };
Contact EmployeeFactory::aux{ "", new Address{ "123B East Dr", "London", 0 } };

int main()
{
  //This code has memory leaks in address member of Contact, to work properly with it, we should use smart pointers to avoid those leaks.
  {
    // this is tedious since we have to make the each contact manually
    Contact john{ "John Doe", new Address{"123 East Dr", "London", 123} };
    Contact jane{ "Jane Doe", new Address{"123 East Dr", "London", 103} };
  }
  {
    //We can make a very simple implementation of prototype pattern using deep copy with a copy constructor or copy assignment operator
    Contact john{ "John Doe", new Address{"123 East Dr", "London", 123} };
    Contact jane{ john };
    jane.name = "Jane Smith";
    jane.address->suite = 103;
  }
  {
    //Another option is to use a global variable to use it to create new Employees, but is not clear the client that he can use that variable, so
    //a better implementation is through a Factory, making the constructors of Contacts private, etc.

    //This is done in EmployeeFactory, first we create the NewEmployee method as private, which takes the prototype as a parameter. This function is private
    //to later make specializations of it with NewMainOfficeEmployee and NewAuxOfficeEmployee. In the Factory class, we can use static members to generate the 
    //general Contact, and then specialize it with the arguments.
    auto john = EmployeeFactory::NewAuxOfficeEmployee("John Doe", 123);
    auto jane = EmployeeFactory::NewMainOfficeEmployee("Jane Doe", 125);

    cout << *john << "\n" << *jane << "\n";
  }
  {
    /*
    * Instead of having to create copy constructor or copy assignment operator we can use the idea of serialization and deserialization.
    * 
    * Serialize: store all the aspects of an object
    * Deserialize: restore all the aspects of an object
    * 
    * In this example, we will use boost deserialization/serialization.
    * 
    * The advantage of this use is that we can't forget to copy some member, for example if we don't copy the pointers, serialization
    * won't compile, whereas in copy constructor an undesirable shallow copy would happen, so this adds an extra security to our code.
    */
    auto serializeDeserializeFN = [](const Contact& cont) {

      //Serialization
      //We store the info in oss through oa, which calls serialize function by calling oa << cont;
      ostringstream oss;
      boost::archive::text_oarchive oa{ oss };
      oa << cont;
      std::string oastring = oss.str();
      std::cout << oastring << std::endl;

      //Deserialization
      //We load the info from oss and create a new Contact from it. 
      istringstream iss(oastring);
      boost::archive::text_iarchive ia(iss);
      Contact result;
      ia >> result;
      return result;
    };

    auto john = EmployeeFactory::NewAuxOfficeEmployee("John Doe", 123);
    auto jane = serializeDeserializeFN(*john);
    jane.name = "Jane";
    jane.address->suite = 129;

    std::cout << *john << "\n" << jane << std::endl;
  }

  getchar();
  return 0;
}