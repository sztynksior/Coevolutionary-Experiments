#pragma once

#include <vector>
#include <list>
#include <numeric>
#include <stack>
#include <stdexcept>
#include <random>
#include "Population.h"

class SelectionStrategy {
public:
    virtual  void select(std::vector<int>& selections, const std::vector<double>& populationFitnes) = 0;
};

class RouletteWheelSelection : public SelectionStrategy {
    std::vector<double> probabilityDistribution;
    std::vector<double> probabilityTable;
    std::vector<int> aliasTable;
public:
    RouletteWheelSelection(int populationSize) {
        probabilityDistribution.resize(populationSize);
        aliasTable.resize(populationSize);
        probabilityTable.resize(populationSize);
    }
    void select(std::vector<int>& selections, const std::vector<double>& populationFitnes) override {
        int newPopulationSize = populationFitnes.size();
        if (newPopulationSize != probabilityDistribution.size() || newPopulationSize != aliasTable.size()) {
            throw std::invalid_argument("ProbabilityDistribution and alias table size must match the population size!");
        }
        double totalScore = std::accumulate(populationFitnes.begin(), populationFitnes.end(), 0.0);
        for(int i = 0; i < newPopulationSize; i++) {
            double probability = 1 - populationFitnes[i] / totalScore;
            probabilityDistribution[i] = probability;
        }
        initializeAliasMethodDataStructures();
        for(int i = 0; i < newPopulationSize; i++) {
            selections[i] = sample();
        }
    }
private:
    void initializeAliasMethodDataStructures() {
        std::stack<int> small, large;
        for (int i = 0; i < probabilityDistribution.size(); i++) {
            probabilityDistribution[i] = probabilityDistribution[i] * probabilityDistribution.size();
            if (probabilityDistribution[i] < 1.0) {
                small.push(i);
            } else {
                large.push(i);
            }
        }
        int smallIndex;
        int largeIndex;
        while(!small.empty() && !large.empty()) {
            smallIndex = small.top();
            largeIndex = large.top();
            small.pop();
            large.pop();
            probabilityTable[smallIndex] = probabilityDistribution[smallIndex];
            aliasTable[smallIndex] = largeIndex;
            probabilityDistribution[largeIndex] += probabilityDistribution[smallIndex] - 1;
            if(probabilityDistribution[largeIndex] < 1) {
                small.push(largeIndex);
            } else {
                large.push(largeIndex);
            }
        }
        while (!small.empty())
        {   
            smallIndex = small.top();
            small.pop();
            probabilityTable[smallIndex] = 1.0;
        }
        while (!large.empty())
        {   
            largeIndex = large.top();
            large.pop();
            probabilityTable[largeIndex] = 1.0;
        }
    }
    int sample() {
        int fairDieRoll = std::rand() % probabilityTable.size();
        double biasedCoinRoll = std::rand() / double(RAND_MAX);
        if(biasedCoinRoll < probabilityTable[fairDieRoll]) {
            return fairDieRoll;
        } else {
            return aliasTable[fairDieRoll];
        }
    }
};