#include "system.h"

using namespace std;

System::System(Graph_info* g): _info(g){
    _info->_equation = "x"; // sin(x^-2)
    Plot _plot = Plot(_info);
    _points = _plot();
}

void System::Step(int command, Graph_info*& g){
    _info = g;
    if(command == 100){ // entering equation
        // _g.update(_info);
    }
    else if(command == 4){ // left arrow
        _info->_origin.x += (_info->_window_dimensions.x * (_info->fullDomain / 10) / _info->fullDomain);
        _info->_domain.x -= (_info->fullDomain / 10);
        _info->_domain.y -= (_info->fullDomain / 10);
        // _info->_domain.x -= 1;
        // _info->_domain.y -= 1;
        // _info->_origin.x += (_info->_window_dimensions.x/ _info->fullDomain);
        // _g.update(_info);
    }
    else if(command == 6){ // right arrow
        _info->_origin.x -= (_info->_window_dimensions.x * (_info->fullDomain / 10) / _info->fullDomain);
        _info->_domain.x += (_info->fullDomain / 10);
        _info->_domain.y += (_info->fullDomain / 10);
        // _info->_domain.x += 1;
        // _info->_domain.y += 1;
        // _info->_origin.x -= (_info->_window_dimensions.x / _info->fullDomain);
        // _g.update(_info);
    }
    else if(command == 8){ // up arrow
        _info->_origin.y += (_info->_window_dimensions.y * (_info->fullDomain / 10) / _info->fullDomain);
        // _info->_origin.y += (_info->_window_dimensions.y / _info->fullDomain);
        // _g.update(_info);
    }  
    else if(command == 10){ // down arrow
        _info->_origin.y -= (_info->_window_dimensions.y * (_info->fullDomain / 10) / _info->fullDomain);
        // _g.update(_info);
    }
    else if(command == 12){ // zoom in
        // _info->_domain.x -= (_info->_window_dimensions.x * (_info->fullDomain / 50) / _info->fullDomain);
        // _info->_domain.y -= (_info->_window_dimensions.x * (_info->fullDomain / 50) / _info->fullDomain);
        // _info->fullDomain = abs(_info->_window_dimensions.x * (_info->fullDomain / 50) / _info->fullDomain - _info->_window_dimensions.x * (_info->fullDomain / 50) / _info->fullDomain);

        _info->_domain.x /= 1.2;
        _info->_domain.y /= 1.2;
        _info->fullDomain = abs((_info->_domain.y /= 1.2) -  (_info->_domain.x /= 1.2));
        // _g.update(_info);
    }
    else if(command == 14){ // zoom out
        // _info->_domain.x -= (_info->_window_dimensions.x * (_info->fullDomain / 50) / _info->fullDomain);
        // _info->_domain.y -= (_info->_window_dimensions.x * (_info->fullDomain / 50) / _info->fullDomain);
        // _info->fullDomain = abs(_info->_window_dimensions.x * (_info->fullDomain / 50) / _info->fullDomain - _info->_window_dimensions.x * (_info->fullDomain / 50) / _info->fullDomain);

        _info->_domain.x *= 1.2;
        _info->_domain.y *= 1.2;
        _info->fullDomain = abs((_info->_domain.y *= 1.2) -  (_info->_domain.x *= 1.2));
        // _g.update(_info);
    }
    else if(command == 88){ // reset
        _info->_domain = sf::Vector2f(-5, 5);
        _info->fullDomain = abs(_info->_domain.y - _info->_domain.x);
        _info->_origin = sf::Vector2f(WORK_PANEL - (WORK_PANEL / 2), SCREEN_HEIGHT - (SCREEN_HEIGHT / 2));
        // _g.update(_info);
    }
    _g.update(_info);
}

void System::Draw(sf::RenderWindow &window){
    window.clear();
    _g.draw(window, _points);
}
