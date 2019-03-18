
#ifndef ALGO_H
#define ALGO_H

#include <string>
#include <vector>
#include <algorithm>
#include <ostream>
#include <list>
#include <fstream>
#include <iosfwd>

#include "Graph.h"


using namespace std;

class Algo
{
public:

  Algo ();
  virtual ~Algo ();
  virtual void resolveAlgo(); 


};

#endif // ALGO_H
