#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <list>
#include <iostream>
#include <cmath>
#include <string.h>
#include <memory>
#include <fstream>
#include "src/Population.h"
#include <crtdbg.h>

int main() {
    srand(time(0));
    
    {
        std::ofstream logFile("evolution_log.txt");
        if (!logFile) {
            std::cerr << "Error opening log file." << std::endl;
            return 1;
        }

        int size = 100;
        int chromosomeLength = 20;
        double mutationProbability = 1.0 / chromosomeLength;
        double crossoverProbability = 0.7;
        int generations = 100000;
        Population<float> population(
            size,
            std::make_shared<RangeInitializer<float>>(chromosomeLength, -5.12, 5.12),
            std::make_shared<OnePointCrossover<float>>(crossoverProbability),
            std::make_shared<RangeMutation<float>>(mutationProbability, -5.12, 5.12),
            std::make_shared<RastriginFitness<float>>(),
            std::make_shared<RouletteWheelSelection>(size)
        );
        std::cout << population.averagePopulationFitness() << std::endl;
        for (int i = 0; i < generations; ++i) {
            population.evolutionStep();
            logFile << population.bestIndividualFitness() << std::endl;
            if (i % 10 == 0) {
                population.printBest();
                std::cout << " Avg: " << population.averagePopulationFitness();
                std::cout << " Best: " << population.bestIndividualFitness() << std::endl;
            }
        }
        logFile.close();
    }

    _CrtDumpMemoryLeaks();
    return 0;
}
