#include "Graph.h"
#include "Algo.h"
#include "Glouton.h"
#include "Genetic.h"
#include "bruteforce.h"
#include "pvc.h"

using namespace std;

void test_algo_genetique() {
    list<pair<int, int>> lc = {make_pair(0, 0), make_pair(1, 1),
        make_pair(2, 4), make_pair(1, -3), make_pair(0, -5), make_pair(0, 4),
        make_pair(-1, 5), make_pair(-2, 3), make_pair(-3, 0)};
    Genetic::algo_genetique(lc, 10, 3);
}


void test_bruteforce_pvc_coords() {
    list<pair<int, int>> lc = {make_pair(0, 0), make_pair(1, 1),
        make_pair(2, 4), make_pair(1, -3), make_pair(0, -5), make_pair(0, 4),
        make_pair(-1, 5), make_pair(-2, 3), make_pair(-3, 0)};
    BruteForce::bruteforce_pvc_coords(lc);
}

void test_glouton_pvc() {
    list<pair<int, int>> lc = {make_pair(0, 0), make_pair(1, 1),
        make_pair(2, 4), make_pair(1, -3), make_pair(0, -5), make_pair(0, 4),
        make_pair(-1, 5), make_pair(-2, 3), make_pair(-3, 0)};
    Glouton::glouton_pvc(lc);
}

void test_coord_vers_matrice() {
    list<pair<int, int>> lc = {make_pair(0, 0), make_pair(1, 1),
        make_pair(2, 4), make_pair(1, -3), make_pair(0, -5), make_pair(0, 4),
        make_pair(-1, 5), make_pair(-2, 3), make_pair(-3, 0)};
    Graph::Matrice m = Graph::Matrice::coord_vers_matrice(lc);
    m.print();
}

void test_meilleure_boucle(Graph g2) {
    vector<vector<int>> tab = g2.get_tab();
    list<list<int>> lb = BruteForce::generate_permutations(g2.get_sommets());
    pair<int, list<int>> m_b = BruteForce::meilleure_boucle(lb, tab);
    if (m_b.first == -1) {
        cout << "Echec de la fonction meilleure_boucle." << endl;
        return ;
    }
    cout << "La plus courte distance est " << m_b.first << " pour: ";
    for_each(m_b.second.begin(), m_b.second.end(), [](auto a) {
        cout << a << " ";
    });
    cout << endl;
}

void test_permutations() {
    list<list<int>> tmp = BruteForce::generate_permutations(4);
    for_each(tmp.begin(), tmp.end(), [](list<int> l){
        for_each(l.begin(), l.end(), [](int a){cout << a << " ";});
        cout << endl;
    });
}

void test_one_permutation() {
    list<list<int>> tmp = BruteForce::generate_one_permutations(3, 1);
    for_each(tmp.begin(), tmp.end(), [](list<int> l){
        for_each(l.begin(), l.end(), [](int a){cout << a << " ";});
        cout << endl;
    });
}

void test_distances_boucle(Graph g2) {
    vector<vector<int>> tab = g2.get_tab();
    list<list<int>> lb = BruteForce::generate_permutations(4);
    list<int> l = BruteForce::distances_boucles(lb, tab);
    cout << "distances: " << endl;
    list<list<int>>::iterator it = lb.begin();
    for_each(l.begin(), l.end(), [&it, lb](int distance){
        cout << "[ ";
        for_each(it->begin(), it->end(), [](auto noeud){
            cout << noeud << " ";
        });
        it++;
        cout << "] = " << distance << endl;
    });
    cout << endl;
}


void test_glouton_pvc_2_opt() {
    list<pair<int, int>> lc = {make_pair(0, 0), make_pair(1, 1),
        make_pair(2, 4), make_pair(1, -3), make_pair(0, -5), make_pair(0, 4),
        make_pair(-1, 5), make_pair(-2, 3), make_pair(-3, 0)};
    Glouton::glouton_pvc_2_opt(lc);
}




int main(void){
    srand (time(NULL));
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
    test_algo_genetique();
    // test_bruteforce_pvc_coords();
	// test_glouton_pvc_2_opt();
    // test_glouton_pvc();
    // bruteforce_pvc(g2);
    // test_permutations();
    // test_meilleure_boucle(g2);
    return (0);
}


