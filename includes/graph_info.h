#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H
#include <iostream>
#include <iomanip>
#include <string>
#include "constants.h"
#include <SFML/Graphics.hpp>
using namespace std;

struct Graph_info{
    sf::Vector2f _window_dimensions = sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT);
    sf::Vector2f _origin = sf::Vector2f(WORK_PANEL - (WORK_PANEL / 2), SCREEN_HEIGHT - (SCREEN_HEIGHT / 2));
    sf::Vector2f _domain = sf::Vector2f(-5, 5);

    int _points = 10000;
    int fullDomain = abs(_domain.y - _domain.x);
    int calcFullD(){ return abs(_domain.y - _domain.x); }
    string _equation = "sin(x)";

    Graph_info() {
        _window_dimensions = sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT);
        _origin = sf::Vector2f(WORK_PANEL - (WORK_PANEL / 2), SCREEN_HEIGHT - (SCREEN_HEIGHT / 2));
        _domain = sf::Vector2f(-5, 5);

        int fullDomain = abs(_domain.y - _domain.x);

        _points = 1000;
        _equation = "sin(x^2)";

            bool debug = false;
            if(debug){
                cout << "Graph_info() CTOR" << endl;
            }
    }

};

#endif 