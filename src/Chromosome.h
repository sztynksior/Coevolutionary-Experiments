#pragma once

#include <list>
#include <memory>
#include "GeneInitializer.h"
#include "Crossover.h"
#include "Mutation.h"
#include "FitnessFunction.h"

template<typename T>
class Chromosome {
    bool preserveGenes;
    std::list<T> genes;
    std::list<T> evolvingGenes;
    std::shared_ptr<Crossover<T>> crossover;
    std::shared_ptr<Mutation<T>> mutation;
    std::shared_ptr<FitnessFunction<T>> fitnessFunction;
public:
    Chromosome(
        std::shared_ptr<GeneInitializer<T>> initializer,
        std::shared_ptr<Crossover<T>> crossover,
        std::shared_ptr<Mutation<T>> mutation,
        std::shared_ptr<FitnessFunction<T>> fitnessFunction
    ) : 
    genes(initializer->generateGenes()), 
    evolvingGenes(initializer->generateDefaultGenes()), 
    crossover(crossover), 
    mutation(mutation), 
    fitnessFunction(fitnessFunction) 
    {
        preserveGenes = false;
    }

    void print() const {
        for (const auto& gene : genes) {
            std::cout << "[" << gene << "]";
        }
    }

    void performCrossover(Chromosome& other) {
        crossover->performCrossover(evolvingGenes, other.evolvingGenes);
    }

    void performMutation() {
        mutation->performMutation(evolvingGenes);
    }

    double evaluateFitness() const {
        return fitnessFunction->evaluate(genes);
    }

    void evolve() {
        if (!preserveGenes) {
            std::swap(genes, evolvingGenes);
        } else {
            preserveGenes = false;
        }
    }

    void setEvolvingGenes(const std::list<T>& genes) {
        evolvingGenes = genes;
    }
    void preserveCurrentGenes() {
        preserveGenes = true;
    }

    const std::list<T>& getGenes() const {
        return genes;
    }
};