#include "chestnut/kdtree.hpp"
#include <benchmark/benchmark.h>

static void BM_kdtree_default_constructor(benchmark::State& state)
{
  for (auto _: state)
  {
    chestnut::KdTree<3> kdree;
  }
}
BENCHMARK(BM_kdtree_default_constructor);

BENCHMARK_MAIN();