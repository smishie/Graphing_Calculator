#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;


class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width, vector<string>& old_equations);
    void draw(sf::RenderWindow& window);
    string& operator [](int index);
private:
    ifstream f;
    vector<string> history;

    sf::RectangleShape rect;            //sidebar rectangle
    vector<string> items;               //strings to place on the sidebar
    sf::Font font;                      //used to draw text
    sf::Text sb_text;                   //used to draw strings on the window object

    float _left;
    float _width;

};

#endif // SIDEBAR_H
