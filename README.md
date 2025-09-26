# Design Patterns in Modern CPP

This document contains information about the content of the sections and solutions in the repository, so it is easier to navigate and search information.

From section 14, the projects change from VS to VSCode with WSL and docker. As explained in the document *Dev_environment_setup.pdf*.

To install Boost on linux: `sudo apt update && apt upgrade -y && apt install libboost-all-dev`, so it is only necessary for the Visual Studio project that don't have CMake.

## Types of Design Patterns

First of all, a summary of the design patterns types, which are usually categorized in three different groups. This categorization comes after Erich Gamma, one 
of the Ganf of Four authors who wrote the original Design Patterns book.

### Creational Patterns

- They have as objective the creation (construction) of objects.
- It can be through explicit creation (call to constructor) or implicit (Dependency Injection (DI) framework, reflection, etc.).
- Can be Wholesale (a single statement, like a constructor call is enough for the possibility of using the object) or
piecewise (which means more than a statement is necessary to be able to use the object).

The patterns in this group are:

- Builder
- Factories: Abstract Factory and Factory Method
- Prototype
- Singleton

### Structural Patterns

- They are concerned about the structure of the classes (e.g. class members).
- Many patterns are wrappers that mimic the underlying class' interface
- The importance of a good API design has much weight in this kind of patterns.

The patterns in this group are:

- Adapter
- Bridge
- Composite
- Decorator
- Façade
- Flyweight
- Proxy

### Behavioural Patterns

- They are all different: no central theme.
- There's some overlap between them, but they do the same with totally different object oriented mechanism

The patterns in this group are:

- Chain of Responsibility
- Command
- Interpreter
- Iterator
- Mediator
- Memento
- Observer
- State
- Strategy 
- Template Method
- Visitor
- SOLID Principles

## Section 2 - SOLID Design Principles

Summary and explanation of the SOLID Principles.

**SOLID_Principles solution**

This solution has several projects, one for each principle:

*1_Single_Responsibility*

*2_Open_Closed*

*3_Liskov_Substitution*

*4_Interface_Segregation*

*5_Dependency_Inversion*

## Section 3 - Builder

**Motivation**

There are simple objects which can be constructed with one call to its constructor, but there are some more complex.
For those, having constructors with much arguments (10 for example) is not productive, instead, we can use piecewise construction.

When piecewise construction is complex Builder pattern provides an API for constructing an object step by step.

**Builder solution**

*1_Builder*

Basic arquitecture of Builder pattern, with explanations of elements and why this pattern is used.

*2_Groovy-style_Builder*

Example of basic Builder pattern used with uniform initialization for an HTML application.

*3_Builder_Facets*

More complicated example of Builder pattern in which the object to build is very complex, so we need several builders to 
manage different aspects of the object. This is know as a Builder Facets, which combines the Builder and Façade patterns.

The main file is Facets.cpp.

*Assignment*

The assignment of the section is done.

## Section 4 - Factories

**Motivation**

This patterns (or pattern since everything has the same idea of a Factory creation) comes into account when the object creation logic becomes too
complicated even before using it. They're the Abstract Factory and the Factory Method.

This happens for example when the constructors are not descriptive: you can not overload constructor with same arguments and different names, 
if you define multiple optional parameters with default values it can be very confusing for clients to know which arguments have to be passed, which
not, etc. 

Here comes the Factory patterns, which are related to Wholesale construction, not piecewise unlike Builders in which we build the object in several steps.
With Factory patterns, creation of objects can be outsourced to a separate function (Factory Method), a different class (Factory) or create
a hierarchy of factories (Abstract Factory). Here Factory is not an original pattern from the gang of four, but is the same idea of factory patterns.

**Factories solution**

*1_Factory_Method*

The Factory Method pattern is explained with a simple class.

*2_Factory*

The Factory pattern is explained. This is not part of the original Gang of Four patterns, but it is useful enough. It's a specialization of 
the Abstract Factory, since it creates a class but it's not abstract.

*3_Inner_Factory*

Explanation of the problem of the solution 2_Factory and the resolution with Inner Factory pattern.

*4_Abstract_Factory*

The previous sections are all variations of the Factory Method pattern, this is the other type of factories pattern. Abstract Factory is explained
with the 2 variations of it, the Object Oriented approach and the Functional approach.

*Assignment*

The assignment of the section is done.

## Section 5 - Prototype

**Motivation**

This pattern is used to copy objects and create new ones. This is useful when we have an already existing class (Prototype) and we copy it and modify it.

This pattern requires deep copy support. The cloning of the objects has to be convenient, for example, using a Factory.

The definition is basically: A partially or fully initialized object that you copy (clone) and make use of.

**Protoype solution**

*Prototype*

The prototype pattern is shown through copy constructor and assignment operator, a factory method and serialization.

*Assignment*

The assignment of the section is done.

## Section 6 - Singleton

**Motivation**

For some components of a system it only makes sense to have one instance of it, for example, a database repository, an object factory, when the constructor is really expensive
when you don't want copies of the object, etc.

**Singleton solution**

*1_Singleton_Implementation*

The singleton is implemented and several problems are fixed through the DI principle.

*2_Singleton_lifetime_DI_Container*

The singleton pattern is created through a boost DI container.

*3_Monostate*

The Monostate variation of the singleton pattern is shown but it's not recommended to use.

*4_Multiton*

The Multiton variation of the singleton pattern is presented.

*Assignment*

The assignment of the section is done.

## Section 7 - Adapter

**Motivation**

The objective is to get the interface that you want from the interface you have.

**Adapter solution**

*AdapterVisual*

The Adapter pattern is shown in this MFC application. The project does not work for me because of dependencies issues, but the explanations
are done in AdapterVisual.cpp.

*Assignment*

The assignment of the section is done.

## Section 8 - Bridge

**Motivation**

The Bridge pattern is about connecting components together through abstractions. It is a mechanism that decouples an interface from an implementation.
It prevents a "Cartesian Product" complexity explosion.

**Bridge solution**

*1_Pimpl_Idiom*

The Pimpl Idiom is explained since it is a manifestation of the bridge design pattern, but slightly different.

*2_Shrink_Wrapped_Pimpl*

A library component (class) is created so the Pimpl Idiom pattern is easier to use. The class can be imported in any project easily.

*3_Bridge_Implementation*

The Bridge pattern is explained.

*Assignment*

The assignment of the section is done.

## Section 9 - Composite

**Motivation**

The Composite pattern is about treating individual and aggregate objects uniformly. Objects use other objects' fields/properties/members through inheritance and composition (objects as members of other objects).
For example, a grouping of shapes that consist of several shapes. 

So Composite pattern allow us to treat singular objects and composite objects uniformly, for example, Foo and Collection<Foo> have common AP	Is and we can use those APIs without knowing if the object is single or composite.

**Composite solution**

*1_Geometric_Shapes*

Composite pattern is used with shapes to be able to use just one function with single shapes or a group of shapes.

*2_Neural_Network*

Composite pattern is used to simulate the connection between single neurons and a layer of several neurons, all with only 1 function. CRTP (Curiously Recurring Template Pattern) pattern is used too.

*3_Array-Backed_Properties*

An example of an intersection of the composite and proxy patterns is shown. It has to do with the ways that fields are exposed from objects.

*Assignment*

The assignment of the section is done.

## Section 10 - Decorator

**Motivation**

The objective of the pattern is to add behaviour without altering the class itself.

The motivation is when you want new functionality but don't want to break the OCP or don't have access to the source code. Also, you respect the SRP since the new
funcionality is in a new class. You need to be able to interact with the existing structures.

There are two options: aggregate the decorated object as a reference in your new class and add the functionality or, you can inherit from the decorated object.
First option is known as dynamic decorator and the second as static decorator.

**Decorator solution**

*1_Dynamic_Decorator*

Dynamic, static and functional decorator are explained with their advantages and disadvantages.

*Assignment*

The assignment of the section is done.

## Section 11 - Façade

**Motivation**

The objective of this pattern is to expose several components through a single interface.

The motivation comes with the fact that end-users of a software do not want to know about all the complexity and implementation details, they want to use it the simples way possible and that it is usable.

So the façade provides a simple, easy to understand/user interface over a large and sophisticated body of code.

**Bloom solution**

*Bloom*

A project from the professor is given where a console can be build and shown, but all the implementation details (creating a buffer, adding values, showing the window...) are hidden in a façade.
The main files are Bloom.cpp and Console.h.

## Section 12 - Flyweight

**Motivation**

The objective of this pattern is the space optimization. The idea is to avoid redundancy when storing data by storing externally the data associated with similar objects.

**Flyweight solution**

*1_Handmade_Flyweight*

The flyweight pattern is used both handmade and with boost library.

*2_Text_Formatting*

The flyweight pattern is used with an application of text formatting.

*Assignment*

The assignment of the section is done.

## Section 13 - Proxy

**Motivation**

A proxy is an inteface for accessing a particular resource. This interface looks like the interface of the object but in the backend it's behaviour is completely different.

There are different types of proxies, depending on how it access the properties: communication, logging, virtual, guarding, etc. The reasons to build proxies are: the resource is remote, is expensive to construct, may require logging, etc.

**Proxy solution**

*1_Smart_pointers*

This solution explains that smart pointers are proxies.

*2_Property_proxy*

Property proxy is explained.

*3_Virtual_proxy*

Virtual proxy is explained.

*4_Communication_proxy*

Communication proxy is explained. There's a zip with the project with all the dependencies, the file here is only for knowledge.

*Assignment*

The assignment of the section is done.

## Section 14 - Chain of Responsibility

**Motivation**

It is a chain of components who all get a chance to process a command or a query, optionally having default processing implementation and abilitiy to terminate the processing chain. So the elements up in the chain don't make their processing.

**Folders in the section**

*1_pointer_chain*

Explains the classical way of doing a Chain of Responsibility pattern.

*2_broker_chain*

Explains the modern way of doing a Chain of Responsibility pattern.

*3_assignment*

The assignment of the section is done.

## Section 15 - Command

**Motivation**

Ordinary C plus plus statements that you make they are what I would call perishable, meaning that after you assign a field, there is no record anywhere that the field has been assigned.
This means that you cannot simply go ahead and undo a field or a property assignment or whatever it is that you are doing. And also the downside of this is you cannot take a sequence of the actions that you just made and you cannot serialize them to some database or something because that is actually something that you sometimes want.

So what we want to do with the Command design pattern is we want to have a separate object which represents a particular operation. The most common use of the Command design pattern is GUI commands.

So a command is an object which represents an instruction or a set of instructions to perform a particular action. Contains all the information that is necessary for the action to be taken.

There is one thing that I wanted to mention which isn't directly tied to the subject of the Command design pattern, and that is this idea of command query separation (cqs) (seen in Section 14 subsection 2), because the word command appears as part of the command design pattern.

So let's just remind ourselves what a command is. So a command is when you're asking for an action. And typically in the concept of command query separation, a command is something which is mutable in the sense that it causes a mutation of the object, but it doesn't have a return value, it doesn't have any result. Now, in command query separation, we separate the commands from the queries. And the second part of this is a query. So a query is when you're asking for information and queries are typically not causing any mutation.

So we have this idea of command query separation, where you basically split your system into separate components and separate means of sending commands. So asking for changes and sending queries as well, and those can be implemented by the same components or you can completely separate the system.

Now the reason why this is mentioned it is because the Gang of four doesn't mention queries. The Gang of four only mentions the command design pattern, but in the context of the Gang of Four book, I would say that both commands and queries, since they are wrapping some instructions in an object, they are both represented by the command design pattern.

**Folders in the section**

*1_Comand*

This section explains the Command pattern design with an example of a Bank Account.

*2_Undo_Operations*

This section extends the section 1 adding the undo operations to the example.

*3_Composite_Command_(Macro)*

This section takes the same example and enhaces it mixing the Command design pattern the Composite design pattern.

*4_Assignment*

The assignment of the section is done.

## Section 16 - Interpreter

**Motivation**

The interpreter pattern is everywhere in programming. Some examples are the programming languages compilers, interpreters for languages like python, HTML, XML, regular expressions... all those have in common the idea of taking strings and turning them into object oriented objects.

The challenge of the interpreter design pattern is turning strings into object oriented structures. It is a component which processes structured text data using two stages. The first one is called lexing and it turns the string into separate lexical tokens (split it into different self-contained pieces of information with no semantic meaning). The second stage is called parsing, which takes the sequence of tokens and tries to turn it into some sort of meaningful, object oriented representation.

**Folders in the section**

*1_handmade_interpreter*

A handmade interpreter is done in this section.

*2_interpreter_boost_spirit*

An example of a real life project for designing a programming language. It is a Visual Studio Solution whose URL is https://github.com/nesteruk/tlon.

So essentially the programming language doesn't compile into native code. What it does instead is it gets translated into C++. So this kind of construct is made possible because it uses a library in order to help building the language. And the library is called Boost Spirit.

The files of the library allow you to build the parser using some predefined constructs.

In the ast.hpp file, the definition of the abstract syntax tree that the project has for the different parts of the language is presented. It uses a two part or double dispatch visitor. The interesting thing about this is that all of these elements are subsequently adapted using boost fusion. Now Boost Fusion is yet another library that's actually being used by Boost spirit. The reason why it is used is so that when we actually build the parsing process, it can leverage all the *BOOST_FUSION_* structures defined.

In the parser.hpp file, we have a few predefined structures from Boost spirit, and these predefined structures are, for example, the grammar base class. So we're defining a grammar for a particular kind of file. In this case, it's a file in the learn programming language. Certain rules for the grammar are defined. The grammar is kind of like the backus-naur form. If you're not familiar with the Backus-naur form, it's kind of like regular expressions, but for languages as opposed to text. So having constructed all of this, what I then do is I use some of the code from Spirit once again in order to parse a string. So I have an input file, I pass the entire file and I try to get it into this object oriented format and subsequently print it into C plus plus. 

In the cpp_printer.hpp a printer is defined. So essentially a printer is just a visitor that does double dispatch, it inherits from a printer base class and in the file, special rules are created for printing.

So this is essentially an illustration of how using a framework can let you make a parser more convenient. Now one thing you'll notice it's also very important to note is that there is no explicit lexer here, there is no explicit lexical part at no point in time am I keeping lists of tokens. This might be done behind the scenes, but I don't really care because all I'm interested in is basically taking a large chunk of text turning it into some object oriented structure and then traversing that structure using a visitor to actually print something meaningful on the right hand side.

## Section 17 - Iterator

**Motivation**

Iteration (traversal) is a core functionality of various data structures. 

An iterator is a class that facilitates the traversal

- Keeps a reference to the current element
- Knows how to move to a different element

Can be used implicitly  (e.g. Range-based for, coroutines)


**Folders in the section**

## Section 18 - Mediator

**Motivation**



**Folders in the section**

## Section 19 - Memento

**Motivation**



**Folders in the section**

## Section 20 - Observer

**Motivation**



**Folders in the section**

## Section 21 - State

**Motivation**



**Folders in the section**

## Section 22 - Strategy

**Motivation**



**Folders in the section**

## Section 23 - Template Method

**Motivation**



**Folders in the section**

## Section 24 - Visitor

**Motivation**



**Folders in the section**

## Section 25 - Course Summary
