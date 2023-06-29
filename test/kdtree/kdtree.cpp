#include <chestnut/kdtree.hpp>
#include <chestnut/test/test_input.hpp>
#include <gtest/gtest.h>

TEST(kdtree, default_constructor)
{
  chestnut::KdTree<3> const kdtree{};
}

TEST(kdtree, is_empty_on_empty_tree)
{
  chestnut::KdTree<3> kdtree{};
  EXPECT_TRUE(kdtree.is_empty());
}

TEST(kdtree, is_empty)
{
  chestnut::KdTree<3> kdtree{};
  kdtree.insert(chestnut::Point3d{});
  EXPECT_FALSE(kdtree.is_empty());
}

TEST(kdtree, size_on_empty_tree)
{
  chestnut::KdTree<3> kdtree{};
  EXPECT_EQ(kdtree.size(), chestnut::KdTree<3>::size_type{0});
}

TEST(kdtree, size)
{
  chestnut::KdTree<3> kdtree;
  kdtree.insert(chestnut::Point3d{1, 1, 1});
  kdtree.insert(chestnut::Point3d{2, 2, 2});
  EXPECT_EQ(kdtree.size(), chestnut::KdTree<3>::size_type{2});
}

TEST(kdtree, insert_duplicate)
{
  chestnut::KdTree<3> kdtree;
  auto point = chestnut::Point3d{1, 1, 1};
  kdtree.insert(point);
  kdtree.insert(point);
  EXPECT_EQ(kdtree.size(), 2);
}

class KdTreeTest : public ::testing::Test {
protected:
  void SetUp() override
  {
    for (auto const& point: chestnut::test::testPoints)
    {
      kdtree.insert(point);
    }
  }

  std::vector<chestnut::Point3d> points;
  chestnut::KdTree<3> kdtree;
};

TEST(kdtree, contains_on_empty_tree)
{
  chestnut::KdTree<3> kdtree{};
  EXPECT_FALSE(kdtree.contains(chestnut::Point3d{}));
}

TEST_F(KdTreeTest, contains_all_true)
{
  EXPECT_FALSE(kdtree.is_empty());
  for (auto const& point: points)
  {
    EXPECT_TRUE(kdtree.contains(point));
  }
}
