#include <chestnut/kdtree.hpp>
#include <gtest/gtest.h>

TEST(point, default_constructor)
{
  chestnut::Point3d point{};
  EXPECT_EQ(point.coordinates[0], 0);
  EXPECT_EQ(point.coordinates[1], 0);
  EXPECT_EQ(point.coordinates[2], 0);
}

TEST(point, constructor)
{
  chestnut::Point3d point(1, 2, 3);
  EXPECT_EQ(point.coordinates[0], 1);
  EXPECT_EQ(point.coordinates[1], 2);
  EXPECT_EQ(point.coordinates[2], 3);
}

TEST(point, constructor_array)
{
  chestnut::Point3d point(std::array<double, 3>{1, 2, 3});
  EXPECT_EQ(point.coordinates[0], 1);
  EXPECT_EQ(point.coordinates[1], 2);
  EXPECT_EQ(point.coordinates[2], 3);
}

TEST(point, distance)
{
  chestnut::Point3d const p1(1, 1, 1);
  chestnut::Point3d const p2(1, 1, 2);
  EXPECT_EQ(p1.distance(p2), 1);
}
