#ifndef GENETIC_H
#define GENETIC_H


#include "pvc.h"
#include "Algo.h"
#include "Glouton.h"

class Genetic : public Algo
{
public:
    virtual void resoleAlgo()
    {
            
    }

int distance_of_individual(const vector<pair<int, int>> individual);

auto generate_population(vector<pair<int, int>> alpha_individual, int nb_individuals);


void display_population(vector<pair<int, vector<pair<int, int>>>> population) ;


auto make_child(auto a, auto b) ;


void reproduction(auto reproductors, int nb_individuals) ;


static void algo_genetique(list<pair<int, int>> lc, int nb_individuals, int max_reproductors) ;



};

#endif