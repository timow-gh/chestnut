#ifndef CHESTNUT_POINT_HPP
#define CHESTNUT_POINT_HPP

#include <array>
#include <chestnut/traits.hpp>
#include <cstddef>

namespace chestnut
{

template <typename TSize,
          TSize N,
          typename TNumeric,
          typename = std::enable_if_t<is_number_v<TNumeric> && std::numeric_limits<TSize>::is_integer>>
class Point {
public:
  using size_type = TSize;
  using value_type = TNumeric;

private:
  std::array<value_type, N> coordinates;

public:
  using iterator = typename std::array<value_type, N>::iterator;
  using const_iterator = typename std::array<value_type, N>::const_iterator;

  template <typename... TArgs, typename = std::enable_if_t<(sizeof...(TArgs) == N) && (is_number_v<TArgs> && ...)>>
  constexpr explicit Point(TArgs... args)
      : coordinates{args...}
  {
  }

  template <
      typename InputIter,
      typename = std::enable_if_t<std::is_base_of_v<std::input_iterator_tag, typename std::iterator_traits<InputIter>::iterator_category>>>
  constexpr Point(InputIter begin, InputIter end)
  {
    auto dist = std::distance(begin, end);
    if (dist != N)
      std::abort();
    std::copy_n(begin, dist, coordinates.begin());
  }

  template <typename TContainer>
  constexpr explicit Point(const TContainer& container)
      : Point(container.begin(), container.end())
  {
  }

  //  assert(std::distance(container.begin(), container.end()) == N);

  [[nodiscard]] constexpr value_type operator[](size_type index) const { return coordinates[index]; }

  [[nodiscard]] constexpr bool operator==(const Point& other) const { return coordinates == other.coordinates; }
  [[nodiscard]] constexpr bool operator!=(const Point& other) const { return !this->operator==(other); }

  [[nodiscard]] constexpr value_type distance_squared(const Point& other) const
  {
    value_type sum{};
    for (size_type i = 0; i < N; ++i)
    {
      const value_type diff = coordinates[i] - other.coordinates[i];
      sum += diff * diff;
    }
    return sum;
  }
  [[nodiscard]] constexpr value_type distance(const Point& other) const { return std::sqrt(distance_squared(other)); }

  friend std::ostream& operator<<(std::ostream& os, const Point& p)
  {
    for (size_type i = 0; i < N; ++i)
    {
      os << p.coordinates[i] << " ";
    }
    return os;
  }
};

using Point2d = Point<std::size_t, 2, double>;
using Point2f = Point<std::size_t, 2, float>;

using Point3d = Point<std::size_t, 3, double>;
using Point3f = Point<std::size_t, 3, float>;

} // namespace chestnut

#endif // CHESTNUT_POINT_HPP
