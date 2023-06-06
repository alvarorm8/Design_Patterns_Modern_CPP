# Design Patterns in Modern CPP

This document contains information about the content of the sections and solutions in the repository, so it is easier to navigate and search information.

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

*3_Liskov_Substitution**

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

*3_Builder_Facets**

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



**Bridge solution**

## Section 9 - Composite

**Motivation**



**Composite solution**

## Section 10 - Decorator

**Motivation**



**Decorator solution**

## Section 11 - Façade

**Motivation**



**Facade solution**

## Section 12 - Flyweight

**Motivation**



**Flyweight solution**

## Section 13 - Proxy

**Motivation**



**Proxy solution**

## Section 14 - Chain of Responsibility

**Motivation**



**Adapter solution**

## Section 15 - Command

**Motivation**



**Command solution**

## Section 16 - Interpreter

**Motivation**



**Interpreter solution**

## Section 17 - Iterator

**Motivation**



**Iterator solution**

## Section 18 - Mediator

**Motivation**



**Mediator solution**

## Section 19 - Memento

**Motivation**



**Memento solution**

## Section 20 - Observer

**Motivation**



**Observer solution**

## Section 21 - State

**Motivation**



**State solution**

## Section 22 - Strategy

**Motivation**



**Strategy solution**

## Section 23 - Template Method

**Motivation**



**Template_Method solution**

## Section 24 - Visitor

**Motivation**



**Visitor solution**

## Section 25 - Course Summary
