# Design Patterns in Modern CPP

This document contains information about the content of the sections and solutions in the repository, so it is easier to navigate and search information.

From section 14, the projects change from VS to VSCode with WSL and docker. As explained in the document *Dev_environment_setup.pdf*.

To install Boost on linux: `sudo apt update && sudo apt upgrade -y && sudo apt install libboost-all-dev`, so the folder 3rdParty is only necessary for the Visual Studio projects that don't have CMake.

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

*3_Assignment*

The assignment of the section is done.

## Section 17 - Iterator

**Motivation**

Iteration (traversal) is a core functionality of various data structures. 

An iterator is a class that facilitates the traversal

- Keeps a reference to the current element
- Knows how to move to a different element

Can be used implicitly  (e.g. Range-based for, coroutines)

Typically requires of != and ++ operators.

**Folders in the section**

*1_Iterator*

Implementation of the iterator pattern using std iterators, later a manual implementation which is harder to understand and create, and lastly implementation using coroutines, which eases the implementation.

*2_Boost_iterator*

Implementation of the iterator using Boost iterator facade, which facilitates the implementation.

*3_Assignment*

The assignment of the section is done.

## Section 18 - Mediator

**Motivation**

Facilitates the communication between components by letting the components be aware of the presence or absence of the others.

Components may go in a out of a system at any time, so it makes no sense to have direct references to one another since the references may go dead.

The solution is to make all the components to refer to some central component which facilitates the communication.

The mediator is a component that facilitates the communication between other components without them necessarily being aware of each other or having a direct reference to each other.

The mediator usually is a singleton since there's only one in the entire system. It engages bidirectinoal communication with its connected components (the mediator has functions which the components can call,
and viceversa). It is usually included in the constructor as a parameter to ensure that the mediator is available in all the components.

**Folders in the section**

*1_ChatRoom*

The classic example of the Mediator pattern is developed. In this example a chatroom is generated, where people join and can chat.

*2_EventBroker*

An event broker is implemented in this section (this was also seen in the chain of responsibility section). In the chain of responsibility we look to build a sequence of objects which can process
a particular event one after another. Here, we are interested in delivering the events in a centralised way. This centralisation is going to be developed using the observer pattern and the mediator pattern.

*3_Assignment*

The assignment of the section is done.

## Section 19 - Memento

**Motivation**

Keep a memento (memories) of an object's state to return to that state.

An object goes through a set of changes, there are different ways of navigating through those changes:

- One way is to recorde every change (Command pattern) and teach a command to "undo" itself.
- Another way is to save snapshots of the system and allow to go back a particular snapshot (simpler way).

A memento is a class which represents a token or identifier representing the system state. It lets us roll back to the state whe the token was generated. The token may or may not directly expose state information, but typically
is unmutable and does not have functions on its own appart from the constructor/destructor, so you can see the information of the state, but it does not allow you to change the system unless you explicitly insert the token into the system and roll back to the state.

There are also cases when a memento causes the restoration of a state in it´s destructor. For example if we have a system which is peforming some actions, like printing data with a specific indentation, we can 
have a class which serves as memento whose constructor increases the indentation of the printer, and its destructor decreases again the indentation of the printer. In this way, if we create an object as a local variable
of the memento class in a function, and print whatever we want, at the exit of the function the memento object will be destroyed, so the indentation will be back at the initial state. This kind of memento is an alternative
approach, since we don´t explicitly use the memento to restore to a specific state, but it is done automatically.


**Folders in the section**

*1_Memento*

A memento example is created with a Bank Account. Several options like restore the bank to a specific state, undo and redo operations, etc., are added.

*2_Assignment*

The assignment of the section is done.

## Section 20 - Observer

**Motivation**

Getting notification when things happen.

Sometimes we need to be informed when certain things happen:

- Object's field changes
- Object does something
- Some external event occurs

We want to listen to events and notified when they occur.

The terms are event or signal for the things that happen, and subscriber or slot for the ones intereted in receiving the notifications. The first one is for the general case
while the second one is used in libraries like the boost signals library.

An observer is an object that wishes to be informed about events happening in the system. The entity generating the events is an observable.

The observable provides a way of subscribing to an event (signal)
The obsever performs the subscription

**Folders in the section**

*1_Observer*

An observer example is created both with manual implementation and with boost:signals2 library, which eases the implementation.

*2_Assignment*

The assignment of the section is done.

## Section 21 - State

**Motivation**

The state design pattern is a pattern in which the object's behaviour is determined by its state. An object transitions from one state to another (something needs to trigger a transition).

A formalised construct which manages state and transitions is called a state machine. This usually is class, which can be developed by ourselves or imported from another library. Normally this second
approach is better, since the library is more robust and offers additional funcionalities.

This design pattern makes sense when the complexity is sufficient.

**Folders in the section**

*1_Classic*

The classic way of creating the state machine is shown. This implementation is currently not used since the way of implementing it is not realistic in modern code.

*2_Handmade*

A handmade example of the state pattern is shown. This type of implementation is easier than the previous one, basically based on enumerations and maps to define the state machine.

*3_Boost_MSM*

The state machine is created using Boost MSM (meta state machine) library. Boost has two libraries for state machines, this is one of them.

*4_Assignment*

The assignment of the section is done.

## Section 22 - Strategy

**Motivation**

System behaviour partially specified at runtime. 

Many algorithms can be decomposed into higher and lower level parts. The high level algorithm can be reused, while the low level parts are specific to the different problems.

The Strategy design patern enables the exact behaviour of a system to be selected either at run-time (dynamic strategy) or compile-time (static strategy). This is also known as policy, specially in the C++ world.

In the dynamic strategy, we can change the selection in runtime, while on the static strategy, we can not do this.

**Folders in the section**

*1_Dynamic_Strategy*

An example of dynamic strategy is implemented where we can select to print data in different formats.

*2_Static_Strategy*

An example of static strategy is implemented where we can select to print data in different formats.

*3_Assignment*

The assignment of the section is done.

## Section 23 - Template Method

**Motivation**

A high-level blueprint for an algorithm to be completed by inheritors.

As we have seen in the Strategy pattern, algorithms can be decomposed into common parts (high level) + specific parts (low levels). 

The Strategy design pattern does this through composition:
    - High-level algorithm uses an interface
    - Concrete implementations implement the interface

The Template design pattern does this through inheritance:
    - Overall algorithm makes use of abstract member
    - Inhertitors override the abstract member

The Template method design pattern allows us to define the 'skeleton' of the algorithm, with concrete implementations defined in subclasses.

**Folders in the section**

*1_Template_Method*

An example of the Template Method pattern is implemented with an example of a game with different players.

*2_Assignment*

The assignment of the section is done.

## Section 24 - Visitor

**Motivation**

This is a complex pattern. Let´s suppose we have a hierarchy of documents elements and you need to defined some new operation on an entire class hierarchy.

You don´t want to keep modifying every class in the hierarchy, since this is very tedious and breaks the open close principle (if you have code that has been already
tested, you don't want to modify it, instead you should use inheritance for example) and the single responsibility principle (you are adding more functionality to the classes).

The downside is that you need access to the non-common aspects of classes in the hierarchy, since for all the elements in the classes a single interface wouldn't work.

Instead, you want to create an external component to handle the new operations, taking the objects and operating with them. The way of working should avoid type checks, since the usage
of dynamic casting to check the type is possible but it is not scalable.

So, the visitor design pattern is a pattern where a component (visitor) is allowed to traverse the entire inheritance hierarchy. Implemented by propagating a single visit() method throughout
the entire hierarchy, instead of implementing the visit method in each visitor. This way you have the hierarchy with the visit method, and then you can define visitors, which fulfills the 
open close and single responsibility principles.

**Folders in the section**

*1_Intrusive_visitor*

*2_Reflective_visitor*

*3_Classic_visitor*

*4_Acyclic_visitor*

*5_Multimethods*

*6_Variant_and_std_visit*

*7_Assignment*

The assignment of the section is done.

## Section 25 - Course Summary
