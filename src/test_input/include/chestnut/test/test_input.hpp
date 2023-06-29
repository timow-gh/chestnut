#ifndef CHESTNUT_EXAMPLE_INPUT_H
#define CHESTNUT_EXAMPLE_INPUT_H

#include <chestnut/kdtree.hpp>
#include <vector>

namespace chestnut
{

namespace test
{

std::vector<Point3d> testPoints{
    Point3d{4, 2, 6}, Point3d{8, 9, 7}, Point3d{1, 4, 3}, Point3d{6, 2, 9}, Point3d{8, 5, 7}, Point3d{3, 6, 5}, Point3d{5, 1, 8},
    Point3d{1, 2, 3}, Point3d{6, 9, 4}, Point3d{5, 7, 2}, Point3d{2, 4, 8}, Point3d{3, 5, 7}, Point3d{9, 6, 1}, Point3d{7, 3, 2},
    Point3d{4, 8, 5}, Point3d{2, 1, 6}, Point3d{9, 7, 4}, Point3d{8, 3, 1}, Point3d{6, 5, 2}, Point3d{4, 9, 7}, Point3d{7, 2, 8},
    Point3d{5, 6, 1}, Point3d{1, 3, 9}, Point3d{2, 7, 5}, Point3d{3, 8, 4}, Point3d{6, 1, 3}, Point3d{5, 4, 9}, Point3d{9, 2, 6},
    Point3d{7, 8, 1}, Point3d{4, 5, 3}, Point3d{2, 6, 7}, Point3d{3, 9, 8}, Point3d{1, 7, 4}, Point3d{8, 4, 2}, Point3d{6, 3, 5},
    Point3d{5, 9, 1}, Point3d{9, 8, 3}, Point3d{7, 6, 4}, Point3d{4, 7, 8}, Point3d{2, 5, 9}, Point3d{3, 1, 6}, Point3d{1, 8, 7},
    Point3d{8, 6, 5}, Point3d{6, 7, 2}, Point3d{5, 3, 1}, Point3d{9, 1, 4}, Point3d{7, 4, 9}, Point3d{4, 6, 3}, Point3d{2, 3, 5}};

} // namespace test

} // namespace chestnut

#endif // CHESTNUT_EXAMPLE_INPUT_H
