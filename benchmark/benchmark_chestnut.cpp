#include <benchmark/benchmark.h>
#include <chestnut/chestnut.hpp>

static void BM_chestnut(benchmark::State& state)
{
  for (auto _: state)
  {
    chestnut::libraryFunction(42);
  }
}
BENCHMARK(BM_chestnut);

BENCHMARK_MAIN();