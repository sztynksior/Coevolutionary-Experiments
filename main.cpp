#include <list>
#include <iostream>

class Chromosome {
    std::list<int> genes;
public: 
    Chromosome(std::list<int> g) : genes(std::move(g)) {};
    void print() const {
        for (const auto& gene : genes) {
            std::cout << gene << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Chromosome chromo({1, 0, 1, 1, 0});
    chromo.print();
    return 0;
}