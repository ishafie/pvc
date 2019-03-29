

#include "bruteforce.hpp"




list<list<int>> BruteForce::generate_one_permutations(int n, int depart) {
    list<list<int>> ret;
    vector<int> tab(n);
    for (int i = 0; i < n; i++) {
        tab[i] = i;
    }
    tab[depart] = 0;
    tab[0] = depart;
    Graph::permute(&ret, tab, 1, n - 1);
    return ret;
}

list<int>  BruteForce::distances_boucles(list<list<int>> lb, vector<vector<int>> tab) {
    list<int> ret;
    for_each(lb.begin(), lb.end(), [&ret, tab](list<int> boucle){
        int distance = 0;
        int last_index = 0;
        for (list<int>::iterator it = boucle.begin(); next(it) != boucle.end(); it++) {
            // cout << "tab[" << *it << "][" << *next(it) << "] = " << tab[*it][*next(it)] << endl;
            distance += tab[*it][*next(it)];
            last_index = *next(it);
        }
        distance += tab[last_index][*(boucle.begin())]; // return to first index.
        ret.push_back(distance);
    });
    return ret;
}

list<list<int>> BruteForce::genere_boucle(int n, int depart) {
    return generate_one_permutations(n, depart);
}

pair<int, list<int>> BruteForce::meilleure_boucle(list<list<int>> lb, vector<vector<int>> tab) {
    pair<int, list<int>> ret;
    list<int> l =  BruteForce::distances_boucles(lb, tab);
    list<list<int>>::iterator it = lb.begin();
    auto min_it = min_element(l.begin(), l.end());
    int min_index = distance(l.begin(), min_it);
    for (int i = 0; it != lb.end() && i < min_index; i++) {
        it++;
    }
    if (it != lb.end()) {
        return make_pair(*min_it, *it);
    }
    return make_pair(-1, l);
}

void BruteForce::bruteforce_pvc(Graph g2) {
    vector<vector<int>> tab = g2.get_tab();
    list<list<int>> lb = generate_one_permutations(g2.get_sommets(), 0);
    pair<int, list<int>> m_b = meilleure_boucle(lb, tab);
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

void BruteForce::bruteforce_pvc_coords(list<pair<int, int>> lc) {
    Graph::Matrice m = Graph::Matrice::coord_vers_matrice(lc);
    map<int, pair<int, int>> from_index_to_coord = m.get_index_to_coord();
    vector<vector<int>> tab = m.get_matrice();
    list<list<int>> lb = generate_one_permutations(m.get_sommets(), 0);
    pair<int, list<int>> m_b = meilleure_boucle(lb, tab);
    if (m_b.first == -1) {
        cout << "Echec de la fonction meilleure_boucle." << endl;
        return ;
    }
    cout << "La plus courte distance est " << m_b.first << " pour: " << endl;
    for_each(m_b.second.begin(), m_b.second.end(), [&from_index_to_coord](auto a) {
        pair<int, int> coords = from_index_to_coord[a];
        cout << "(" << coords.first << ", " << coords.second << ")" << endl;
    });
    
}



