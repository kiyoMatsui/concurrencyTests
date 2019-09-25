#ifndef MYEXCEPTIONS
#define MYEXCEPTIONS
/*
From Jon Kalb talk
Do not use dynamic exception specifications, noexcept depricates them.
All code can throw! -unless you think otherwise.
std::swap is noexcept (as long as they are with noexcept move operators).

Exception Safety Guarantees
Basic: Just maintains invarients and no leaks.
Strong:  is "do or not do..." like db transactions.
No-Throw: " will not emit exception (or is handled inside).

no throw swap if move operations are no throw
check swap makes sure swap at compile time is noexcept, so move constructor/assignment are noexcept 
check swap in any class member "void AnyMember() {mCheckSwap::checkSwap(this); ...}"

A quick note on inheritance specifiers (virtual helps with common base classes in hierarchies, i.e. diamond problem)
<members>   <public in>   <protected in>   <private in>
public:     public        protected        private
protected:  protected     protected        private 
private:    !accessible   !accessible      !accessible

*/

#include <exception>
#include <type_traits>

struct MyException : virtual public std::exception {
  const char* what() const noexcept {return "called MyException";}
};

struct MyException2 : virtual public std::exception {
  const char* what() const noexcept {return "called MyException2";}
};

class MyExceptionExp : virtual public std::exception {
 public:
  MyExceptionExp(unsigned int a) : x(a) {}
  unsigned int getCode() const { return x; }
  const char* what() const noexcept {return "called MyExceptionExp";}

 private:
  const unsigned int x;
};

struct MyExceptionHierarchy : virtual public MyException, virtual public MyException2 {
  const char* what() const noexcept {return "called MyExceptionHierarchy";}
};
  
namespace mCheckSwap { // probably just use: static_assert(std::is_nothrow_swappable<T>::value, "is_nothrow_swappable"); //c++17
template <typename T> void checkSwap(T* const t = 0) {
  //static_assert(noexcept(delete t),           "destructor is not noexcept"); //old but uses noexcept as operator
  //static_assert(noexcept(T(std::move(*t))),   "move construction is not noexcept");
  //static_assert(noexcept(*t = std::move(*t)), "move assignment is not noexcept"); 
  static_assert(std::is_nothrow_move_constructible<T>::value, "is_nothrow_move_constructible");// c++11
  static_assert(std::is_nothrow_move_assignable<T>::value, "is_nothrow_move_assignable"); 
}
} // namespace 

#endif
/*
Widget& Widget::operator=(Widget const& rhs) {
 T1 tempT1(rhs.t1_); //might throw
 T2 tempT2(rhs.t1_); //might throw
 //The Critical Line
 t1_.swap(tempT1); //won't throw with guarantees
 t2_.swap(tempT2); //won't throw with guarantees
}
// Strong Guarantee achieved! if throws object is unchanged.
*/
