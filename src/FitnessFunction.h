#pragma once

#include <list>
#include <cmath>

class FitnessFunction {
public:
    virtual double evaluate(const std::list<int>& genes) const = 0;
};

class RastriginFitness : public FitnessFunction { 
public:
    double evaluate(const std::list<int>& genes) const override {
        constexpr double pi = 3.14159265358979323846;
        double sum = 0.0;
        for (const auto& gene : genes) {
            sum += gene * gene - 3.0 * std::cos(2.0 * pi * gene);
        }
        return 3 * genes.size() + sum;
    }
};