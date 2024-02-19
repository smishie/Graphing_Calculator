#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include "operator.h"

class Function: public Operator{
public: 
    Function(): Operator(){ _func = ""; init_precedence(); }
    Function(const string& str): Operator(str), _func(str){ init_precedence(); }

    virtual int get_precedence(){ return _precedence; }
    bool is_variable(){
        if(_func.length() == 1){
            return true;
        }
        return false;
    }

    virtual string get_op(){ return _func; }
    double evaluate_func(double x);

    virtual void print() const{
        cout <<  _func;
    }
    
private:
    int _precedence = 999;
    string _func;
};

#endif 
