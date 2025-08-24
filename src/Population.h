#pragma once

#include <list>
#include <vector>
#include "Chromosome.h"
#include "SelectionStrategy.h"

template<typename T>
class Population {
    int size;
    std::vector<Chromosome<T>> individuals;
    std::shared_ptr<SelectionStrategy> selectionStrategy;
    std::vector<int> selections;
public:
    Population(
        int size,
        std::shared_ptr<GeneInitializer<T>> initializer,
        std::shared_ptr<Crossover<T>> crossover,
        std::shared_ptr<Mutation<T>> mutation,
        std::shared_ptr<FitnessFunction<T>> fitnessFunction,
        std::shared_ptr<SelectionStrategy> selectionStrategy
    ) : size(size), selectionStrategy(selectionStrategy) {
        if (size % 2 != 0) {
            throw std::invalid_argument("Population size have to by multiply of 2!");
        }
        selections.resize(size);
        for (int i = 0; i < size; ++i) {
            individuals.emplace_back(Chromosome<T>(
                initializer,
                crossover,
                mutation,
                fitnessFunction
            ));
        }
    }
    void print() const {
        for (int i = 0; i < individuals.size(); i++) {
            individuals[i].print();
            std::cout << " | ";
            if (i % 2 == 1) {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
    void print(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        auto it = std::next(individuals.begin(), index);
        it->print();
        std::cout << std::endl;
    }
    void printBest() {
        individuals[getBestIndividualIndex()].print();
    }
    void evolutionStep() {
        std::vector<double> populationFitness = getPopulationFitness();
        selectionStrategy->select(selections, populationFitness);
        for(int i = 0; i < size; i++) {
            individuals[i].setEvolvingGenes(individuals[selections[i]].getGenes());
        }
        individuals[getBestIndividualIndex()].preserveCurrentGenes();
        for(int i = 0; i < size; i += 2) {
            individuals[i].performCrossover(individuals[i + 1]);
            individuals[i].performMutation();
            individuals[i + 1].performMutation();
            individuals[i].evolve();
            individuals[i + 1].evolve();
        }
    }
    double averagePopulationFitness() const {
        double total = 0.0;
        for (const Chromosome<T>& individual : individuals) {
            total += individual.evaluateFitness();
        }
        return total / size;
    }
    double bestIndividualFitness() const {
        return individuals[getBestIndividualIndex()].evaluateFitness();
    }
private:
    std::vector<double> getPopulationFitness() {
        std::vector<double> fitnessValues(size);
        for(int i = 0; i < size; ++i) {
            fitnessValues[i] = individuals[i].evaluateFitness();
        }
        return fitnessValues;
    }
    int getBestIndividualIndex() const {
        double bestFitness = std::numeric_limits<double>::max();
        int bestIndex = -1;
        for (int i = 0; i < individuals.size(); i++) {
            if (individuals[i].evaluateFitness() < bestFitness) {
                bestFitness = individuals[i].evaluateFitness();
                bestIndex = i;
            }
        }
        return bestIndex;
    }
};