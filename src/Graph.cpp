#include "pvc.h"
#include <climits>

#include "Algo.h"
#include "Graph.h"
#include "Glouton.h"

using namespace std;
//faire classe abstraite resoudre

static list<list<int>> generate_permutations(int n) {
    list<list<int>> ret;
    vector<int> tab(n);
    for (int i = 0; i < n; i++) {
        tab[i] = i;
    }
    Graph::permute(&ret, tab, 0, n - 1);
    return ret;
}


map<pair<int, int>, int> Graph::Matrice::get_coord_to_index() {
    return this->from_coord_to_index;
}

map<int, pair<int, int>> Graph::Matrice::get_index_to_coord() {
    return this->from_index_to_coord;
}

vector<vector<int>> Graph::Matrice::get_matrice() {
    return this->tab;
}

int Graph::Matrice::get_sommets() {
    return this->sommets;
}

void Graph::Matrice::print() {
    for (int i = 0; i < this->sommets; i++) {
        for (int i2 = 0; i2 < this->sommets; i2++) {
            cout << tab[i][i2];
        }
        cout << endl;
    }
}

void Graph::Matrice::remove_index(int a) {
    for (int i = 0; i < this->sommets; i++) {
        this->tab[a][i] = -1;
        this->tab[i][a] = -1;
    }
}


vector<vector<int>> Graph::createTab(int sommets) {
    vector<vector<int>> tabtmp(sommets, vector<int>(sommets, 0));
    return tabtmp;
}



int Graph::getIntUpToDelimiter(string line, char delimiter) {
    static int i = 0;
    if (line.empty() || i > line.size()) {
        i = 0;
        return -1;
    }
    int save = i;
    for (i; i <= line.size();i++) {
        if (line[i] == delimiter || line[i] == '\0') {
            string nb = line.substr(save, i - save);
            i++;
            if (!(nb.find_first_not_of( "0123456789" ) == string::npos))
                return -1;
            return stoi(nb);
        }
    }
    return (-1);
}

Graph::~Graph() {

}

vector<vector<int>> Graph::get_tab() {
    return this->tab;
}

int Graph::get_sommets() {
    return this->sommets;
}
auto Graph::generateRandomWeight(int max) {
    std::list<int> ret;
    for (int i = 0; i < this->sommets;i++) {
        ret.push_back(rand() % max);
    }
    // for_each(ret.begin(), ret.end(), [](int n){cout << n << endl;});
    return (ret);
}

void Graph::generateRandomGraph(std::ostream &o, int max) {
    list<int> weights = generateRandomWeight(max);
    o << max << endl;
    for (int weight : weights) {
        o << rand() % max << " " << rand() % max << " " << weight << endl;
    }
}

void Graph::print() {

    for (int i = 0; i < this->sommets; i++) {
        for (int i2 = 0; i2 < this->sommets; i2++) {
            cout << tab[i][i2];
        }
        cout << endl;
    }
    
}


list<int> trouver_permutation(int *order, int n, int index) {
    list<int> ret;
    for (int i = 0; i < n; i++) {
        ret.push_back(order[(i + index) % n]);
    }
    return ret;
}

/*
int main(void){
    srand (time(NULL));
    */
    /*std::ofstream file ("../resources/test.txt");
    Graph g(5);
    cout << "starting pvc" << endl;
    g.generateRandomGraph(file, 10);
    file.close();
    g.print();*/
    /*std::ifstream input("../resources/complet.txt");
    Graph g2(input);
    cout << "created" << endl;
    g2.print();
    input.close();*/
    /*
    test_algo_genetique();
    // test_bruteforce_pvc_coords();
	// test_glouton_pvc_2_opt();
    // test_glouton_pvc();
    // bruteforce_pvc(g2);
    // test_permutations();
    // test_meilleure_boucle(g2);
    return (0);
}
*/




   /* 
    [ 0 1 2 3 ]
    [ 1 2 3 0 ]
    [ 2 3 0 1 ]
    [ 3 0 1 2 ]

    [ 1 0 2 3 ]
    [ 0 2 3 1 ]
    [ 2 3 1 0 ]
    [ 3 1 0 2 ]

    [ 0 2 1 3 ]
    [ 2 1 3 0 ]
    [ 1 3 0 2 ]
    [ 3 0 2 1 ]

    [ 2 3 0 1 ]
    [ 3 0 1 2 ]
    [ 0 1 2 3 ]
    [ 1 2 3 0 ]


    [ 2 1 3 0 ]
    [ 1 3 0 2 ]
    [ 3 0 2 1 ]
    [ 0 2 1 3 ]

    [ 1 2 3 0 ]
    [ 2 3 0 1 ]
    [ 3 0 1 2 ]
    [ 0 1 2 3 ]
-----
    0 1 2 3 > swap 1 - 2
    0 2 1 3 > swap 1 - 3, retour au debut
    0 2 3 1 > swap 2 - 3
    0 3 2 1 > swap 2 - 1, retour au debut
    0 3 1 2 > swap 3 - 1
    0 1 3 2 > swap 3 - 2, retour au debut, facto6 donc stop

    1 0 2 3 > swap 0 - 2
    1 2 0 3 > swap 0 - 3, retour au debut
    1 2 3 0 > swap 2 - 3
    1 3 2 0 > swap 2 - 0, retour au debut
    1 3 0 2 > swap 3 - 0
    1 0 3 2 > swap 3 - 2, retour au debut, facto6 donc stop

    0 1 2 > swap 1 - 2
    0 2 1 > retour au debut
    1 0 2 > swap 0 - 2
    1 2 0 > retour au debut
    2 1 0 > swap 1 - 0
    2 0 1 > retour au debut


    0 1 2 3 4 > swap 1 - 2
    0 2 1 3 4 > swap 1 - 3
    0 2 3 1 4 > swap 1 - 4, retour au debut
    0 2 3 4 1 > swap 2 - 3

    0 3 2 4 1 > swap 2 - 4
    0 3 4 2 1 > swap 2 - 1, retour au debut
    0 3 4 1 2 > swap 3 - 4

    0 4 3 1 2 > swap 3 - 1
    0 4 1 3 2 > swap 3 - 2, retour au debut
    0 4 1 2 3 > swap 4 - 1

    0 1 4 2 3 > swap 4 - 2
    0 1 2 4 3 > swap 4 - 3, retour au début


    (23)

-----
    0 1 2 3
    0 1 3 2
    0 2 1 3
    0 2 3 1
    0 3 1 2
    0 3 2 1

    1 0 2 3
    1 0 3 2
    1 2 0 3
    1 2 3 0
    1 3 0 2
    1 3 2 0
    2 0 1 3
    2 0 3 1
    2 1 0 3
    2 1 3 0
    2 3 0 1
    2 3 1 0
    3 0 1 2
    3 0 2 1
    3 1 2 0
    3 1 0 2
    3 2 0 1
    3 2 1 0*/
