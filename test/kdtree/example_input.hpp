#ifndef CHESTNUT_EXAMPLE_INPUT_H
#define CHESTNUT_EXAMPLE_INPUT_H

#include <chestnut/kdtree.hpp>
#include <vector>

namespace chestnut
{
namespace test
{

std::vector<Point<3>> testPoints{
    Point<3>{4, 2, 6}, Point<3>{8, 9, 7}, Point<3>{1, 4, 3}, Point<3>{6, 2, 9}, Point<3>{8, 5, 7}, Point<3>{3, 6, 5}, Point<3>{5, 1, 8},
    Point<3>{1, 2, 3}, Point<3>{6, 9, 4}, Point<3>{5, 7, 2}, Point<3>{2, 4, 8}, Point<3>{3, 5, 7}, Point<3>{9, 6, 1}, Point<3>{7, 3, 2},
    Point<3>{4, 8, 5}, Point<3>{2, 1, 6}, Point<3>{9, 7, 4}, Point<3>{8, 3, 1}, Point<3>{6, 5, 2}, Point<3>{4, 9, 7}, Point<3>{7, 2, 8},
    Point<3>{5, 6, 1}, Point<3>{1, 3, 9}, Point<3>{2, 7, 5}, Point<3>{3, 8, 4}, Point<3>{6, 1, 3}, Point<3>{5, 4, 9}, Point<3>{9, 2, 6},
    Point<3>{7, 8, 1}, Point<3>{4, 5, 3}, Point<3>{2, 6, 7}, Point<3>{3, 9, 8}, Point<3>{1, 7, 4}, Point<3>{8, 4, 2}, Point<3>{6, 3, 5},
    Point<3>{5, 9, 1}, Point<3>{9, 8, 3}, Point<3>{7, 6, 4}, Point<3>{4, 7, 8}, Point<3>{2, 5, 9}, Point<3>{3, 1, 6}, Point<3>{1, 8, 7},
    Point<3>{8, 6, 5}, Point<3>{6, 7, 2}, Point<3>{5, 3, 1}, Point<3>{9, 1, 4}, Point<3>{7, 4, 9}, Point<3>{4, 6, 3}, Point<3>{2, 3, 5}};

}
} // namespace chestnut

#endif // CHESTNUT_EXAMPLE_INPUT_H
