from individual import Individual
import random
import operator


class Generation:
    def __init__(self, size, individual_size):
        self.size = size
        self.individual_size = individual_size
        self.keep = int((size * 50) / 100)
        self.individuals = self.__initial_individuals()

    def get_best(self):
        return self.individuals[-1]

    def update_generation(self):
        self.individuals.sort(key=operator.attrgetter('fitness'))
        parents = self.individuals[self.size - self.keep:]
        distribution = self.__selection_distribution(parents)
        for i in range(0, self.keep):
            parent1 = self.__select_parent(distribution, parents)
            parent2 = self.__select_parent(distribution, parents)
            child = Individual.crossover(parent1, parent2)
            child.mutate()
            self.individuals[i] = child

    def set_generation_fitness(self, fitness_fun):
        for individual in self.individuals:
            individual.fitness = fitness_fun(individual)

    def correct_idividuals(self, correction_fun):
        for individual in self.individuals:
            correction_fun(individual)

    def __selection_distribution(self, parents):
        total_fitness = sum(individual.fitness for individual in parents)
        return [individual.fitness / total_fitness for individual in parents]

    def __select_parent(self, distribution, parents):
        prob = random.uniform(0, 1)
        for index, parent in enumerate(parents):
            if distribution[index] >= prob:
                return parent
            else:
                prob -= distribution[index]

    def __initial_individuals(self):
        return [Individual.random(self.individual_size) for _ in range(0, self.size)]
