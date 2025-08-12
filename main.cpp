#include <list>
#include <iostream>

class Chromosome {
public: 
    std::list<int> genes;

    Chromosome(std::list<int> g) : genes(std::move(g)) {};

    void print() const {
        for (const auto& gene : genes) {
            std::cout << gene << " ";
        }
        std::cout << std::endl;
    }
};

class Crossover {
public:
    Crossover() = default;
    void performCrossover(std::list<int>& parent1, std::list<int>& parent2) {
        int crossoverPoint = std::rand() % parent1.size();
        crossoverPoint = std::max(1, crossoverPoint);
        auto firstParentCorssPoint = std::next(parent1.begin(), crossoverPoint);
        auto secondParentCrossPoint = std::next(parent2.begin(), crossoverPoint);
        auto spliceSize = parent1.size() - crossoverPoint;

        parent1.splice(parent1.end(), parent2, secondParentCrossPoint, parent2.end());
        parent2.splice(parent2.end(), parent1, firstParentCorssPoint, std::prev(parent1.end(), spliceSize));
    }
};

int main() {
    srand(time(0));

    Crossover crossover;
    Chromosome parent1({11, 22, 33, 44, 55});
    Chromosome parent2({1, 2, 3, 4, 5});

    crossover.performCrossover(parent1.genes, parent2.genes);
    parent1.print();
    parent2.print();

    return 0;
}