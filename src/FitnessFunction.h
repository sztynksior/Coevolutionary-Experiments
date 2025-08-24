#pragma once

#include <list>
#include <cmath>

template<typename T>
class FitnessFunction {
public:
    virtual double evaluate(const std::list<T>& genes) const = 0;
};

template<typename T>
class RastriginFitness : public FitnessFunction<T> { 
public:
    double evaluate(const std::list<T>& genes) const override {
        constexpr double pi = 3.14159265358979323846;
        double sum = 0.0;
        for (const auto& gene : genes) {
            sum += gene * gene - 3.0 * std::cos(2.0 * pi * gene);
        }
        double fitness = 3 * genes.size() + sum;
        return fitness;
    }
};

template<typename T>
class myfitness : public FitnessFunction<T> { 
public:
    double evaluate(const std::list<T>& genes) const override {
        constexpr double pi = 3.14159265358979323846;
        double sum = 0.0;
        for (const auto& gene : genes) {
            sum += gene * gene - 2.0 * std::sin(2.0 * pi * gene);
        }
        double fitness = 3 * genes.size() + sum;
        return fitness;
    }
};