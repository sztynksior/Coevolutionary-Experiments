#pragma once

#include <list>

template<typename T>
class Crossover {
    double crossoverProbability;
protected:
    bool shouldCrossover() const {
        return std::rand() / double(RAND_MAX) < crossoverProbability;
    }
public:
    Crossover(double prob) : crossoverProbability(prob) {}
    virtual void performCrossover(std::list<T>& parent1, std::list<T>& parent2) = 0;
};

template<typename T>
class OnePointCrossover : public Crossover<T> {
    public:
    OnePointCrossover(double prob) : Crossover<T>(prob) {}
    void performCrossover(std::list<T>& parent1, std::list<T>& parent2) override {
        if (!this->shouldCrossover()) {
            return;
        }

        int crossoverPoint = std::rand() % parent1.size();
        crossoverPoint = std::max(1, crossoverPoint);
        auto firstParentCorssPoint = std::next(parent1.begin(), crossoverPoint);
        auto secondParentCrossPoint = std::next(parent2.begin(), crossoverPoint);
        int spliceSize = parent1.size() - crossoverPoint;

        parent1.splice(parent1.end(), parent2, secondParentCrossPoint, parent2.end());
        parent2.splice(
            parent2.end(), parent1, firstParentCorssPoint, std::prev(parent1.end(), spliceSize)
        );
    }
};
