#pragma once

#include <list>
#include "Chromosome.h"

template<typename T>
class Population {
    int size;
    std::list<Chromosome<T>> chromosomes;
public:
    Population(
        int size,
        std::shared_ptr<GeneInitializer<T>> initializer,
        std::shared_ptr<Crossover<T>> crossover,
        std::shared_ptr<Mutation<T>> mutation,
        std::shared_ptr<FitnessFunction> fitnessFunction
    ) : size(size) {
        for (int i = 0; i < size; ++i) {
            chromosomes.emplace_back(Chromosome<T>(
                initializer,
                crossover,
                mutation,
                fitnessFunction
            ));
        }
    }
    void print() const {
        for (const auto& chromosome : chromosomes) {
            chromosome.print();
        }
    }
};