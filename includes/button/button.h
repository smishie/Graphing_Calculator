#ifndef BUTTON_H
#define BUTTON_H
#include <iostream>
#include "../constants.h"
#include "../graph_info.h"
#include <SFML/Graphics.hpp>

using namespace std;
struct Button{
    sf::RectangleShape button = sf::RectangleShape(sf::Vector2f(100, 30));
    sf::Text text;
    int btnWidth = 0;
    int btnHeight = 0;
    bool hovering = false;

    void changeBackColor(){
        button.setFillColor(sf::Color(216, 191, 216));
    }

    void returnBackColor(){
        button.setFillColor(sf::Color(230, 230, 250));
    }

    bool mouseOver(sf::RenderWindow &window){
        int mouseX = sf::Mouse::getPosition(window).x;
        int mouseY = sf::Mouse::getPosition(window).y;

        int btnPosX = button.getPosition().x;
        int btnPosY = button.getPosition().y;

        int btnxPosWidth = button.getPosition().x + btnWidth;
        int btnyPosHeight = button.getPosition().y + btnHeight;

        if(mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY){
            return true;
        }
        return false;
    }

    void drawTo(sf::RenderWindow &window){
        window.draw(button);
        window.draw(text);
    }

    void updateButtonHeight(int &saved_equations){
        btnHeight *= saved_equations;
    }

    void updateButtonPosition(int &saved_equations){
        button.setPosition(sf::Vector2f(WORK_PANEL + 10, SCREEN_HEIGHT - (((button.getLocalBounds().height + 20) * saved_equations) + 20)));
    }

    float getPositionx(){
       return button.getPosition().x; 
    }

    float getPositiony(){
        return button.getPosition().y;
    }

    Button(){}
    Button(int& saved_equations){
        button.setSize(sf::Vector2f(200, 20));
        // button.setFillColor(sf::Color(230, 230, 250));
        button.setFillColor(sf::Color::Green);
        button.setPosition(sf::Vector2f(WORK_PANEL + 10, SCREEN_HEIGHT - (((button.getLocalBounds().height + 10) * saved_equations) + 20)));

        int btnWidth = button.getSize().x;
        int btnHeight = button.getSize().y;

    }
    
    Button(string &equation, int &saved_equations, sf::Font &font){
        text = sf::Text("uhm" , font);
        text.setCharacterSize(40);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color(112, 41, 99));
        text.setPosition(sf::Vector2f(WORK_PANEL + 20, SCREEN_HEIGHT - (((text.getLocalBounds().height + 20) * saved_equations) + 20)));
        text.setString(equation);
        // cout << "text.position: (" << text.getPosition().x << ", " << text.getPosition().y << ")" << endl;

        button.setSize(sf::Vector2f(text.getLocalBounds().width + 5, text.getLocalBounds().height + 8));
        button.setFillColor(sf::Color(230, 230, 250));
        button.setPosition(text.getPosition()); 

        int btnWidth = button.getSize().x;
        int btnHeight = button.getSize().y;
    }
};

#endif