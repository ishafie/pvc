#include "Glouton.hpp"


int Glouton::solve_glouton(Graph::Matrice m, list<pair<int, int>> lc, pair<int, int> start_coord, vector<pair<int, int>> *ret) {
    if (lc.size() <= 0)
        return 0;
    map<int, pair<int, int>> from_index_to_coord = m.get_index_to_coord();
    map<pair<int, int>, int> from_coord_to_index = m.get_coord_to_index();
    vector<vector<int>> tab = m.get_matrice();
    int sommets = m.get_sommets();
    int start_index = from_coord_to_index[start_coord];
    int min_index = start_index == 0 ? 1 : 0;
    int min_distance = INT_MAX;
    pair<int, int> min_coord = start_index == 0 ? from_index_to_coord[1] : from_index_to_coord[0];
    for (int i = 0; i < sommets; i++) {
        if (start_index != i && tab[start_index][i] != -1 && tab[start_index][i] < min_distance) {
            // cout << "i : " << i << endl;
            min_index = 1;
            min_distance = tab[start_index][i];
            min_coord = from_index_to_coord[i];
			// cout << "tab[][]=" << tab[start_index][i] << endl;
        }
    }
    /* cout << "min_distance: " << min_distance << endl;
    cout << "startindex: " << start_index << endl;
    cout << "minindex: " << min_index << endl;
    cout << "min: (" << min_coord.first << ", " << min_coord.second << ") " << endl;
    cout << "removing index: " << start_index << ", " << min_index << endl;*/
    m.remove_index(start_index);
    lc.remove(start_coord);
    lc.remove(min_coord);
    ret->push_back(min_coord);    
    return min_distance + solve_glouton(m, lc, min_coord, ret);
}

vector<pair<int, int>> Glouton::glouton_pvc(list<pair<int, int>> lc) {
    // construire pas à pas
    // partir d'un sommet quelconque et itérer, à chaque itération
    // on relie le dernier sommet atteint au sommet le plus proche en excluant les sommets deja parcourus
    // a la fin on relie le dernier sommet au premier sommet.
    // (0, 0) => 
    Graph::Matrice m = Graph::Matrice::coord_vers_matrice(lc);
    map<int, pair<int, int>> from_index_to_coord = m.get_index_to_coord();
    map<pair<int, int>, int> from_coord_to_index = m.get_coord_to_index();
    vector<vector<int>> tab = m.get_matrice();

    vector<pair<int, int>> ret;
    ret.push_back(*(lc.begin()));
    int distance = solve_glouton(m, lc, *(lc.begin()), &ret);
    pair<int, int> end = *(--ret.end());
    distance += tab[from_coord_to_index[end]][from_coord_to_index[*(lc.begin())]];
    cout << "distance: " << distance << endl;
    for_each(ret.begin(), ret.end(), [](auto a){
        cout << "(" << a.first << ", " << a.second << ") ";
    });
    cout << endl;
    return ret;
    // (0, 0) (1, 1) (2, 4) (0, 4) (-1, 5) (-2, 3) (-3, 0) (1, -3) (0, -5)
}


/*void solve_glouton_for_opt(Matrice m, list<pair<int, int>> lc, pair<int, int> start_coord, vector<pair<int, int>> *ret) {
    cout << "size: " << lc.size() << endl;
    if (lc.size() == 1){
		ret->push_back(lc.front());
        return ;
	}
	if (lc.size() < 0){
        return ;
	}
	m=coord_vers_matrice(lc);
    map<int, pair<int, int>> from_index_to_coord = m.get_index_to_coord();
    map<pair<int, int>, int> from_coord_to_index = m.get_coord_to_index();
    vector<vector<int>> tab = m.get_matrice();
    int sommets = m.get_sommets();
    int start_index = from_coord_to_index[start_coord];
    int min_distance = start_index == 0 ? tab[start_index][1] : tab[start_index][0];
    pair<int, int> min_coord = start_index == 0 ? from_index_to_coord[1] : from_index_to_coord[0];
    cout << "startindex: " << start_index << endl;
    cout << "min_distance: " << min_distance << endl;
    for (int i = 0; i < sommets; i++) {
        if (start_index != i && tab[start_index][i] <= min_distance) {
            min_distance = tab[start_index][i];
            min_coord = from_index_to_coord[i];
			//cout << "tab[][]=" << tab[start_index][i] << endl;
        }
    }

    lc.remove(start_coord);
    lc.remove(min_coord);
	for (auto a : lc){
		cout << a.first << " " << a.second << endl;
	}

    cout << "size after delete: " << lc.size() << endl;
    ret->push_back(min_coord);
    return solve_glouton_for_opt(m, lc, min_coord, ret);
}*/




auto Glouton::solve_2_opt(vector<pair<int, int>> *ret){
	bool better = true;
	int s = ret->size();
	//cout << " size -1 = " << s << endl;
	while (better == true) {
		better = false;
		//cout << " ----------  restart  ----------" << endl;
		for (int i = 0; i < ret->size(); i ++){
			for (int j = 0; j < ret->size() ; j ++){
				if ( j != i -1  && j != i && j != i+1){
					//if (distance(ret->at(i), ret->at(i+1)) + distance(ret->at(j),ret->at(j+1)) > distance(ret->at(i),ret->at(j)) + distance(ret->at(i+1),ret->at(j+1))){
					//cout << "x=" << i << ", y=" << j << " ====>  " ;
					//cout << distance((*ret)[i], (*ret)[i+1 % s]) + distance((*ret)[j],(*ret)[j+1 % s]) << " - ";
					//cout << distance((*ret)[i], (*ret)[j]) + distance((*ret)[i+1],(*ret)[j+1]) << endl;
					if (Graph::distance((*ret)[i], (*ret)[i+1 % s]) + Graph::distance((*ret)[j],(*ret)[j+1 % s]) > Graph::distance((*ret)[i],(*ret)[j]) + Graph::distance((*ret)[i+1 % s],(*ret)[j+1 % s])){
						//cout << "btter found !" << endl;
						pair<int, int> tmp = (*ret)[i+1%s];
						(*ret)[i+1%s] = (*ret)[j%s];
						(*ret)[j%s]= tmp;
						
						better = true;
					}
				}
			}
		}
	}
	return ret;
}


vector<pair<int, int>> Glouton::glouton_pvc_2_opt(list<pair<int, int>> lc) {
    // opt-2 a partir glouton_pvc
    // (0, 0) => 
    
    Graph::Matrice::coord_vers_matrice(lc);
    vector<pair<int, int>> ret = glouton_pvc(lc);
    // solve_glouton_for_opt(m, lc, *(lc.begin()), &ret);
	cout << "Before 2-opt : " << endl;
    for_each(ret.begin(), ret.end(), [](auto a){
        cout << "(" << a.first << ", " << a.second << ") ";
    });
    cout << endl;
	solve_2_opt(&ret);
	cout << "after : " << endl;
	for_each(ret.begin(), ret.end(), [](auto a){
        cout << "(" << a.first << ", " << a.second << ") ";
    });
    cout << endl;
    return ret;

};








