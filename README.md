### Evolutionary Computing (EC)

The general idea behind Evolutionary Computing (EC) algorithms is to iteratively generate new populations of candidate solutions through selection, recombination, and mutation.
Selection pressure, which implements the principle of survival of the fittest, leads to an overall increase in population fitness over successive generations.
Recombination and mutation operators enable the algorithm to explore the search space and discover new, potentially better solutions.

The main branches of EC include Genetic Algorithms, Evolution Strategies, Genetic Programming, and Evolutionary Programming. 
These approaches share the same fundamental concepts and differ primarily in their representations, operators, and implementation details.

### Coevolutionary Algorithms (CEAs)

Coevolutionary Algorithms extend traditional EC methods by introducing an additional layer of evolutionary interaction.
Instead of evolving a single population, CEAs evolve multiple subpopulations simultaneously, each responsible for optimizing a specific part or aspect of the overall problem, typically under partial isolation.
Through coevolution, these subpopulations influence one another’s fitness and adaptation processes, enabling more complex and dynamic evolutionary dynamics.

Different types of CEAs can be characterized by:
- the mechanism of inter-population communication,
- the order in which subpopulations evolve, and
- the method used to compute the fitness of individuals based on interactions across subpopulations.

The choice of the underlying EC algorithm determines how each subpopulation evolves internally.

### Project Objectives

The final scope of my master’s thesis has not yet been fully defined; therefore, a flexible and extensible experimental environment is required.
Both EC and CEA frameworks are composed of multiple interchangeable components that collectively determine algorithmic performance.
The objective of this project is to leverage this modularity—together with object-oriented design principles and software design patterns—to implement a common, standardized framework for EC and CEA experimentation.
Specific algorithmic mechanisms can then be added or replaced as needed to support different experimental setups.
