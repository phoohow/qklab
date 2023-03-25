#include "Lopencv.h"
#include <iostream>
#include <string>

#include <benchmark/benchmark.h>

using namespace std;

static void BM_minSquare(benchmark::State &state)
{
    // Perform setup here
    for (auto _ : state)
    {
        // Set image path and name
        std::string imagePathDir("D:/Pictures/texture/"); // by default
        std::string imageName("xx.png");                  // by default

        // This code gets timed
        minSquare(imagePathDir, imageName);
    }
}

// Register the function as a benchmark
BENCHMARK(BM_minSquare)->Unit(benchmark::kMillisecond)->Iterations(1)->Complexity();

// Run the benchmark
BENCHMARK_MAIN();