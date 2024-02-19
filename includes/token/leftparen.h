#ifndef LEFTPAREN_H
#define LEFTPAREN_H
#include <iostream>
#include <iomanip>
#include "token.h"

class LeftParen: public Token{
public:
    LeftParen(): Token(), _str("(") {}
    LeftParen(const string& str): Token(str), _str(str){}

    virtual int get_type(){ return _type; }
    virtual string get_op(){ return "("; }

    virtual void print() const{
        cout << "( ";
    } 

private:
    int _type = 4;
    string _str;

};

#endif
