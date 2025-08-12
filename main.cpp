#include <list>
#include <iostream>

class Crossover {
public:
    virtual void performCrossover(std::list<int>& parent1, std::list<int>& parent2) = 0;
};

class OnePointCrossover : public Crossover {
    public:
    OnePointCrossover() = default;
    void performCrossover(std::list<int>& parent1, std::list<int>& parent2) override {
        int crossoverPoint = std::rand() % parent1.size();
        crossoverPoint = std::max(1, crossoverPoint);
        auto firstParentCorssPoint = std::next(parent1.begin(), crossoverPoint);
        auto secondParentCrossPoint = std::next(parent2.begin(), crossoverPoint);
        auto spliceSize = parent1.size() - crossoverPoint;

        parent1.splice(parent1.end(), parent2, secondParentCrossPoint, parent2.end());
        parent2.splice(parent2.end(), parent1, firstParentCorssPoint, std::prev(parent1.end(), spliceSize));
    }
};

class Chromosome {
    std::list<int> genes;
    Crossover* crossover;

    public: 

    Chromosome(
        std::list<int> g, Crossover* c
    ) : genes(std::move(g)), crossover(c) {};

    void print() const {
        for (const auto& gene : genes) {
            std::cout << gene << " ";
        }
        std::cout << std::endl;
    }

    void performCrossover(Chromosome& other) {
        crossover->performCrossover(genes, other.genes);
    }
};

int main() {
    srand(time(0));

    Crossover* crossover = new OnePointCrossover();
    Chromosome parent1({11, 22, 33, 44, 55}, crossover);
    Chromosome parent2({1, 2, 3, 4, 5}, crossover);

    parent1.performCrossover(parent2);
    parent1.print();
    parent2.print();

    return 0;
}