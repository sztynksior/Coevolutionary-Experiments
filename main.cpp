#include <list>
#include <iostream>
#include "src/Chromosome.h"
#include "src/ChromosomeInitializer.h"
#include "src/Crossover.h"
#include "src/Mutation.h"
#include "src/FitnessFunction.h"

#include <cmath>

int main() {
    srand(time(0));

    int length = 5;

    ChromosomeInitializer<float>* initializer = new RangeInitializer<float>(length, -5.12, 5.12);
    Crossover<float>* crossover = new OnePointCrossover<float>(100);
    Mutation<float>* mutation = new RangeMutation<float>(100, -5.12, 5.12);
    FitnessFunction* fitnessFunction = new RastriginFitness();
    Chromosome<float> parent1(initializer, crossover, mutation, fitnessFunction);
    Chromosome<float> parent2(initializer, crossover, mutation, fitnessFunction);

    parent1.print();
    parent2.print();
    std::cout << "After crossover:" << std::endl;
    parent1.performCrossover(parent2);
    parent1.print();
    parent2.print();

    std::cout << "After mutation:" << std::endl;
    parent1.performMutation();
    parent1.print();

    delete crossover;
    delete mutation;
    delete fitnessFunction;
    delete initializer;

    return 0;
}