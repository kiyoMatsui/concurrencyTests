#include <iostream>

#include "myExceptions.h"

enum class inWhere {
  base,
  derived,
  both
};

class testClass {
 public:
  testClass() {}
  void notPropergatingUpAsNotConstructor() {
    try {
      throw 1;
    } catch (int e) {
      std::cerr << "all good nothing more should print\n\n";
    }
  }
};
  
class baseClass {
 public:
  baseClass(inWhere x) : member(x) {
    if (x == inWhere::base) 
      throw MyExceptionExp(1); 
  }
  inWhere member;
};

class derivedClass : public baseClass {
 public:
  derivedClass(inWhere x)
  try : baseClass(x) {
    if (x == inWhere::derived) 
      throw MyExceptionExp(2);  
  } catch (MyExceptionExp& e) {
    std::cerr << "Exception caught in try Function block Constructor\n";
  }
};

int tryFunctionBlockConstructor() {
  try {
    testClass a;
    a.notPropergatingUpAsNotConstructor();
  } catch (int e) {
    std::cerr << "this should not print! \n";
  }  
  try {
    derivedClass b(inWhere::base);
  } catch (MyExceptionExp& e) {
    std::cerr << "Exception should be thrown in base class\n";
    std::cerr << "check: does e = 1? e = " << e.getCode() << "\n\n" ;
  }
  
  try {
    derivedClass b(inWhere::derived);
  } catch (MyExceptionExp& e) {
    std::cerr << "Exception should be thrown in derived class\n";
    std::cerr << "check: does e = 2? e = " << e.getCode() << "\n\n" ;    
  }
  return 0;
}
