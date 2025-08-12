#include <list>
#include <iostream>

class Crossover {
public:
    virtual void performCrossover(std::list<int>& parent1, std::list<int>& parent2) = 0;
};

class Mutation {
protected:
    int mutationProbability;
public:
    Mutation(int prob) : mutationProbability(prob) {}
    virtual void performMutation(std::list<int>& genes) = 0;
};

class FitnessFunction {
public:
    virtual double evaluate(const std::list<int>& genes) const = 0;
};

class Chromosome {
    std::list<int> genes;
    Crossover* crossover;
    Mutation* mutation;
    FitnessFunction* fitnessFunction;
public: 
    Chromosome(
        std::list<int> g, Crossover* c, Mutation* m, FitnessFunction* f
    ) : genes(std::move(g)), crossover(c), mutation(m), fitnessFunction(f) {};

    void print() const {
        for (const auto& gene : genes) {
            std::cout << gene << " ";
        }
        std::cout << std::endl;
    }

    void performCrossover(Chromosome& other) {
        crossover->performCrossover(genes, other.genes);
    }

    void performMutation() {
        mutation->performMutation(genes);
    }

    void evaluateFitness() {
        fitnessFunction->evaluate(genes);
    }
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
        parent2.splice(
            parent2.end(), parent1, firstParentCorssPoint, std::prev(parent1.end(), spliceSize)
        );
    }
};

class SwapMutation : public Mutation {
    public:
        SwapMutation(int prob) : Mutation(prob) {}
        void performMutation(std::list<int>& genes) {
            if (std::rand() % 100 < mutationProbability) {
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
        }
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

int main() {
    srand(time(0));
    std::cout << std::rand() << std::endl;
    Crossover* crossover = new OnePointCrossover();
    Mutation* mutation = new SwapMutation(100);
    FitnessFunction* fitnessFunction = new RastriginFitness();
    Chromosome parent1({11, 22, 33, 44, 55}, crossover, mutation, fitnessFunction);
    Chromosome parent2({1, 2, 3, 4, 5}, crossover, mutation, fitnessFunction);

    std::cout << "Before crossover:" << std::endl;
    parent1.performCrossover(parent2);
    parent1.print();
    parent2.print();

    std::cout << "Before mutation:" << std::endl;
    parent1.performMutation();
    parent1.print();

    delete crossover;
    delete mutation;
    delete fitnessFunction;

    return 0;
}