#pragma once

#include <list>

template<typename T>
class Mutation {
private:
    double mutationProbability;
protected:
    bool shouldMutate() const {
        double randomValue = std::rand() / double(RAND_MAX);
        bool condition = randomValue < mutationProbability;
        return condition;
    }
public:
    Mutation(double prob) : mutationProbability(prob) {}
    virtual void performMutation(std::list<T>& genes) = 0;
};

template<typename T>
class SwapMutation : public Mutation<T> {
    public:
        SwapMutation(double prob) : Mutation<T>(prob) {}
        void performMutation(std::list<T>& genes) override {
            if (!this->shouldMutate()) {
                return;
            }

            int firstSwapPosition;
            int secondSwapPosition;
            do {
                firstSwapPosition = std::rand() % genes.size();
                secondSwapPosition = std::rand() % genes.size();
            } while (firstSwapPosition == secondSwapPosition);

            auto firstSwapPositionIt = std::next(genes.begin(), firstSwapPosition);
            auto secondSwapPositionIt = std::next(genes.begin(), secondSwapPosition);
            std::swap(*firstSwapPositionIt, *secondSwapPositionIt);
        }
};

template<typename T>
class RangeMutation : public Mutation<T> {
private:
    T min;
    T max;
public:
    RangeMutation(double prob, T min, T max) : Mutation<T>(prob), min(min), max(max) {}
    void performMutation(std::list<T>& genes) override {
        if (!this->shouldMutate()) {
            return;
        }

        auto geneToMutate = std::next(genes.begin(), std::rand() % genes.size());
        *geneToMutate = static_cast<T>(std::fmod(std::rand(), max - min) + min);
    }
};