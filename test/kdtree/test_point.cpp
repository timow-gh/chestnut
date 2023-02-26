#include "chestnut/kdtree.hpp"
#include <gtest/gtest.h>

TEST(point, constructor_2f)
{
  const chestnut::Point2f point{1.0f, 2.0f};
  EXPECT_FLOAT_EQ(point[0], 1);
  EXPECT_FLOAT_EQ(point[1], 2);
}

TEST(point, constructor_2d)
{
  const chestnut::Point2d point{1.0, 2.0};
  EXPECT_DOUBLE_EQ(point[0], 1);
  EXPECT_DOUBLE_EQ(point[1], 2);
}

TEST(point, constructor_3f)
{
  const chestnut::Point3f point{1.0f, 2.0f, 3.0f};
  EXPECT_FLOAT_EQ(point[0], 1.0f);
  EXPECT_FLOAT_EQ(point[1], 2.0f);
  EXPECT_FLOAT_EQ(point[2], 3.0f);
}

TEST(point, constructor_3d)
{
  const chestnut::Point3d point{1.0, 2.0, 3.0};
  EXPECT_DOUBLE_EQ(point[0], 1);
  EXPECT_DOUBLE_EQ(point[1], 2);
  EXPECT_DOUBLE_EQ(point[2], 3);
}

TEST(point, constructor_iterators)
{
  std::array<double, 3> arr{1, 2, 3};
  const chestnut::Point3d point{arr.begin(), arr.end()};
  EXPECT_DOUBLE_EQ(point[0], 1);
  EXPECT_DOUBLE_EQ(point[1], 2);
  EXPECT_DOUBLE_EQ(point[2], 3);

  std::array<double, 2> arr2{1, 2};
  EXPECT_DEATH((chestnut::Point3d{arr2.begin(), arr2.end()}), ".*");

  const std::array<double, 4> arr4{2, 2, 3, 4};
  EXPECT_DEATH((chestnut::Point3d{arr4.begin(), arr4.end()}), ".*");
}

TEST(point, constructor_std_array)
{
  chestnut::Point3d point{std::array<double, 3>{1, 2, 3}};
  EXPECT_DOUBLE_EQ(point[0], 1);
  EXPECT_DOUBLE_EQ(point[1], 2);
  EXPECT_DOUBLE_EQ(point[2], 3);

  const std::array<double, 2> arr{2, 2};
  EXPECT_DEATH((chestnut::Point3d{arr}), ".*");

  const std::array<double, 4> arr4{2, 2, 3, 4};
  EXPECT_DEATH((chestnut::Point3d{arr4}), ".*");
}

TEST(point, constructor_std_vector)
{
  const chestnut::Point3d point{std::vector<double>{1, 2, 3}};
  EXPECT_DOUBLE_EQ(point[0], 1);
  EXPECT_DOUBLE_EQ(point[1], 2);
  EXPECT_DOUBLE_EQ(point[2], 3);

  const std::vector<double> vec2{2, 2};
  EXPECT_DEATH((chestnut::Point3d{vec2}), ".*");

  const std::vector<double> vec4{2, 2, 3, 4};
  EXPECT_DEATH((chestnut::Point3d{vec4}), ".*");
}

TEST(point, constructor_point)
{
  auto point = chestnut::Point3d(chestnut::Point3d{1., 2., 3.});
  EXPECT_DOUBLE_EQ(point[0], 1);
  EXPECT_DOUBLE_EQ(point[1], 2);
  EXPECT_DOUBLE_EQ(point[2], 3);
}

TEST(point, equality_comparison)
{
  const chestnut::Point3d p1{1., 2., 3.};
  const chestnut::Point3d p2{1., 2., 3.};
  EXPECT_EQ(p1, p2);

  const chestnut::Point3d p3{1., 2., 4.};
  EXPECT_NE(p1, p3);
}

TEST(point, distance)
{
  const chestnut::Point3d p1{1., 1., 1.};
  const chestnut::Point3d p2{1., 1., 3.};
  EXPECT_DOUBLE_EQ(p1.distance(p2), 2);
}

TEST(point, distance_squared)
{
  chestnut::Point3d const p1{1., 1., 1.};
  chestnut::Point3d const p2{1., 1., 3.};
  EXPECT_DOUBLE_EQ(p1.distance_squared(p2), 4);
}
