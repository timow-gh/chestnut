#ifndef CPP_LIB_TEMPLATE_LIBRARY_H
#define CPP_LIB_TEMPLATE_LIBRARY_H

#include <array>
#include <chestnut/point.hpp>
#include <cmath>
#include <memory>
#include <vector>

namespace chestnut
{

// See https://rosettacode.org/wiki/K-d_tree#C++
// - kdtree move only
// - nodes in a vector
// - recursive tree building
// - node pointer into the array for the tree

namespace details
{

template <typename TPoint>
struct Node
{
  TPoint point{};
  Node* left{nullptr};
  Node* right{nullptr};

  explicit Node(TPoint point)
      : point(point)
  {
  }

  ~Node()
  {
    if (left != nullptr)
      delete left;
    if (right != nullptr)
      delete right;
  }
};
} // namespace details

template <std::size_t N, typename TPoint>
class KdTree {
public:
  using size_type = std::size_t;
  using value_type = typename TPoint;
  using node_type = details::Node<value_type>;

private:
  node_type* root{nullptr};

public:
  // Allows for duplicate points in the tree
  void insert(value_type point)
  {
    if (root == nullptr)
    {
      root = new node_type(point);
      return;
    }

    node_type* current = root;
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

  [[nodiscard]] bool is_empty() const { return root == nullptr; }

  [[nodiscard]] size_type size() const
  {
    if (root == nullptr)
      return 0;

    std::size_t size{0};
    std::vector<node_type*> nodes;
    nodes.push_back(root);
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

  [[nodiscard]] bool contains(const value_type& point) const
  {
    if (root == nullptr)
      return false;

    std::size_t depth{0};
    node_type* node = root;
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
};

} // namespace chestnut

#endif // CPP_LIB_TEMPLATE_LIBRARY_H
