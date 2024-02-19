#ifndef INTEGER_H
#define INTEGER_H
#include <iostream>
#include <cmath>
#include <iomanip>
#include "token.h"

class Integer: public Token{
public:
    Integer(): Token(){ _value = 9999; }
    Integer(const string& str): Token(str){ _value = stod(str); }
    Integer(double value): Token(), _value(value){}

    virtual int get_type(){ return _type; }
    virtual double get_value(){ return _value; }

    virtual void print() const{
        cout << _value;
    }

private:
    double _value;
    int _type = 1;
};

#endif 
