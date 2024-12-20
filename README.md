# Error Handling Library

Header only library, that lets user to choose error handling mechanism in your library

## HowTo

For function return type use 
~~~cpp
template<ehl::Policy EHP>
ehl::Result_t<T, E, EHP>
~~~
 whereis:
* T - return type
* E - error type
* EHP - ehl::Policy

#### Note: EHP variable must always be named like EHP


Error handling mechanism defined in ehl::Policy enum:
~~~cpp
enum class Policy
{
  Exception,  //throw exception
  Optional,   //return std::optional
  Expected,   //return std::expected
  Terminate,  //call std::terminate
  Unreachable //call std::unreachable(tell compiler that error can not happen, otherwise UB)
};
~~~

For returning error from function use
~~~cpp
EHL_THROW_IF(condition, error)
~~~


## Simple example
See it in Compiler Explorer: https://godbolt.org/z/3Wbffzc95
~~~cpp
#include "ehl/ehl.hpp"

enum class MyError
{
  NullPointer
};

template<auto EHP = ehl::Policy::Exception> //default Exception policy
[[nodiscard]] //do not ignore error
ehl::Result_t<int, MyError, EHP> myfunc(int* p) noexcept(EHP != ehl::Policy::Exception) // does not throw exception if policy is not Exception
{
  EHL_THROW_IF(p == nullptr, MyError::NullPointer); // return MyError::NullPointer if p == nullptr

  return *p;
}

extern int* p;

int main()
{
  std::optional<int> i = myfunc<ehl::Policy::Optional>(p);
  if(i) return i.value();
}
~~~

#### Requirements: C++23

## Using with cmake
~~~cmake
include(FetchContent)

FetchContent_Declare(
  ehl
  GIT_REPOSITORY https://github.com/SanyaNya/ehl
  GIT_TAG v1.1.1)

FetchContent_MakeAvailable(ehl)

target_link_libraries(your_target ehl)
~~~
