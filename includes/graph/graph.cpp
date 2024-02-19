#include "graph.h"

Graph::Graph(): g_info(new Graph_info()){
    initAxis();
    for(int i = 0; i < 1000; i++){
        circles.push_back(sf::CircleShape(2));
    }
    cout << "size: " << circles.size() << endl;
}

Graph::Graph(Graph_info*& g): g_info(g){
    initAxis();
    for(int i = 0; i < 1000; i++){
        circles.push_back(sf::CircleShape(2));
    }
    cout << "size: " << circles.size() << endl;
}

void Graph::initAxis(){
    _x = sf::RectangleShape(sf::Vector2f(2, SCREEN_WIDTH));
    _x.setPosition(g_info->_origin.x, SCREEN_HEIGHT - (SCREEN_HEIGHT / 2));
    _x.setOrigin(1, SCREEN_WIDTH/2);
    _x.setFillColor(sf::Color(207, 159, 255));
    _y = sf::RectangleShape(sf::Vector2f(WORK_PANEL, 2));
    _y.setPosition(WORK_PANEL - (WORK_PANEL / 2), g_info->_origin.y);
    _y.setOrigin(WORK_PANEL/2, 1);
    _y.setFillColor(sf::Color(207, 159, 255));

}

void Graph::update(Graph_info*& g){ 
    try{
    initAxis();
    g_info = g;
    originDot.setFillColor(sf::Color::Green);
    originDot.setOrigin(1.5, 1.5);
    originDot.setPosition(g_info->_origin);

    Plot _plot(g_info);
    // cout << "domain: (" << g_info->_domain.x << ", " << g_info->_domain.y << ")" << endl;
    // cout << "full domain: " << g_info->calcFullD() << endl;
    _points = _plot();

    for(int i = 0; i < g_info->_points; i++){
        circles[i].setFillColor(sf::Color(112, 41, 99));
        circles[i].setPosition(_points[i]);
    }
    } // end of try
    catch(int error_code){
        cout << "GRAPH update: error_code [" << error_code << "]" << endl;
        _error->setCode(error_code);
    }

}

void Graph::draw(sf::RenderWindow &window, vector<sf::Vector2f>& points){
    window.draw(_x);
    window.draw(_y);
/*
* screen and graph of domain and the first and last x points
*/
    /*// _points = points;
    // sf::Vector2f* ptr = &_points[0];
    sf::CircleShape dot = sf::CircleShape(3);
    for(int i = 0; i < g_info->_points; i++){ // drawing the dots on graph
        // cout << "point[" << i << "]: (" << ptr->x << ", " << ptr->y << ")" << endl;
        dot.setFillColor(sf::Color(170, 51, 106));
        dot.setPosition(_points[i]);
        // dot.setPosition(_points[i].x, _points[i].y);
        window.draw(dot);
        // ptr++;
    }*/
sf::CircleShape firstX = sf::CircleShape(3);
firstX.setFillColor(sf::Color::Green);
firstX.setOrigin(1.5, 1.5);
firstX.setPosition(_points[0]);

sf::CircleShape lastX = sf::CircleShape(3);
lastX.setFillColor(sf::Color::Green);
lastX.setOrigin(1.5, 1.5);
lastX.setPosition(_points[999]);

window.draw(firstX);
window.draw(lastX);

    for(int i = 0; i < g_info->_points; i++){
        window.draw(circles[i]);
    }
    window.draw(originDot);
}