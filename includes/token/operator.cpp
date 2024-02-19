#include <cmath>
#include "operator.h"

void Operator::init_precedence(){
    if(_op == "+" || _op == "-"){
        _precedence = 1;
    }
    if(_op == "*" || _op == "/"){
        _precedence = 2;
    }
    if(_op == "^"){
        _precedence = 3;
    }
    if(_op == "x" || _op == "X" && _op.length() == 1 && _op.length() == 1){ // change precedence for variable
        _precedence = 999;
    }
    if(_op.length() > 1){
        _precedence = 999;
    }
    if(_op == ""){
        _precedence = 9999;
    }

}

double Operator::evaluate(double under, double above){
    if(_op == "+"){
        return (under + above);
    }
    if(_op == "-"){
        return (under - above);
    }
    if(_op == "*"){
        return (under * above);
    }
    if(_op == "/"){
        return (under / above);
    }
    if(_op == "^"){
        return (pow(under, above));
    }
    return 9999;
}

