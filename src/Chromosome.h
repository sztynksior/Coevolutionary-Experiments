#pragma once

#include <list>
#include <memory>
#include "GeneInitializer.h"
#include "Crossover.h"
#include "Mutation.h"
#include "FitnessFunction.h"

template<typename T>
class Chromosome {
    std::list<T> genes;
    std::shared_ptr<Crossover<T>> crossover;
    std::shared_ptr<Mutation<T>> mutation;
    std::shared_ptr<FitnessFunction> fitnessFunction;
public:
    Chromosome(
        std::shared_ptr<GeneInitializer<T>> initializer,
        std::shared_ptr<Crossover<T>> crossover,
        std::shared_ptr<Mutation<T>> mutation,
        std::shared_ptr<FitnessFunction> fitnessFunction
    ) : genes(initializer->initialize()), crossover(crossover), mutation(mutation), fitnessFunction(fitnessFunction) {};

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