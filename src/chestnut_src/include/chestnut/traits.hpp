#ifndef CHESTNUT_TRAITS_HPP
#define CHESTNUT_TRAITS_HPP

#include <type_traits>

namespace chestnut
{

template <typename T>
struct is_number
    : std::integral_constant<bool,
                             std::is_arithmetic_v<T> && !std::is_same_v<bool, std::decay_t<T>> && !std::is_same_v<char, std::decay_t<T>>>
{
};

template <typename T>
constexpr bool is_number_v = is_number<T>::value;

} // namespace chestnut

#endif // CHESTNUT_TRAITS_HPP
