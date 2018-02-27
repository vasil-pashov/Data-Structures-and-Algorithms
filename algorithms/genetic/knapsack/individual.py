import random


class Individual:
    def __init__(self, genes, fitness):
        self.genes = genes
        self.fitness = fitness
        self.size = len(genes)

    def __repr__(self):
        return "{}".format((self.genes, self.fitness))

    def __str__(self):
        return __repr__()

    def mutate(self):
        if random.uniform(0, 1) < 0.01:
            idx = random.randrange(self.size)
            self.genes[idx] = not(self.genes[idx])

    @classmethod
    def crossover(cls, parent1, parent2):
        child_genes = []
        for i in range(0, parent1.size):
            chosen_parent = random.randint(0, 1)
            if chosen_parent == 0:
                child_genes.append(parent1.genes[i])
            else:
                child_genes.append(parent2.genes[i])
        return cls(child_genes, 0)

    @classmethod
    def random(cls, size):
        genes = [bool(random.getrandbits(1)) for _ in range(0, size)]
        return cls(genes, 0)
