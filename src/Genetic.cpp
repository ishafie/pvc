#include "Genetic.hpp"
#include "pvc.hpp"
#include "Algo.hpp"
#include "Glouton.hpp"



int Genetic::distance_of_individual(const vector<pair<int, int>> individual) {
    int distance_sum = 0;
    int i = 0;
    for (i = 0; (i + 1) < individual.size(); i++) {
        distance_sum += Graph::distance(individual[i], individual[i + 1]);
    }
    distance_sum += Graph::distance(individual[i], individual[0]);
    return distance_sum;
}

auto Genetic::generate_population(vector<pair<int, int>> alpha_individual, int nb_individuals) {
    vector<pair<int, int>> individual;
    vector<pair<int, vector<pair<int, int>>>> population;
    population.push_back(make_pair(distance_of_individual(alpha_individual), alpha_individual));
    for (int i = 0; i < nb_individuals; i++) {
        individual = alpha_individual;
        random_shuffle(individual.begin(), individual.end());
        population.push_back(make_pair(distance_of_individual(individual), individual));
    }
    return population;
}

void Genetic::display_population(vector<pair<int, vector<pair<int, int>>>> population) {
    cout << "POPULATION:" << endl;
    for_each(population.begin(), population.end(), [](auto individual){
        cout << individual.first << ": ";
        for_each(individual.second.begin(), individual.second.end(), [](auto a){ cout << "(" << a.first << ", " << a.second << ") "; });
        cout << endl;
    });
}

auto Genetic::make_child(pair<int, vector<pair<int, int>>> a, pair<int, vector<pair<int, int>>> b) {
    int nb_genes = a.second.size();
    int doublon_remover = 0;
    int k = rand() % nb_genes;
    int k2 = rand() % nb_genes;
    vector<pair<int, int>> genes;
    for (int i = 0; i < k; i ++) {
        genes.push_back(a.second[i]);
    }
    for (int i = k; i < nb_genes; i++) {
        while (find(genes.begin(), genes.end(), b.second[(i + doublon_remover) % nb_genes]) != genes.end()) {
            // cout << "DOUBLON: " << doublon_remover << " => " << b.second[i].first << ", " << b.second[i].second << endl;
            doublon_remover++;
        }
        genes.push_back(b.second[(i + doublon_remover) % nb_genes]);
        doublon_remover = 0;
    }
    k = rand() % nb_genes;
    k = k == k2 ? (k + 1) % nb_genes : k;
    iter_swap(genes.begin() + k, genes.begin() + k2); // mutation
    return make_pair(distance_of_individual(genes), genes);
}

void Genetic::reproduction(vector<pair<int, vector<pair<int, int>>>> reproductors, int nb_individuals) {
    vector<pair<int, vector<pair<int, int>>>> children;
    for (int i = 0; i < nb_individuals; i++) {
        int other_parent = rand() % nb_individuals;
        other_parent = other_parent == i ? (other_parent + 1) % nb_individuals : other_parent;
        cout << "child between " << i << " and " << other_parent << endl;
        auto child = Genetic::make_child(reproductors[i], reproductors[other_parent]);
        children.push_back(child);
    }
    Genetic::display_population(children);
}

void Genetic::algo_genetique(list<pair<int, int>> lc, int nb_individuals, int max_reproductors) {
    cout << "start genetique" << endl;
    vector<pair<int, int>> alpha_individual = Glouton::glouton_pvc_2_opt(lc);
    vector<pair<int, vector<pair<int, int>>>> population = Genetic::generate_population(alpha_individual, nb_individuals);
    sort(population.begin(), population.end(), [](auto a, auto b){return a.first < b.first;});
    vector<pair<int, vector<pair<int, int>>>> reproductors;
    for (int i = 0; i < nb_individuals; i++) {
        reproductors.push_back(make_pair(population[i % max_reproductors].first, population[i % max_reproductors].second));
    }
    Genetic::reproduction(reproductors, nb_individuals);
    // display_population(reproductors, nb_individuals);

}

