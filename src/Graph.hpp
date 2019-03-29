
#ifndef GRAPH_H
#define GRAPH_H
#include "pvc.hpp"
#include <string>
#include <vector>

using namespace std;
/**
  * class Graph
  * 
  */
  
class Graph
{

   private:
    
    std::vector<std::vector<int> >tab;
    int sommets = 0;
    



public:

  /**
   * @param  sommets
   * @param  max
   */
  void generer_poids_aleatoire (int sommets, int max);
  
  /**
   * @param  out
   */
  void generer_fichier (std::ostream & out);

  /**
   * @return int **
   * @param  file
   */
  int ** generer_matrice (std::ifstream & file);

  /**
   */
  void affiche_console ();

  /**
   * @param  n
   */
  void genere_permutations (int n);


  /**
   * @param  n
   * @param  depart
   */
  void genere_boucle (int n, int depart);



public:
    ~Graph();
    void print();
    auto generateRandomWeight(int max);
    void generateRandomGraph(std::ostream &o, int max);
    int getIntUpToDelimiter(std::string line, char delimiter);
    std::vector<std::vector<int>> createTab(int sommets);
    std::vector<std::vector<int>> get_tab();
    int get_sommets();
    static int distance(pair<int, int> a, pair<int, int> b);
    static void permute(list<list<int>> *ret, vector<int> tab, int l, int n);
    static list<list<int>> generate_permutations(int n) ;


//faire classe abstraite resoudre
    class Matrice {
        private:
        map<pair<int, int>, int> from_coord_to_index;
        map<int, pair<int, int>> from_index_to_coord;
        vector<vector<int>> tab;
        int sommets;

        public:
        Matrice(map<pair<int, int>, int> fcti, map<int, pair<int, int>> fitc, vector<vector<int>> tab, int sommets): 
          from_coord_to_index{fcti}, from_index_to_coord{fitc}, tab{tab}, sommets{sommets} {
        }
        void print();
        vector<vector<int>> get_matrice();
        void remove_index(int a);
        int get_sommets();
        map<pair<int, int>, int> get_coord_to_index();
        map<int, pair<int, int>> get_index_to_coord();

        int distance(pair<int, int> a, pair<int, int> b) {
          return sqrt(((b.first - a.first) * (b.first - a.first)) + ((b.second - a.second) * (b.second - a.second)));
        }

        static Matrice coord_vers_matrice(list<pair<int, int>> lc);
        
    };






Graph(int sommets) {
    this->sommets = sommets;
    this->tab = createTab(sommets);
}

Graph(std::ifstream &i) {
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
  /**
   * Set the value of tab
   * @param new_var the new value of tab
   */
  void setTab (std::vector<std::vector<int> > new_var)   {
      tab = new_var;
  }

  /**
   * Get the value of tab
   * @return the value of tab
   */
  
  std::vector<std::vector<int> > getTab ()   {
    return tab;
  }
private:


  void initAttributes () ;

};

#endif // GRAPH_H
