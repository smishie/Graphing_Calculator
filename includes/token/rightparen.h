#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H
#include <iostream>
#include <iomanip>
#include "token.h"

class RightParen: public Token{
public:
    RightParen(): Token(), _str(")") {}
    RightParen(const string& str): Token(str), _str(str){}

    virtual int get_type(){ return _type; }

    virtual void print() const{
        cout << ")";
    }

private:
    int _type = 5;
    string _str;
};

#endif 