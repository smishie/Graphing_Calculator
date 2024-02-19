#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include "../plot/plot.h"
#include "../graph_info.h"
#include <SFML/Graphics.hpp>
using namespace std;

class Graph{
public:
    Graph();
    Graph(Graph_info*& g);
    // Graph(Graph_info* g, string equation);

    void initAxis();
    void update(Graph_info*& g);
    void draw(sf::RenderWindow &window, vector<sf::Vector2f>& points);

private:
    errorCode* _error;

    string _equation = "";
    sf::CircleShape originDot = sf::CircleShape(3);
    vector<sf::CircleShape> circles;
    Graph_info* g_info;
    vector<sf::Vector2f> _points;
    sf::RectangleShape _x;
    sf::RectangleShape _y;
};

#endif 