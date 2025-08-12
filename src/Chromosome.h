#pragma once

#include <list>
#include "ChromosomeInitializer.h"
#include "Crossover.h"
#include "Mutation.h"
#include "FitnessFunction.h"

template<typename T>
class Chromosome {
    std::list<T> genes;
    Crossover<T>* crossover;
    Mutation<T>* mutation;
    FitnessFunction* fitnessFunction;
public: 
    Chromosome(
        ChromosomeInitializer<T>* initializer , Crossover<T>* c, Mutation<T>* m, FitnessFunction* f
    ) : genes(initializer->initialize()), crossover(c), mutation(m), fitnessFunction(f) {};

    void print() const {
        for (const auto& gene : genes) {
            std::cout << gene << " ";
        }
        std::cout << std::endl;
    }

    void performCrossover(Chromosome& other) {
        crossover->performCrossover(genes, other.genes);
    }

    void performMutation() {
        mutation->performMutation(genes);
    }

    double evaluateFitness() {
        return fitnessFunction->evaluate(genes);
    }
};