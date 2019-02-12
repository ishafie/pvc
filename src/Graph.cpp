#include <iostream>
#include <list>
#include <algorithm>
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

class Graph {
    private:
    int **tab;
    int summits = 0;


    public:
    Graph(int summits);
    Graph(ifstream &i);
    ~Graph();
    void print();
    auto generateRandomWeight(int max);
    void generateRandomGraph(ostream &o, int max);
    int getIntUpToDelimiter(string line, char delimiter);
    int **createTab(int summits);

};

int **Graph::createTab(int summits) {
    int **tabtmp = new int*[summits];
    for (int i = 0; i < summits;i++) {
        tabtmp[i] = new int[summits];
        for (int i2 = 0; i2 < summits; i2++) {
            tabtmp[i][i2] = 0;
        }
    }
    return tabtmp;
}

Graph::Graph(int summits) {
    this->summits = summits;
    this->tab = createTab(summits);
}

Graph::Graph(ifstream &i) {
    string line;
    cout << "reading file" << endl;
    getIntUpToDelimiter("", ' '); // to reset static int to 0
    if (i.is_open()) {
        getline(i, line);
        if (!(line.find_first_not_of( "0123456789" ) == string::npos)) {
            cout << "Wrong file" << endl;
            exit(0);    
        }
        cout << "aretes: " << line << endl;
        this->summits = stoi(line);
        this->tab = createTab(this->summits);
        while (getline(i, line)) {
            if (line.size() <= 0) {
                return ;
            }
            cout << line << endl;
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
            cout << "node1: " << node << " node2: " << node2 << " weight: " << weight << endl;
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
    /*for (int i = 0 ; i < summits; i++)
    {
        delete[] tab[i];
    }
    delete[] tab;*/
}

auto Graph::generateRandomWeight(int max) {
    std::list<int> ret;
    for (int i = 0; i < this->summits;i++) {
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
    for (int i = 0; i < this->summits; i++) {
        for (int i2 = 0; i2 < this->summits; i2++) {
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

void permut_tab(int **tab, int nb_permut, int n) {
    int swap = 0;
    //0, 1, 2
    //swap = 1
    //1, 0, 2
    //1,0,2 - 2,1,0 - 0,2,1
    //swap = 0
    //1, 2, 0  
        //cout << "index[" << i % n << "] = "<< (*tab)[i %n] <<", index + 1["<< (i + 1) % n << "] " << (*tab)[(i + 1) % n]  << endl;

    cout << "nb: " << nb_permut << endl;
    for (int i = 0; i < n; i++) {
        cout << (*tab)[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < nb_permut; i++) {
        swap = (*tab)[i % n];
        (*tab)[i] = (*tab)[(i + 1) % n];
        (*tab)[(i + 1) % n] = swap;
    }
}
int factorial(int input) {
    if (input <= 0)
        return 0;
    int res = 1;    
    while (input > 1) {
        res *= input;
        input -= 1;
    }
    return res;
}

int *create_tab(int n) {
    int *tab = new int[n];
    for (int i = 0; i < n; i++) {
        tab[i] = i;
    }
    return tab;
}

void swap(int *x, int *y) 
{ 
    int temp; 
    temp = *x; 
    *x = *y; 
    *y = temp; 
} 
  
void permute(list<list<int>> *ret, int *tab, int l, int n) 
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
          swap((tab + l), (tab + i)); 
          permute(ret, tab, l + 1, n); 
          swap((tab + l), (tab + i));
       } 
   } 
} 

list<list<int>> generate_permutations(int n) {
    list<list<int>> ret;
    int *tab = create_tab(n);
    permute(&ret, tab, 0, n - 1);
    delete tab;
    return ret;
}

list<list<int>> generate_one_permutations(int n, int depart) {
    list<list<int>> ret;
    int *tab = create_tab(n);
    tab[depart] = 0;
    tab[0] = depart;
    permute(&ret, tab, 1, n - 1);
    delete tab;
    return ret;
}

/*list<int> distances_boucles(list<list<int>> lb, int **tab) {

}*/

list<list<int>> genere_boucle(int n, int depart) {
    return generate_one_permutations(n, depart);
}


int main(void){
    list<list<int>> tmp = generate_one_permutations(3, 1);
    for_each(tmp.begin(), tmp.end(), [](list<int> l){
        for_each(l.begin(), l.end(), [](int a){cout << a << " ";});
        cout << endl;
    });
    /*std::ofstream file ("../resources/test.txt");
    srand (time(NULL));
    Graph g(5);
    cout << "starting pvc" << endl;
    g.print();
    g.generateRandomGraph(file, 10);
    file.close();
    std::ifstream input("../resources/test.txt");
    Graph g2(input);
    cout << "created" << endl;
    g2.print();
    input.close();*/
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