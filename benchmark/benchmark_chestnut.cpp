#include <benchmark/benchmark.h>
#include <chestnut/kdtree.hpp>
#include <chestnut/test/test_input.hpp>

static void BM_kdtree_insert(benchmark::State& state)
{
  for (auto _: state)
  {
    chestnut::KdTree<3> kdree;
    for (auto const& point: chestnut::test::testPoints)
    {
      kdree.insert(point);
    }
  }
}
BENCHMARK(BM_kdtree_insert);

BENCHMARK_MAIN();