#include <chestnut/traits.hpp>
#include <gtest/gtest.h>

TEST(trait, is_number)
{
  static_assert(!chestnut::is_number_v<bool>);        // true
  static_assert(chestnut::is_number_v<int>);          // true
  static_assert(chestnut::is_number_v<int const>);    // true
  static_assert(!chestnut::is_number_v<int&>);        // false
  static_assert(!chestnut::is_number_v<int*>);        // false
  static_assert(chestnut::is_number_v<double>);       // true
  static_assert(chestnut::is_number_v<double const>); // true
  static_assert(chestnut::is_number_v<float>);        // true
  static_assert(chestnut::is_number_v<float const>);  // true
  static_assert(chestnut::is_number_v<long>);         // true
  static_assert(chestnut::is_number_v<long const>);   // true
  static_assert(!chestnut::is_number_v<float&>);      // false
  static_assert(!chestnut::is_number_v<float*>);      // false
  static_assert(!chestnut::is_number_v<char>);        // false
  static_assert(!chestnut::is_number_v<char const>);  // false
  static_assert(!chestnut::is_number_v<char&>);       // false
  static_assert(!chestnut::is_number_v<char*>);       // false
}