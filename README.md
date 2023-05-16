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

### SOLID_Principles Solution

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

*1_Builder*

Basic arquitecture of Builder pattern, with explanations of elements and why this pattern is used.

*2_Groovy-style_Builder*

Example of basic Builder pattern used with uniform initialization for an HTML application.

*3_Builder_Facets**

More complicated example of Builder pattern in which the object to build is very complex, so we need several builders to 
manage different aspects of the object. This is know as a Builder Facets, which combines the Builder and Façade patterns.

The main file is Facets.cpp.

## Section 4 - Factories

## Section 5 - Prototype

## Section 6 - Singleton

## Section 7 - Adapter

## Section 8 - Bridge

## Section 9 - Composite

## Section 10 - Decorator

## Section 11 - Façade

## Section 12 - Flyweight

## Section 13 - Proxy

## Section 14 - Chain of Responsibility

## Section 15 - Command

## Section 16 - Interpreter

## Section 17 - Iterator

## Section 18 - Mediator

## Section 19 - Memento

## Section 20 - Observer

## Section 21 - State

## Section 22 - Strategy 

## Section 23 - Template Method

## Section 24 - Visitor

## Section 25 - Course Summary
