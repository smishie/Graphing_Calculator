#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "../constants.h"
#include <SFML/Graphics.hpp>

#define DELETE_KEY 8
#define ENTER_KEY 13                              
#define TAB_KEY 9

using namespace std;

struct Textbox{ 
    sf::Text textbox;
    std::ostringstream text;
    bool isSelected = false;

    void inputLogic(int typed){
        if(typed != DELETE_KEY && typed != TAB_KEY && typed != ENTER_KEY){
            text << static_cast<char>(typed);
        }
        else if(typed == DELETE_KEY){
            if(text.str().length() > 0){
                deleteLastChar(); 
            }
        }
        textbox.setString(text.str() + "_"); // sets underscore at the end of last input collected
    }

    void deleteLastChar(){
        string org = text.str();
        string new_str = "";

        for(int i  = 0; i < org.length() - 1; i++){
            new_str += org[i];
        }
        text.str(""); // wipe original string
        text << new_str; // replace with new, deleted end string
        textbox.setString(text.str());
    }

    Textbox(string& equation, int& saved_equations, sf::Font font){
        textbox = sf::Text("uhm" , font);
        textbox.setCharacterSize(30);
        textbox.setStyle(sf::Text::Bold);
        textbox.setFillColor(sf::Color(112, 41, 99));
        textbox.setPosition(sf::Vector2f(WORK_PANEL + 10, SCREEN_HEIGHT - (textbox.getLocalBounds().height * saved_equations)));
        textbox.setString(equation);
    }

    Textbox(bool& clicked){ 
        isSelected = clicked;

        textbox.setCharacterSize(20);
        textbox.setStyle(sf::Text::Bold);
        textbox.setFillColor(sf::Color(112, 41, 99));
        textbox.setPosition(sf::Vector2f(10, SCREEN_HEIGHT - (2 * textbox.getLocalBounds().height)));
        textbox.setString("_");

        if(isSelected){
            // textbox.setString("_");
            textbox.setString("_");
        }
        else{
            textbox.setString("");
        }
    }
};

#endif 