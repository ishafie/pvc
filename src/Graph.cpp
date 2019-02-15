#include <iostream>
#include <list>
#include <algorithm>
#include <time.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class Matrice {
    private:
    map<int, int> from_coord_to_index;
    map<int, int> from_index_to_coord;
    vector<vector<int>> tab;

    public:
    Matrice(map<int, int> fcti, map<int, int> fitc, vector<vector<int>> tab);
    map<int, int> getCoordToIndex();
    map<int, int> getIndexToCoord();
    vector<vector<int>> getMatrice();
};

Matrice::Matrice(map<int, int> fcti, map<int, int> fitc, vector<vector<int>> tab): 
    from_coord_to_index{fcti}, from_index_to_coord{fitc}, tab{tab} {
}

class Graph {
    private:
    vector<vector<int>> tab;
    int sommets = 0;
    


    public:
    Graph(int sommets);
    Graph(ifstream &i);
    ~Graph();
    void print();
    auto generateRandomWeight(int max);
    void generateRandomGraph(ostream &o, int max);
    int getIntUpToDelimiter(string line, char delimiter);
    vector<vector<int>> createTab(int sommets);
    vector<vector<int>> get_tab();
    int get_sommets();
};

vector<vector<int>> Graph::createTab(int sommets) {
    vector<vector<int>> tabtmp(sommets, vector<int>(sommets, 0));
    return tabtmp;
}

Graph::Graph(int sommets) {
    this->sommets = sommets;
    this->tab = createTab(sommets);
}

Graph::Graph(ifstream &i) {
    string line;
    // cout << "reading file" << endl;
    getIntUpToDelimiter("", ' '); // to reset static int to 0
    if (i.is_open()) {
        getline(i, line);
        if (!(line.find_first_not_of( "0123456789" ) == string::npos)) {
            cout << "Wrong file" << endl;
            exit(0);    
        }
        // cout << "aretes: " << line << endl;
        this->sommets = stoi(line);
        this->tab = createTab(this->sommets);
        while (getline(i, line)) {
            if (line.size() <= 0) {
                return ;
            }
            // cout << line << endl;
            int node = getIntUpToDelimiter(line, ' ');
            if (node == -1) {
                cout << "Wrong file" << endl;
                exit(0);
            }
            int node2 = getIntUpToDelimiter(line, ' ');
            if (node2 == -1) {
                cout << "Wrong file" << endl;
                exit(0);
            }
            int weight = getIntUpToDelimiter(line, ' ');
            if (weight == -1) {
                cout << "Wrong file" << endl;
                exit(0);
            }
            getIntUpToDelimiter("", ' '); // to reset static
            this->tab[node][node2] = weight;
            // cout << "node1: " << node << " node2: " << node2 << " weight: " << weight << endl;
        }
    }
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
    /*for (int i = 0 ; i < sommets; i++)
    {
        delete[] tab[i];
    }
    delete[] tab;*/
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

void Graph::generateRandomGraph(ostream &o, int max) {
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

void permute(list<list<int>> *ret, vector<int> tab, int l, int n) 
{ 
    int i; 
    if (l == n) {
        list<int> tmp;
        for (int index = 0; index <= n; index++) {
            tmp.push_back(tab[index]);
        }
        ret->push_back(tmp);
    }
     
    else
    { 
        for (i = l; i <= n; i++) 
        {
            iter_swap(tab.begin() + l, tab.begin() + i);
            permute(ret, tab, l + 1, n); 
            iter_swap(tab.begin() + l, tab.begin() + i);
        }
    } 
} 

list<list<int>> generate_permutations(int n) {
    list<list<int>> ret;
    vector<int> tab(n);
    for (int i = 0; i < n; i++) {
        tab[i] = i;
    }
    permute(&ret, tab, 0, n - 1);
    return ret;
}

list<list<int>> generate_one_permutations(int n, int depart) {
    list<list<int>> ret;
    vector<int> tab(n);
    for (int i = 0; i < n; i++) {
        tab[i] = i;
    }
    tab[depart] = 0;
    tab[0] = depart;
    permute(&ret, tab, 1, n - 1);
    return ret;
}

list<int> distances_boucles(list<list<int>> lb, vector<vector<int>> tab) {
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

list<list<int>> genere_boucle(int n, int depart) {
    return generate_one_permutations(n, depart);
}

pair<int, list<int>> meilleure_boucle(list<list<int>> lb, vector<vector<int>> tab) {
    pair<int, list<int>> ret;
    list<int> l = distances_boucles(lb, tab);
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

void bruteforce_pvc(Graph g2) {
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

int distance(pair<int, int> coord) {
    // do distance
    return 0;
}

Matrice coord_vers_matrice(list<pair<int, int>> lc) {
    map<int, int> from_coord_to_index;
    map<int, int> from_index_to_coord;
    for (int i = 0; i < lc.size();i++) {
        from_coord_to_index[i] = -1;
    }
    int i = 0;
    for_each(lc.begin(), lc.end(), [&from_coord_to_index, &i](auto coord){
        if (from_coord_to_index.find(coord.first) == from_coord_to_index.end()) {
            from_coord_to_index[coord.first] = i;
            from_index_to_coord[i] = coord.first;
            i++;
        }
        if (from_coord_to_index.find(coord.second) == from_coord_to_index.end()) {
            from_coord_to_index[coord.second] = i;
            from_index_to_coord[i] = coord.second;
            i++;
        }
    });
    vector<vector<int>> tab(i);
    for_each(lc.begin(), lc.end(), [&from_coord_to_index, &i](auto coord){
        tab[from_coord_to_index[coord.first]][from_coord_to_index[coord.second]] = distance(coord);
    });
    return Matrice(from_coord_to_index, from_index_to_coord, tab);
    //put coord vers matrice in class to have access to both maps everywhere
}


void test_coord_vers_matrice() {
    list<pair<int, int>> lc = {make_pair(0, 0), make_pair(1, 1),
        make_pair(2, 4), make_pair(1, -3), make_pair(0, -5), make_pair(0, 4),
        make_pair(-1, 5), make_pair(-2, 3), make_pair(-3, 0)};
    coord_vers_matrice(lc);
}

void test_meilleure_boucle(Graph g2) {
    vector<vector<int>> tab = g2.get_tab();
    list<list<int>> lb = generate_permutations(g2.get_sommets());
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

void test_permutations() {
    list<list<int>> tmp = generate_permutations(4);
    for_each(tmp.begin(), tmp.end(), [](list<int> l){
        for_each(l.begin(), l.end(), [](int a){cout << a << " ";});
        cout << endl;
    });
}

void test_one_permutation() {
    list<list<int>> tmp = generate_one_permutations(3, 1);
    for_each(tmp.begin(), tmp.end(), [](list<int> l){
        for_each(l.begin(), l.end(), [](int a){cout << a << " ";});
        cout << endl;
    });
}

void test_distances_boucle(Graph g2) {
    vector<vector<int>> tab = g2.get_tab();
    list<list<int>> lb = generate_permutations(4);
    list<int> l = distances_boucles(lb, tab);
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

int main(void){
    /*std::ofstream file ("../resources/test.txt");
    srand (time(NULL));
    Graph g(5);
    cout << "starting pvc" << endl;
    g.generateRandomGraph(file, 10);
    file.close();
    g.print();*/
    std::ifstream input("../resources/complet.txt");
    Graph g2(input);
    cout << "created" << endl;
    g2.print();
    input.close();
    test_coord_vers_matrice();
    // bruteforce_pvc(g2);
    // test_permutations();
    // test_meilleure_boucle(g2);
    return (0);
}




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