#include "animate.h"

animate::animate() : sidebar(WORK_PANEL, SIDE_BAR, old_equations), g_info(new Graph_info()){
    cout << "animate CTOR: TOP" << endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "hihi SFML!");
    // VideoMode class has functions to detect screen size etc.
    // RenderWindow constructor has a third argumnet to set style
    // of the window: resize, fullscreen etc.

    //   System will be implemented to manage a vector of objects to be animated.
    //   at that point, the constructor of the System class will take a vector
    //   of objects created by the animate object.
    //   animate will
    window.setFramerateLimit(60);

    mouseIn = true;

    mousePoint = sf::CircleShape();
    mousePoint.setRadius(5.0);
    mousePoint.setFillColor(sf::Color(191, 64, 191));

    cout << "Geme CTOR. preparing to load the font." << endl;
    //--- FONT ----------
    // font file must be in the "working directory:
    //      debug folder
    // Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    // font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "animate() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }

    myTextLabel = sf::Text("Smii's Graphing Calculator", font);
    myTextLabel.setCharacterSize(40);
    myTextLabel.setStyle(sf::Text::Bold);
    myTextLabel.setFillColor(sf::Color(255, 255, 255));
    myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT - myTextLabel.getLocalBounds().height - 5));

    //--- LEFTDOMAIN ----------
    leftDomain = sf::Text("x: ", font);
    leftDomain.setCharacterSize(30);
    leftDomain.setStyle(sf::Text::Bold);
    leftDomain.setFillColor(sf::Color(255, 255, 255));
    leftDomain.setPosition(sf::Vector2f(10, SCREEN_HEIGHT / 2 + 10));

    //--- RIGHTDOMAIN ----------
    rightDomain = sf::Text("y: ", font);
    rightDomain.setCharacterSize(30);
    rightDomain.setStyle(sf::Text::Bold);
    rightDomain.setFillColor(sf::Color(255, 255, 255));
    rightDomain.setPosition(sf::Vector2f(WORK_PANEL + 50, SCREEN_HEIGHT / 2 + 10));

    //--- USERIN ------------
    if(isTyping){ // creates background rectangle and textbox once clicked
        makeEqBox();
    }
    saved_equations = 0;

    f.open("history.txt", ios::in | ios::out);
    if(f.fail()){
        cout << "FILE DIDNT OPEN, CANT RETREIVE OLD HISTORY !" << endl;
        exit(1);   
    }
    f >> saved_equations; // number of saved
    string str = "";
    for(int i = 0; i < saved_equations; i++){
        int j = i + 1;
        getline(f, str);
        old_equations.push_back(str);
        g_info->_equation = old_equations[i];
        cout << "saved " << old_equations[i] << " to old_equations..." << endl;
        old_equations_buttons.push_back(new Button(g_info->_equation, j, font));
        // updateHistory(); // saves the Text, new Button
        str.clear();
    }
    if(saved_equations > 0){
        totalbtnHeight = (old_equations_buttons[0]->text.getLocalBounds().height * (saved_equations + 1)) + 20; // number of buttons to total
    }
    f.close();

    cout << "animate instantiated successfully." << endl;
}

void animate::checkErrorCodes(){
    switch(inputError.error_code){
        // case 1:
        // break;
        // case 2:
        // break;
        case 3:
            sidebar[SB_KEY_PRESSED] = "ERROR IN EQUATION, \ndividing by zero";
        break;
        case 7:
            sidebar[SB_KEY_PRESSED] = "ERROR IN EQUATION, \nextra left parentheses";
        break;
        default:
            sidebar[SB_KEY_PRESSED] = "ERROR IN EQUATION";
        break;
    }
    userEq->text.str(""); // clean string
    saved_equations--;
    old_equations.pop_back();
    old_equations_buttons.pop_back();
    inputError.error_code = 0;
    makeEqBox();
}

void animate::saveHistory(){
    f.open("history.txt", ios::in | ios::out); // overwrites from the top
        if(f.fail()){
            cout << "FILE DIDNT OPEN, CANT INPUT ! (2)" << endl;
            exit(1);   
        }
        f << saved_equations; // number of saved
        if(saved_equations == 1){
            f << old_equations[0];
        }
        else if(saved_equations > 1){
            for(int i = 0   ; i < saved_equations; i++){
                f << old_equations[i] << endl;
                cout << "IN: wrote " << old_equations[i] << " to file..." << endl;
            }   
        }
        
    f.close();
}

void animate::clearHistory(){
    saved_equations = 0;
    old_equations.clear();
    old_equations_buttons.clear();
    // f.open("history.txt", ios::in | ios::out);
    f.open("history.txt", ios::out);
    if(f.fail()){
        cout << "FILE DIDNT OPEN, CANT CLEAR !" << endl;
        exit(1);   
    }
    f.clear();
    f.close();
}

void animate::updateHistory(){
    old_equations_buttons.push_back(new Button(g_info->_equation, saved_equations, font));
    // fileHistory.push_back(new Textbox(g_info->_equation, saved_equations, font));
    /*
    * instead of vector of buttons that keeps track
    * create buttons
    * use math based off the mouseY and text height to determine which button hovering/clicked
    * DELETE NEWLY ALLOCATED
    */
    // old_equations.push_back(g_info->_equation); // vector of strings
    cout << "equations in history: " << saved_equations << endl;
    if(saved_equations == 1){
        // totalbtnHeight = history_button->text.getLocalBounds().height;
        totalbtnHeight = old_equations_buttons[0]->text.getLocalBounds().height;
    }
    else if(saved_equations > 0){
        // totalbtnHeight = (history_button->text.getLocalBounds().height * (saved_equations + 1)) + 20; // number of buttons to total
        totalbtnHeight = (old_equations_buttons[0]->text.getLocalBounds().height * (saved_equations + 1)) + 20; // number of buttons to total
    }
    // for(int i = 0; i < saved_equations; i++){
    //     cout << i << ": " << old_equations[i] << endl;
    // }
}

void animate::makeFileHistory(){
    // fileHistory = sf::Text("uhm" , font);
    // fileHistory.setCharacterSize(20);
    // fileHistory.setStyle(sf::Text::Bold);
    // fileHistory.setFillColor(sf::Color(112, 41, 99));
    // fileHistory.setPosition(sf::Vector2f(WORK_PANEL + 20, SCREEN_HEIGHT - (((fileHistory.getLocalBounds().height + 20) * saved_equations) + 20)));

    if(!old_equations.empty()){
        f.open("history.txt");
        if(f.fail()){
            cout << "FILE DIDNT OPEN, CAN'T OUTPUT !" << endl;
            exit(1);
        }
        for(int i = 0; i < old_equations.size(); i++){
            f >> old_equations[i];
            // fileHistory.setString();
            // file.push_back(old_equations[i]);
        }
        f.close();
    }
}

void animate::checkButtons(){
    for(float i = 0; i < saved_equations; i++){
        // find individual button, hovering above
        if(mouseX < WORK_PANEL + 20 + old_equations_buttons[i]->text.getLocalBounds().width && overButton == true){ // within individual button width
            if(saved_equations == 1){
                old_equations_buttons[i]->hovering = true;
                // overButton = true;
                if(clicked){
                    g_info->_equation = old_equations[i];
                }
            }

            if(saved_equations > 1 && mouseY < SCREEN_HEIGHT - (old_equations_buttons[i]->btnHeight * saved_equations)){ // doesnt count mouseY below all buttons
                old_equations_buttons[i]->hovering = true;
                cout << "hovering! over button: " << i << endl;
                // overButton = true;
            }
        }
        else{ // not in sidebar, saved_equation_button[i] is not below all button (mouse too high)
            old_equations_buttons[i]->hovering = false;
            overButton = false;
            clicked = false;
        }
        if((mouseY > SCREEN_HEIGHT - old_equations_buttons[i]->getPositiony()) && (mouseY > SCREEN_HEIGHT - old_equations_buttons[i]->getPositiony())){ // within individual button height
            if(old_equations_buttons[i]->hovering){
                old_equations_buttons[i]->changeBackColor();
                if(clicked){
                    cout << "clicked on button " << i << " !" << endl;
                    g_info->_equation = old_equations[i];
                }
            }
            else if(!old_equations_buttons[i]->hovering){
                old_equations_buttons[i]->returnBackColor();
                clicked = false;
            }
        }
    }
}

void animate::checkButtons2(){
    for(int i = 0; i < saved_equations; i++){
        // within sidebar and end of button width, within totalbtnheight
        if(mouseX < WORK_PANEL + 20 + old_equations_buttons[i]->text.getLocalBounds().width && overButton == true){ 
// FIRST BUTTON
            if(saved_equations == 1){
                if(mouseY > SCREEN_HEIGHT - 40 -(old_equations_buttons[0]->text.getLocalBounds().height + 10) && mouseY < SCREEN_HEIGHT - 40){
                    // cout << "hovering over button: 0" << endl;
                    old_equations_buttons[0]->hovering == true;
                    old_equations_buttons[0]->changeBackColor();
                }
                else{
                    old_equations_buttons[0]->hovering == false;
                    old_equations_buttons[0]->returnBackColor();
                }
            }

            // mouseY is greater than current button but less than one before
            if(saved_equations >= 2){ // finding button between i + 1 and i + 2...
                if(mouseY < SCREEN_HEIGHT - 40 - ((old_equations_buttons[0]->text.getLocalBounds().height + (i * 2)) * i) && mouseY > SCREEN_HEIGHT - 40 - ((old_equations_buttons[0]->text.getLocalBounds().height + (i * 2)) * (i + 1))){
                    // cout << "hovering over button: " << i << endl;
                    old_equations_buttons[i]->hovering = true;
                    old_equations_buttons[i]->changeBackColor();
                    if(old_equations_buttons[i]->hovering && clicked){
                        sidebar[SB_KEY_PRESSED] = "CLICKED PAST EQUATION";
                        g_info->_equation = old_equations[i];
                        clicked = false;
                    }
                }
                else{
                    old_equations_buttons[i]->hovering == false;
                    old_equations_buttons[i]->returnBackColor();
                }      
    
            }

        }  
    }  
}

void animate::getDomains(){
    string ldstring = "";
    string rdstring = "";
    leftdomain.str("");
    rightdomain.str("");

    leftdomain << std::fixed << setprecision(3) << g_info->_domain.x;
    ldstring = leftdomain.str();   
    leftDomain.setString("x: " + ldstring); 
    leftDomain.setPosition(sf::Vector2f(10, g_info->_origin.y)); // follows the y axis

    rightdomain << std::fixed << setprecision(3) << g_info->_domain.y;
    rdstring = rightdomain.str();    
    rightDomain.setString("y: " + rdstring);
    rightDomain.setPosition(sf::Vector2f(WORK_PANEL - 125, g_info->_origin.y)); // follows the y axis
}

void animate::makeEqBox(){
        eqbg = sf::RectangleShape(sf::Vector2f((WORK_PANEL / 2), 30));
        eqbg.setOrigin(eqbg.getLocalBounds().width / 2, eqbg.getLocalBounds().height / 2);
        eqbg.setFillColor(sf::Color(230, 230, 250));
        eqbg.setPosition(sf::Vector2f(10, SCREEN_HEIGHT - myTextLabel.getLocalBounds().height- eqbg.getLocalBounds().height));

        userEq = new Textbox(isTyping);
        /*
        * NEED TO DELETE THIS
        * constantly creating a new one
        */
        userEq->text.str("");
        userEq->textbox.setPosition(eqbg.getPosition());

        writeEqBox();
}

void animate::writeEqBox(){
    eqBox = sf::Text("write here !", font);
    eqBox.setCharacterSize(20);
    eqBox.setStyle(sf::Text::Bold);
    eqBox.setFillColor(sf::Color(170, 51, 106));
    eqBox.setOrigin(0, eqBox.getLocalBounds().height / 2 + 5);
    eqBox.setPosition(eqbg.getPosition());
    eqBox.setString(userEq->text.str());
}

void animate::Draw(){
    // Look at the data and based on the data, draw shapes on window object.
    system.Draw(window);
    if (mouseIn)
    {
        window.draw(mousePoint);
    }

    sidebar.draw(window);

    //- - - - - - - - - - - - - - - - - - -
    // getPosition() gives you screen coords, getPosition(window) gives you window coords
    // cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -

    // drawing Test: . . . . . . . . . . . .
    // This is how you draw text:)
    window.draw(myTextLabel);
    if(isTyping){
        window.draw(eqbg);
        window.draw(userEq->textbox);
        writeEqBox();        
        window.draw(eqBox);
    }
    getDomains();
    window.draw(rightDomain);
    window.draw(leftDomain);
    if(saved_equations > 0){
        // window.draw(history->button);
        // checkButtons();
        checkButtons2();
        for(int i = 0; i < saved_equations; i++){
            // window.draw(fileHistory[i]->textbox);
            old_equations_buttons[i]->drawTo(window);
        }
    }

    //. . . . . . . . . . . . . . . . . . .

}

void animate::update(){
    // cause changes to the data for the next frame
    try{
    // inputError->setCode(0);
    system.Step(command, g_info);
    command = 0;
    if (mouseIn)
    {
        // mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x - 5,
                               sf::Mouse::getPosition(window).y - 5);

        // mouse location text for sidebar:
        sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);
    }
    } // end of try
    catch(errorCode error_code){
        // cout << "ANIMATE: error_code [" << error_code.error_code << "]" << endl;
        inputError.setCode(error_code.error_code);
    }
        // cout << "after: error_code [" << inputError.error_code << "]" << endl;

}

void animate::render(){
    window.clear();
    Draw();
    window.display();
}

void animate::processEvents(){
    sf::Event event;
    while (window.pollEvent(event)) // or waitEvent
    {
        // check the type of the event...
        switch (event.type)
        {
        // window closed
        case sf::Event::Closed:
            window.close();
            break;
        
        if(event.key.code == sf::Keyboard::Tab){
            isTyping = true;
        }

        case sf::Event::TextEntered:
        if(isTyping){
            // cout << "isTyping: " << isTyping << endl;
                    if(event.text.unicode < 128){
                        userEq->inputLogic(event.text.unicode);
                        writeEqBox();
                        // cout << "text = " << userEq->text.str() << endl;     
                    }
                    if(event.text.unicode == sf::Keyboard::Return){
                        isTyping = false;
                    }
            break;
        }
        else if(!isTyping){
        // key pressed
        case sf::Event::KeyPressed:
            if(isTyping){
                switch(event.key.code){
                case sf::Keyboard::Return:
                    sidebar[SB_KEY_PRESSED] = "ENTERED EQUATION";
                    isTyping = false;
                    if(userEq->text.str().length() >= 1){                    
                        g_info->_equation = userEq->text.str();
                        saved_equations++;
                        old_equations.push_back(g_info->_equation); // vector of strings
                        updateHistory(); // saves the Text, new Button
cout << "after: error_code [" << inputError.error_code << "]" << endl;
                            if(inputError.error_code){
                                checkErrorCodes();
                                break;
                            }
                        saveHistory(); 
                        userEq->text.str(""); // clean string
                    }  
                    command = 100;
                break; // exit enter
                }
            break; // exit key pressing
            }
            switch(event.key.code)
            {
            case sf::Keyboard::K:
                sidebar[SB_MOUSE_CLICKED] = "Key: \nPanning: arrows \nZooming: I&O keys \nReset: R \nExit: ESC \nEquation: TAB \nClear History: C";
                command = 2;
            break;
            case sf::Keyboard::Tab:
                sidebar[SB_KEY_PRESSED] = "TYPE EQUATION";
                sidebar[SB_MOUSE_CLICKED] = "";
                isTyping = true;
                makeEqBox();
            break;
            case sf::Keyboard::Left:
                sidebar[SB_KEY_PRESSED] = "LEFT ARROW";
                sidebar[SB_MOUSE_CLICKED] = "";
                command = 4;
            break;
            case sf::Keyboard::Right:
                sidebar[SB_KEY_PRESSED] = "RIGHT ARROW";
                sidebar[SB_MOUSE_CLICKED] = "";
                command = 6;
            break;
            case sf::Keyboard::Up:
                sidebar[SB_KEY_PRESSED] = "UP ARROW";
                sidebar[SB_MOUSE_CLICKED] = "";
                command = 8;
            break;
            case sf::Keyboard::Down:
                sidebar[SB_KEY_PRESSED] = "DOWN ARROW";
                sidebar[SB_MOUSE_CLICKED] = "";
                command = 10;
            break;
            case sf::Keyboard::I:
                sidebar[SB_KEY_PRESSED] = "ZOOM IN";
                sidebar[SB_MOUSE_CLICKED] = "";
                command = 12;
            break;
            case sf::Keyboard::O:
                sidebar[SB_KEY_PRESSED] = "ZOOM OUT";
                sidebar[SB_MOUSE_CLICKED] = "";
                command = 14;
            break;
            case sf::Keyboard::R:
                sidebar[SB_KEY_PRESSED] = "RESET";
                sidebar[SB_MOUSE_CLICKED] = "";
                command = 88;
            break;
            case sf::Keyboard::S:
                sidebar[SB_KEY_PRESSED] = "SAVED HISTORY";
                sidebar[SB_MOUSE_CLICKED] = "";
                saveHistory();
            break;
            case sf::Keyboard::C:
                sidebar[SB_KEY_PRESSED] = "CLEARED HISTORY";
                sidebar[SB_MOUSE_CLICKED] = "";
                clearHistory();
            break;
            case sf::Keyboard::Escape:
                sidebar[SB_KEY_PRESSED] = "ESC: EXIT";
                window.close();
            break;
            }
        } // !clickEq
        break;

        case sf::Event::MouseEntered:
            mouseIn = true;
            break;

        case sf::Event::MouseLeft:
            mouseIn = false;
            break;

        case sf::Event::MouseMoved:
            mouseX = event.mouseMove.x;
            mouseY = event.mouseMove.y;
            // Do something with it if you need to...
            if((mouseX < SCREEN_WIDTH - 50) && (mouseX > WORK_PANEL + 20) && (mouseY < SCREEN_HEIGHT - 30) && (mouseY > SCREEN_HEIGHT - totalbtnHeight - 40) && (saved_equations > 0)){
                // cout << "over button !" << endl;
                // cout << "top of button: " << SCREEN_HEIGHT - totalbtnHeight - 40 << endl;
                // cout << "total button height: " << totalbtnHeight << endl;
                overButton = true;
            }else{
                // cout << "not over button..." << endl;
                overButton = false;
            }
        break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                // sidebar[SB_MOUSE_CLICKED] = "RIGHT CLICK " +
                //                             mouse_pos_string(window);
            }
            else
            {
                /*mouseX = event.mouseMove.x;
                mouseY = event.mouseMove.y;
                if((mouseX < SCREEN_WIDTH) && (mouseX > (WORK_PANEL + 20)) && (mouseY < SCREEN_HEIGHT - 50) && (mouseY > SCREEN_HEIGHT - history->btnHeight) && (saved_equations > 0)){
                    cout << "history button color change activated" << endl;
                    overButton = true;
                }
                else{
                    overButton = false;
                    break;*/

                clicked = true;
                cout << "clicked!" << endl;
                //     sidebar[SB_MOUSE_CLICKED] = "LEFT CLICK " +
                //                                 mouse_pos_string(window);
                // }
            break;
            }
        default:
            overButton = false;
            clicked = false;
        break;
        }
    }
}

void animate::run(){
    while (window.isOpen())
    {
        processEvents();
        update();
        render(); // clear/draw/display
    }
    cout << endl
         << "-------ANIMATE MAIN LOOP EXITING ------------" << endl;
}

string mouse_pos_string(sf::RenderWindow &window){
    return "(" +
           to_string(sf::Mouse::getPosition(window).x) +
           ", " +
           to_string(sf::Mouse::getPosition(window).y) +
           ")";
}
