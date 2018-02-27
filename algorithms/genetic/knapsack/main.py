from generation import Generation
from knapsack import Knapsack
import random


def process_generation(generation, knapsack):
    generation.set_generation_fitness(
        lambda individual:
        sum(knapsack.costs[idx]
            for idx, val in enumerate(individual.genes) if val)
    )
    generation.correct_idividuals(
        lambda individual: correct(individual, knapsack))


def correct(individual, knapsack):
    ones = [i for i, val in enumerate(individual.genes) if val]
    individual_weight = sum(knapsack.weights[i] for i in ones)
    while individual_weight > knapsack.volume:
        idx = random.randrange(len(ones))
        individual.genes[ones[idx]] = False
        individual_weight -= knapsack.weights[ones[idx]]
        individual.fitness -= knapsack.costs[ones[idx]]
        del ones[idx]


def main():
    knapsack, items_number = read_input()
    generation = Generation(items_number * 10, items_number)
    process_generation(generation, knapsack)
    for i in range(1, 11):
        print("Before iteration {0} best individual is: {1}".format(
            i, generation.get_best().fitness))
        generation.update_generation()
        process_generation(generation, knapsack)
    print("Final result is: {}".format(generation.get_best().fitness))


def read_input():
    print("Enter items knapsack volume and items number")
    volume, items_number = map(int, input().split())
    costs = []
    weights = []
    print("Enter item weight and item cost")
    for i in range(0, items_number):
        item_weight, item_cost = map(int, input().split())
        costs.append(item_cost)
        weights.append(item_weight)
    return Knapsack(volume, costs, weights), items_number


main()
