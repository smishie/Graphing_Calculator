#ifndef GRAPH_2_SCREEN
#define GRAPH_2_SCREEN
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "graph_info.h"
#include "constants.h"

using namespace std;

struct coordinate_translator{
    Graph_info* _info = new Graph_info();
    coordinate_translator(Graph_info* g): _info(g){}

    void translate(sf::Vector2f& pos){
        pos.x = _info->_origin.x + pos.x * (_info->_window_dimensions.x / _info->fullDomain);
        pos.y = _info->_origin.y - pos.y * (_info->_window_dimensions.y / _info->fullDomain);
        // pos.y = _info->_origin.x - pos.y * (_info->_window_dimensions.x / _info->fullDomain);
    }
};

#endif