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

int main(void){
    std::ofstream file ("../resources/test.txt");
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
    input.close();
    return (0);
}