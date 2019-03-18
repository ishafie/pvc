#ifndef GLOUTON_H
#define GLOUTON_H

#include "pvc.h"
#include <climits>
#include "Algo.h"
#include "Graph.h"


class Glouton : public Algo{

public:
    virtual void resoleAlgo()
    {
            
    }

    static int solve_glouton(Graph::Matrice m, list<pair<int, int>> lc, pair<int, int> start_coord, vector<pair<int, int>> *ret);
    static vector<pair<int, int>> glouton_pvc(list<pair<int, int>> lc);
    static auto solve_2_opt(vector<pair<int, int>> *ret);
    static vector<pair<int, int>> glouton_pvc_2_opt(list<pair<int, int>> lc);

};

#endif