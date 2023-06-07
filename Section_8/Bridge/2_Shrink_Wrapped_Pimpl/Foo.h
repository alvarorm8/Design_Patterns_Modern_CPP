#pragma once

#include "pimpl.h"

/*
* In this class we are using the pimpl class generated so the Pimpl design can be used in an easier way. 
* 
* All the details of the Pimpl pattern are in the pimpl class imported, so here we only have to define the impl class
* with all the implementation details we don't want to share.
* 
* As a summary: in impl member (which is of type pimpl) we have a pointer of type impl class (inner class of Foo).
*/

class Foo
{
  class inner;

  pimpl<inner> inside;

  //Added by me
public:
  Foo() = default;
  int greet();
};


