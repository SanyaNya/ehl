#include "ehl.hpp"
#include <cstdlib>
#include <print>

namespace mylib
{

enum class QuadraticRootError
{
  ImLazyToSupportTwoRoots,
  NoRoots
};

template<auto EHP = ehl::Policy::Exception>
constexpr ehl::Result_t<float, QuadraticRootError, EHP> quadratic_root(float a, float b, float c, [[maybe_unused]] float x) 
  noexcept(EHP != ehl::Policy::Exception)
{
  float D = b*b - 4*a*c;

  EHL_THROW_IF(D > 0, QuadraticRootError::ImLazyToSupportTwoRoots);
  EHL_THROW_IF(D < 0, QuadraticRootError::NoRoots);

  return -b/(2*a);
}

} //namespace mylib

int main()
{
  std::srand(std::time(0));

  std::println("Exception:");
  try
  {
    float r = mylib::quadratic_root(std::rand(), std::rand(), std::rand(), std::rand());
    std::println("Result is: {}", r);
  }
  catch(mylib::QuadraticRootError err)
  {
    std::println(
      "Catch exception QuadraticRootError::{}", 
      err == mylib::QuadraticRootError::NoRoots ? "NoRoots" : "ImLazyToSupportTwoRoots");
  }

  std::println("\nOptional:");
  {
    std::optional<float> r = mylib::quadratic_root<ehl::Policy::Optional>(std::rand(), std::rand(), std::rand(), std::rand());

    if(r) std::println("Result is: {}", r.value());
    else std::println("Optional is null");
  }

  std::println("\nExpected:");
  {
    std::expected<float, mylib::QuadraticRootError> r = 
      mylib::quadratic_root<ehl::Policy::Expected>(std::rand(), std::rand(), std::rand(), std::rand());

    if(r) std::println("Result is: {}", r.value());
    else
      std::println(
        "Get expected QuadraticRootError::{}", 
        r.error() == mylib::QuadraticRootError::NoRoots ? "NoRoots" : "ImLazyToSupportTwoRoots");
  }

  std::println("\nUnreachable:");
  {
    float r = mylib::quadratic_root<ehl::Policy::Unreachable>(std::rand(), std::rand(), std::rand(), std::rand());
    std::println("Result is: {}", r);
  }

  std::println("\nTerminate:");
  {
    float r = mylib::quadratic_root<ehl::Policy::Terminate>(std::rand(), std::rand(), std::rand(), std::rand());
    std::println("Result is: {}", r);
  }
}
