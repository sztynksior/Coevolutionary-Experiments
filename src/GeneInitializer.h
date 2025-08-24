#pragma once

#include <list>
#include <cmath>

template<typename T>
class GeneInitializer {
protected:
    int size;
public: 
    GeneInitializer(int size) : size(size) {}
    virtual std::list<T> generateGenes() = 0;
    std::list<T> generateDefaultGenes() {
        std::list<T> genes;
        for (int i = 0; i < size; i++) {
            genes.push_back(static_cast<T>(i));
        }
        return genes;
    }
};

template<typename T>
class RangeInitializer : public GeneInitializer<T> {
    T min;
    T max;
public:
    RangeInitializer(int size, T min, T max) : GeneInitializer<T>(size), min(min), max(max) {}

    std::list<T> generateGenes() override {
        std::list<T> genes;
        T newGene;
        for (int i = 0; i < this->size; ++i) {
            newGene = static_cast<T>(std::fmod(std::rand(), (max - min + 1)) + min);
            genes.push_back(newGene);
        }
        return genes;
    }
};