#ifndef ANIMATE_H
#define ANIMATE_H
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <fstream>
#include <cstdlib>
#include "../button/button.h"
#include "../textbox/textbox.h"
#include "../system/system.h"
#include "../errorCode/errorCode.h"

class animate{
public:
    animate();

    void checkErrorCodes();

    void saveHistory();
    void clearHistory();
    void makeFileHistory();
    void makeEqBox();
    void getDomains();
    void writeEqBox();
    void updateHistory();
    void checkButtons();
    void checkButtons2();
    // void set_info(Graph_info* g);
    void run();
    void processEvents();
    void update();
    void render();
    void Draw();

private:
    errorCode inputError;

    fstream f;
    // vector<sf::Text> fileHistory;
    // sf::Text fileHistory;
    vector<Textbox*> fileHistory;

    sf::Vector2f points;
    Graph_info* g_info;
    sf::RenderWindow window;
    sf::CircleShape mousePoint;         //The little red dot
    System system;                      //container for all the animated objects
    int command;                        //command to send to system
    sf::Font font;                      //font to draw on main screen
    sf::Text myKey;                     // key dropdown
    sf::Text myTextLabel;               //text to draw on main screen
    bool mouseIn;                       //mouse is in the screen
    Sidebar sidebar;                    //rectangular message sidebar

    sf::RectangleShape eqbg;
    Textbox* userEq;
    sf::Text eqBox;    

    bool isTyping = false;

    sf::Text leftDomain;
    sf::Text rightDomain;
    stringstream leftdomain;
    stringstream rightdomain;
    string ldstring;
    string rdstring;

    vector<string> old_equations;
    vector<Button*> old_equations_buttons;
    int saved_equations = 0;
    int totalbtnHeight = 0;
    Button* history;
    bool overButton = false;
    bool clicked;
    float mouseX, mouseY;
};

string mouse_pos_string(sf::RenderWindow& window);

#endif // GAME_H
