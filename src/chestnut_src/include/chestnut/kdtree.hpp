#ifndef CPP_LIB_TEMPLATE_LIBRARY_H
#define CPP_LIB_TEMPLATE_LIBRARY_H

#include <array>
#include <cmath>
#include <memory>
#include <type_traits>
#include <vector>

namespace chestnut
{

template <std::size_t N, typename TFloat>
struct Point {
  using value_type = TFloat;

  std::array<value_type, N> coordinates;
  Point() = default;
  Point(value_type x, value_type y, value_type z)
      : coordinates(std::array<value_type, 3>{x, y, z})
  {}
  explicit Point(std::array<value_type, N> coordinates)
      : coordinates(coordinates)
  {}

  value_type distance(const Point& other) const
  {
    value_type sum{};
    for (std::size_t i = 0; i < N; ++i)
    {
      sum += (coordinates[i] - other.coordinates[i]) * (coordinates[i] - other.coordinates[i]);
    }
    return std::sqrt(sum);
  }

  value_type operator[](std::size_t index) const { return coordinates[index]; }

  bool operator==(const Point& other) const { return coordinates == other.coordinates; }
  bool operator!=(const Point& other) const { return coordinates != other.coordinates; }

  friend std::ostream& operator<<(std::ostream& os, const Point& p)
  {
    for (std::size_t i = 0; i < N; ++i)
    {
      os << p.coordinates[i] << " ";
    }
    return os;
  }
};

using Point2d = Point<2, double>;
using Point3d = Point<3, double>;
using Point2f = Point<2, float>;
using Point3f = Point<3, float>;
using Point2i = Point<2, int>;
using Point3i = Point<3, int>;

} // namespace chestnut

// See https://rosettacode.org/wiki/K-d_tree#C++
// - kdtree move only
// - nodes in a vector
// - recursive tree building
// - node pointer into the array for the tree

namespace details
{
template <typename TPoint>
struct Node {
  TPoint point{};
  Node* left{nullptr};
  Node* right{nullptr};

  explicit Node(TPoint point)
      : point(point)
  {}

  ~Node()
  {
    if (left != nullptr)
      delete left;
    if (right != nullptr)
      delete right;
  }
};

// Traits that imitate type_traits features of older c++ standards than cxx11
template <typename T, typename... Args>
constexpr bool is_any_of_v = std::disjunction_v<std::is_same<T, Args>...>;

template <typename T>
constexpr bool is_floating_point_v = is_any_of_v<std::remove_cv_t<T>, float, double, long double>;

} // namespace details

namespace chestnut
{

template <std::size_t N, typename T = double, typename TPoint = chestnut::Point<N, T>>
class KdTree {
public:
  using size_type = std::size_t;
  using value_type = std::decay_t<typename TPoint>;
  static_assert(details::is_floating_point_v<typename TPoint::value_type>, "Only floating point types are supported.");
  using node_type = details::Node<value_type>;

private:
  node_type* m_root{nullptr};

public:
  KdTree() = default;
  KdTree(const KdTree&) = delete;
  KdTree& operator=(const KdTree&) = delete;
  KdTree(KdTree&& kdtree) noexcept
  {
    this->m_root = kdtree.m_root;
    kdtree.m_root = nullptr;
  }

  KdTree& operator=(KdTree&& kdtree) noexcept
  {
    this->m_root = kdtree.m_root;
    kdtree.m_root = nullptr;
  }

  ~KdTree()
  {
    if (m_root)
    {
      delete m_root;
    }
  }

  // Allows for duplicate points in the tree
  void insert(value_type point)
  {
    if (m_root == nullptr)
    {
      m_root = new node_type(point);
      return;
    }

    node_type* current = m_root;
    std::size_t depth = 0;
    while (true)
    {
      std::size_t axis = depth % N;
      if (point[axis] < current->point[axis])
      {
        if (current->left == nullptr)
        {
          current->left = new node_type(point);
          return;
        }
        current = current->left;
      }
      else
      {
        if (current->right == nullptr)
        {
          current->right = new node_type(point);
          return;
        }
        current = current->right;
      }
      ++depth;
    }
  }

  [[nodiscard]] bool is_empty() const noexcept { return m_root == nullptr; }

  [[nodiscard]] size_type size() const
  {
    if (m_root == nullptr)
      return 0;

    std::size_t size{0};
    std::vector<node_type*> nodes;
    nodes.push_back(m_root);
    while (!nodes.empty())
    {
      node_type* node = nodes.back();
      nodes.pop_back();
      ++size;
      if (node->left != nullptr)
        nodes.push_back(node->left);
      if (node->right != nullptr)
        nodes.push_back(node->right);
    }
    return size;
  }

  [[nodiscard]] bool contains(const value_type& point) const noexcept
  {
    if (m_root == nullptr)
      return false;

    std::size_t depth{0};
    node_type* node = m_root;
    while (node)
    {
      if (node->point == point)
        return true;

      std::size_t axis = depth % N;
      if (point[axis] < node->point[axis])
      {
        if (!node->left)
          return false;
        node = node->left;
      }
      else
      {
        if (!node->right)
          return false;
        node = node->right;
      }

      depth++;
    }
    return false;
  }

  std::vector<value_type> nearestNeighbour() const { std::vector<value_type> result; }
};

} // namespace chestnut

#endif // CPP_LIB_TEMPLATE_LIBRARY_H
