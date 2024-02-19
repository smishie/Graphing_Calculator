#ifndef OPERATOR_H
#define OPERATOR_H
#include <iostream>
#include <iomanip>
#include <string>
#include "token.h"

using namespace std;

class Operator: public Token{
public:
    Operator(): Token(){ init_precedence(); _op = ""; }
    Operator(char op){ _op = op; init_precedence(); }
    Operator(const string& str): Token(str), _op(str){ init_precedence(); }
    
    double evaluate(double lhs, double rhs);
    virtual int get_type(){ return _type; }

    virtual int get_precedence(){ return _precedence; }

    virtual string get_op(){ return _op; }
    void init_precedence();

    virtual void print() const{
        cout << _op;
    }

private: 
    string _op;
    int _type = 2;
    int _precedence;
};

#endif 