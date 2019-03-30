#ifndef GENETIC_H
#define GENETIC_H


#include "pvc.hpp"
#include "Algo.hpp"
#include "Glouton.hpp"

class Genetic : public Algo
{
public:
    Genetic(){};

    virtual void operator() (list<pair<int, int>> lc){
        return algo_genetique(lc, 10, 3);
    }
    

    static int distance_of_individual(const vector<pair<int, int>> individual);

    static auto generate_population(vector<pair<int, int>> alpha_individual, int nb_individuals);


    static void display_population(vector<pair<int, vector<pair<int, int>>>> population) ;


    static auto make_child(pair<int, vector<pair<int, int>>> a, pair<int, vector<pair<int, int>>> b) ;


    static void reproduction(vector<pair<int, vector<pair<int, int>>>> reproductors, int nb_individuals) ;


    static void algo_genetique(list<pair<int, int>> lc, int nb_individuals, int max_reproductors) ;



};

#endif