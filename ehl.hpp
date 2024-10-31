#pragma once

/* Features:
 *
 * Done:
 * 1. User should choose error handling mechanism 
 * 2. Specialization of error handling mechanism per function or scope or global
 *
 * TODO:
 * 3. Compose multiple errors
 * 4. Specialization of error handling mechanism per error
 * 5. Zero cost wrappers
 * 6. Support Boost.Stacktrace*/

#include <type_traits>
#include <utility>
#include <optional>
#include <expected>
#include <cassert>

#define EHL_POLICY(P) [[maybe_unused]] constexpr auto EHP = ehl::Policy::P

#define EHL_THROW_IF(COND, ERR)                                               \
  do                                                                          \
  {                                                                           \
    if constexpr(EHP == ehl::Policy::Unreachable) assert(!(COND));            \
                                                                              \
    if(COND) [[unlikely]]                                                     \
    {                                                                         \
      if constexpr(EHP == ehl::Policy::Exception) throw (ERR);                \
      if constexpr(EHP == ehl::Policy::Optional) return std::nullopt;         \
      if constexpr(EHP == ehl::Policy::Expected) return std::unexpected(ERR); \
      if constexpr(EHP == ehl::Policy::Terminate) std::terminate();           \
      if constexpr(EHP == ehl::Policy::Unreachable) std::unreachable();       \
    }                                                                         \
  }while(0)

namespace ehl
{

enum class Policy
{
  Exception,
  Optional,
  Expected,
  Terminate,
  Unreachable
};

template<typename T, typename E, Policy P>
struct Result : std::type_identity<T> {};

template<typename T, typename E>
struct Result<T, E, Policy::Expected> : std::type_identity<std::expected<T, E>> {};

template<typename T, typename E>
struct Result<T, E, Policy::Optional> : std::type_identity<std::optional<T>> {};

template<typename T, typename E, Policy P>
using Result_t = typename Result<T, E, P>::type;

} //namespace ehl
