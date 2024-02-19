#ifndef PLOT_H
#define PLOT_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../rpn/rpn.h"
#include "../shunting_yard/shunting_yard.h"
#include "../token/token.h"
#include "../graph_2_screen.h"

using namespace std;

class Plot{
public:
    Plot(): info(new Graph_info()), translate(new coordinate_translator(info)){}

    Plot(Graph_info* g): info(g){
        try{
        translate = new coordinate_translator(info);
        ShuntingYard sy(info->_equation);
        _postfix = sy.postfix(); // changes the equation to postfix expression
        }
        catch(int error_code){
            cout << "PLOT: error_code [" << error_code << "]" << endl;
            _error->setCode(error_code);
        }
    }

    vector<sf::Vector2f> operator ()(){ // returns the vector of points
    // cout << "domain.x: " << info->_domain.x << "    domain.y: " << info->_domain.y << endl;
    int j = 0;
        try{
        for(float i = info->_domain.x; i <= info->_domain.y; i += (abs(info->_domain.y - info->_domain.x) / info->_points)){
            RPN rpn(_postfix);
            points.push_back(sf::Vector2f(i, rpn(i)));
            translate->translate(points[j]);
            j++;
        }
        // return points;
        } // end of try
        catch(int error_code){
            cout << "PLOT operator(): error_code [" << error_code << "]" << endl;
            _error->setCode(error_code);
        }
        return points;
    }

private:
    errorCode* _error;

    Queue<Token*> _postfix;
    vector<sf::Vector2f> points;
    Graph_info* info;
    coordinate_translator* translate;
};

#endif 