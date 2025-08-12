#pragma once

#include <list>
#include <cmath>

template<typename T>
class GeneInitializer {
protected:
    int size;
public: 
    GeneInitializer(int size) : size(size) {}
    virtual std::list<T> initialize() = 0;
};

template<typename T>
class RangeInitializer : public GeneInitializer<T> {
    T min;
    T max;
public:
    RangeInitializer(int size, T min, T max) : GeneInitializer<T>(size), min(min), max(max) {}

    std::list<T> initialize() override {
        std::list<T> genes;
        T newGene;
        for (int i = 0; i < this->size; ++i) {
            newGene = static_cast<T>(std::fmod(std::rand(), (max - min + 1)) + min);
            genes.emplace_back(newGene);
        }
        return genes;
    }
};