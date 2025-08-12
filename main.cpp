#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <list>
#include <iostream>
#include <cmath>
#include <string.h>
#include <memory>
#include "src/Population.h"
#include <crtdbg.h>

int main() {
    srand(time(0));

    {
        int size = 10;
        Population<float> population(
            size,
            std::make_shared<RangeInitializer<float>>(5, -5.12, 5.12),
            std::make_shared<OnePointCrossover<float>>(100),
            std::make_shared<RangeMutation<float>>(100, -5.12, 5.12),
            std::make_shared<RastriginFitness>()
        );

        population.print();
    }

    _CrtDumpMemoryLeaks();
    return 0;
}
