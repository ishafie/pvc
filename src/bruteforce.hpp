
#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "pvc.hpp"
#include "Algo.hpp"
#include "Graph.hpp"

class BruteForce : public Algo
{
public:

    virtual void operator() (list<pair<int, int>> lc){
        return bruteforce_pvc_coords(lc);
    }
    
    static list<list<int>> generate_one_permutations(int n, int depart) ;

    static list<int> distances_boucles(list<list<int>> lb, vector<vector<int>> tab) ;

    list<list<int>> genere_boucle(int n, int depart) ;

    static pair<int, list<int>> meilleure_boucle(list<list<int>> lb, vector<vector<int>> tab) ;

    static void bruteforce_pvc(Graph g2) ;

    static void bruteforce_pvc_coords(list<pair<int, int>> lc); 
    


};

#endif