#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include "../random/random.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cassert>
#include "../graph_info.h"
#include "../graph/graph.h"
#include "../plot/plot.h"
#include "../sidebar/sidebar.h"
#include <SFML/Graphics.hpp>

using namespace std;
class System{
public:
    System(): _info(new Graph_info()), _g(Graph()), _translate(new coordinate_translator(_info)){
        cout << "equation: " << _info->_equation << endl;}
    System(Graph_info* g);

    void Step(int command, Graph_info*& g);
    void Draw(sf::RenderWindow& widnow);
    
private:
    int size;
    Graph _g;
    string _equation;
    vector<sf::Vector2f> _points;
    Graph_info* _info;
    coordinate_translator* _translate;
};

#endif // SYSTEM_H
