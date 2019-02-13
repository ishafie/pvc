
#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>



/**
  * class Graph
  * 
  */




class Graph
{

   private:
    
    std::vector<std::vector<int> >tab;
    int summits = 0;


public:
    
  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Graph ();

  /**
   * Empty Destructor
   */
  virtual ~Graph ();


  /**
   * @param  sommets
   * @param  max
   */
  void generer_poids_aleatoire (int sommets, int max)
  {
  }


  /**
   * @param  out
   */
  void generer_fichier (std::ostream & out)
  {
  }

  /**
   * @return int **
   * @param  file
   */
  int ** generer_matrice (std::ifstream & file)
  {
  }


  /**
   */
  void affiche_console ()
  {
  }


  /**
   * @param  n
   */
  void genere_permutations (int n)
  {
  }


  /**
   * @param  n
   * @param  depart
   */
  void genere_boucle (int n, int depart)
  {
  }



public:
    Graph(int summits);
    Graph(std::ifstream &i);
    void print();
    auto generateRandomWeight(int max);
    void generateRandomGraph(std::ostream &o, int max);
    int getIntUpToDelimiter(std::string line, char delimiter);
    std::vector<std::vector<int> >createTab(int summits);

  // Private attribute accessor methods
  //  


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
